// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSlot.h"

// Sets default values for this component's properties
UWeaponSlot::UWeaponSlot()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWeaponSlot::BeginPlay()
{
	Super::BeginPlay();
}

void UWeaponSlot::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWeaponSlot::SetSlotType(EWeaponSlotTypes NewSlotType)
{
	this->WeaponSlotType = NewSlotType;
}

