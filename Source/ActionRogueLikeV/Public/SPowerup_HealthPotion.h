// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerupActor.h"
#include "SPowerup_HealthPotion.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKEV_API ASPowerup_HealthPotion : public ASPowerupActor
{
	GENERATED_BODY()
	
public:

	ASPowerup_HealthPotion();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

protected:

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
};
