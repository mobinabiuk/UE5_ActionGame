// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SGamePlayInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USGamePlayInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ACTIONROGUELIKEV_API ISGamePlayInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//expose function in both c++ & Blueprint
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	//interact function and who triggered it?
	void Interact(APawn* InstigatorPawn);
};
