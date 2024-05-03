// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/KismetMathLibrary.h"
#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::SetStartParams(float Health)
{
	// Max and Start HP = input value
	MaxHealth = CurrentHealth = Health;
}

void UHealthComponent::GetDmg(float Dmg)
{
	if (!IsDead)
	{
		CurrentHealth = UKismetMathLibrary::Max(CurrentHealth - Dmg, 0.0f);
		if (CurrentHealth == 0.0f)
		{
			Death();
		}
	}
	
}

void UHealthComponent::GetHeal(float Heal)
{
	if (!IsDead)
	{
		CurrentHealth = UKismetMathLibrary::Min(CurrentHealth + Heal, MaxHealth);
	}
}

void UHealthComponent::Death()
{
	if (!IsDead)
	{
		IsDead = true;
		AActor* Owner = GetOwner();
		if (Owner && Owner->GetClass()->ImplementsInterface(UHealthInterface::StaticClass()))
		{
			IHealthInterface* Interface = Cast<IHealthInterface>(Owner);
			if (Interface)
			{
				Interface->Execute_OnDeath(Owner);
			}
		}
	}
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

