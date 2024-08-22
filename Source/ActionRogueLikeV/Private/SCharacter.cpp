// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SInteractionComponent.h"
#include "SAttributeComponent.h"
#include "SProjectileBase.h"
#include "SDashProjectile.h"


// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);
	bUseControllerRotationYaw = false;
	//character looks at the current rotation
	GetCharacterMovement()->bOrientRotationToMovement = true;

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");
	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");
}

void ASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComp->OnHealthChanged.AddDynamic(this, &ASCharacter::OnHealthChanged);
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASCharacter::MoveForward(float value) 
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	AddMovementInput(ControlRot.Vector(), value);
}

void ASCharacter::MoveRight(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	
	//X forward
	//Y right
	//Z up
	// player rotates with camera not pawn
	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, value);
}

void ASCharacter::StartJumpAction() 
{
	
	bPressedJump = true;
}

void ASCharacter::StopJumpAction()
{
	bPressedJump = false;
}

void ASCharacter::PrimaryAttack() 
{
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimeLapsed, 0.2f);
	
}


void ASCharacter::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}

void ASCharacter::PrimaryAttack_TimeLapsed()
{
	if (ensure(ProjectileClass))
	{
		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
		//GetControlRotation is where we are looking at
		//GetActorLocation is center of our actor to spawn
		FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);

		FActorSpawnParameters SpawnParams;
		//SpawnCollisionHandlingOverride is to specify spawn rules
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
	}
	
}

void ASCharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (NewHealth <= 0.0f && Delta < 0.0f )
	{
		//prevent character from moving after death
	    APlayerController* PC =	Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
}



//void ASCharacter::BlackHoleAttack()
//{
//	PlayAnimMontage(AttackAnim);
//	GetworldTimerManager().SetTimer(TimerHandle_BlackholeAttack, this, &ASCharacter::BlackholeAttack_TimeLapsed, AttackAnimDelay);
//}
//
//void ASCharacter::BlackholeAttack_TimeLapsed()
//{
//	SpawnProjectile(BlackHoleProjectileClass);
//}
//
//void ASCharacter::Dash() 
//{
//	PlayAnimMontage(AttackAnim);
//	GetworldTimerManager().SetTimer(TimerHandle_Dash, this, &ASCharacter::Dash_TimeLapsed, AttackAnimDelay);
//}
//
//void ASCharacter::Dash_TimeLapsed() 
//{
//	SpawnProjectile(DashProjectileClass);
//}
//
//void ASCharacter::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
//{
//	if (ensureAlways(ClassToSpawn))
//	{
//		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
//
//		FActorSpawnParameters SpawnParams;
//		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//		SpawnParams.Instigator = this;
//
//		FCollisionShape Shape;
//		Shape.SetSphere(20.0f);
//
//		// Ignore Player
//		FCollisionQueryParams Params;
//		Params.AddIgnoredActor(this);
//
//		FCollisionObjectQueryParams ObjParams;
//		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
//		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
//		ObjParams.AddObjectTypesToQuery(ECC_Pawn);
//
//		FVector TraceStart = CameraComp->GetComponentLocation();
//
//		// endpoint far into the look-at distance (not too far, still adjust somewhat towards crosshair on a miss)
//		FVector TraceEnd = CameraComp->GetComponentLocation() + (GetControlRotation().Vector() * 5000);
//
//		FHitResult Hit;
//		// returns true if we got to a blocking hit
//		if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Shape, Params))
//		{
//			// Overwrite trace end with impact point in world
//			TraceEnd = Hit.ImpactPoint;
//		}
//
//		// find new direction/rotation from Hand pointing to impact point in world.
//		FRotator ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();
//
//		FTransform SpawnTM = FTransform(ProjRotation, HandLocation);
//		GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnTM, SpawnParams);
//	}
//}


// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("JumpAction", IE_Pressed, this, &ASCharacter::StartJumpAction);
	PlayerInputComponent->BindAction("JumpAction", IE_Released, this, &ASCharacter::StopJumpAction);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);
}

