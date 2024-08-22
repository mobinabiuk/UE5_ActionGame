// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USInteractionComponent;
class UAnimMontage;
class USAttributeComponent;

UCLASS()
class ACTIONROGUELIKEV_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
   UPROPERTY(EditAnywhere, Category = "Attack")
   TSubclassOf<AActor> ProjectileClass;

   UPROPERTY(EditAnywhere, Category = "Attack")
   UAnimMontage* AttackAnim;

   FTimerHandle TimerHandle_PrimaryAttack;
  public:
	// Sets default values for this character's properties
	ASCharacter();

protected:

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components")
	USAttributeComponent* AttributeComp;

	

	void MoveForward(float value);
	void MoveRight(float value);
	void StartJumpAction();
	void StopJumpAction();
	void PrimaryAttack();
	void PrimaryInteract();
	void PrimaryAttack_TimeLapsed();

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);
	
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
