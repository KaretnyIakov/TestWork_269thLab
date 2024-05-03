// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TestTopdown/Public/HealthComponent.h"
#include "TestTopdown/Public/HealthInterface.h"
#include "Enemy.generated.h"

UCLASS()
class TESTTOPDOWN_API AEnemy : public APawn, public IHealthInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();
	/** Returns HealthComponent subobject **/
	FORCEINLINE class UHealthComponent* GetHealthComponent() const { return HealthComponent; }

	virtual void OnDmd_Implementation(float Dmg) override;
	virtual void OnHeal_Implementation(float Heal) override;
	virtual void OnDeath_Implementation() override;

	// Implement in Blueprint Attack Function
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Attack();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FVector StartLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* HealthComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


};
