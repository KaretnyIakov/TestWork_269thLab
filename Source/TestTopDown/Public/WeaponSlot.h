// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponSlot.generated.h"


// Enum for weapon slots
UENUM(BlueprintType)
enum class EWeaponSlotTypes : uint8
{
	None UMETA(DisplayName = "None"),
	First UMETA(DisplayName = "First"),
	Second UMETA(DisplayName = "Second")

};

// Weapon Slot Actor Cpmponent with the ability to be the parent class for blueprint classes
UCLASS(Blueprintable)
class TESTTOPDOWN_API UWeaponSlot : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UWeaponSlot();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "WeaponSlotType")
	EWeaponSlotTypes WeaponSlotType;

protected:

	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintImplementableEvent)
	bool IsWeaponValid();

	UFUNCTION(BlueprintCallable)
	void SetSlotType(EWeaponSlotTypes NewSlotType);

		
};
