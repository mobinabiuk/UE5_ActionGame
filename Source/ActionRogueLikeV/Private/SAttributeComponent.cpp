// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"



// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	HealthMax = 200;
	Health = HealthMax;
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

bool USAttributeComponent::IsFullHealth() const
{
	return Health == HealthMax;
}

float USAttributeComponent::GetHealthMax() const
{
	return HealthMax;
}

bool USAttributeComponent::ApplyHealthChange(float Delta)
{
	//Health += Delta;
	float OldHealth = Health;
	Health = FMath::Clamp(Health + Delta, 0.0f, HealthMax);
	float ActualDelta = Health - OldHealth;
	OnHealthChanged.Broadcast(nullptr, this, Health, ActualDelta);
	return ActualDelta != 0;
}



