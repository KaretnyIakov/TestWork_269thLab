// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HealthInterface.generated.h"

// This class does not need to be modified
UINTERFACE(MinimalAPI)
class UHealthInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TESTTOPDOWN_API IHealthInterface
{
	GENERATED_BODY()

	// Functions in this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Health")
	void OnDmd(float Dmg);
	virtual void OnDmd_Implementation(float Dmg) = 0;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Health")
	void OnHeal(float Heal);
	virtual void OnHeal_Implementation(float Heal) = 0;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Health")
	void OnDeath();
	virtual void OnDeath_Implementation() = 0;

};
