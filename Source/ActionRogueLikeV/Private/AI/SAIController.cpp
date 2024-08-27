// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAIController.h"
#include <Kismet/GameplayStatics.h>
#include "BehaviorTree/BlackboardComponent.h"


class UBehaviorTree;

void ASAIController::BeginPlay()
{
	Super::BeginPlay();

	//Starts execution of behavior tree
	RunBehaviorTree(BehaviorTree);
	//retrieves a reference to the player's pawn in the game.
    APawn* MyPawn =	UGameplayStatics::GetPlayerPawn(this, 0);
	if (MyPawn)
	{
		//sets a value in the AI's Blackboard
		GetBlackboardComponent()->SetValueAsVector("MoveToLocation",MyPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsObject("TargetActor", MyPawn);
	}
}
