// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ShootingInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UShootingInterface : public UInterface
{
	GENERATED_BODY()


};

/**
 * 
 */
class TESTTOPDOWN_API IShootingInterface
{
	GENERATED_BODY()

	// Functions in this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Shoot")
	void Shooting();
	virtual void Shooting_Implementation() = 0;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Shoot")
	void StopShooting();
	virtual void StopShooting_Implementation() = 0;
};
