// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "SPowerupActor.generated.h"


class USphereComponent;
class UStaticMeshComponent;

UCLASS(ABSTRACT)
class ACTIONROGUELIKEV_API ASPowerupActor : public AActor, public ISGamePlayInterface
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, Category = "Powerup")
	float RespawnTime;

	FTimerHandle TimerHandle_RespawnTimer;

	UFUNCTION()
	void ShowPowerup();

	void HideAndCooldownPowerup();

	void SetPowerupState(bool bNewIsActive);

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;


public:

	void Interact_Implementation(APawn* InstigatorPawn) override;

public:

	ASPowerupActor();

};
