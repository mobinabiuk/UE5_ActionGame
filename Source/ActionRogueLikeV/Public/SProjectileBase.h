// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SProjectileBase.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;


UCLASS(ABSTRACT)
class ACTIONROGUELIKEV_API ASProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	ASProjectileBase();
	

protected:
	UPROPERTY(EditDefaultsOnly,Category = "Effects")
	UParticleSystem* ImpactVFX;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* MoveComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UParticleSystemComponent* EffectComp;

	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//lets us have cpp implementation and override that in blueprint
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode();

	

	virtual void PostInitializeComponents() override;

	// Called when the game starts or when spawned
	

   public:
	// Sets default values for this actor's properties
	
};
