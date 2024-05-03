// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "TestTopdown/Public/HealthInterface.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTTOPDOWN_API UHealthComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Default values for this component's properties
	UHealthComponent();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Health")
	float MaxHealth = 100.0f;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Health")
	float CurrentHealth = 100.0f;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Health")
	bool IsDead = false;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetStartParams(float Health);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void GetDmg(float Dmg);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void GetHeal(float Heal);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void Death();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
