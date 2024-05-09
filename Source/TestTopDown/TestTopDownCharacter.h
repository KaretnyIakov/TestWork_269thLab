// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TestTopdown/Public/HealthComponent.h"
#include "TestTopdown/Public/WeaponSlot.h"
#include "TestTopdown/Public/HealthInterface.h"
#include "TestTopDownCharacter.generated.h"

UCLASS(Blueprintable)
class ATestTopDownCharacter : public ACharacter, public IHealthInterface
{
	GENERATED_BODY()

public:
	ATestTopDownCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns HealthComponent subobject **/
	FORCEINLINE class UHealthComponent* GetHealthComponent() const { return HealthComponent; }

	virtual void OnDmd_Implementation(float Dmg) override;
	virtual void OnHeal_Implementation(float Heal) override;
	virtual void OnDeath_Implementation() override;

	/* Weapon Slots for FIRST - Pistol and SECOND - Riffle */
	FORCEINLINE class UWeaponSlot* GetFirstWeaponSlot() const { return FirstWeaponSlot; }
	FORCEINLINE class UWeaponSlot* GetSecondWeaponSlot() const { return SecondWeaponSlot; }

	/** Reload Current Weapon */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ReloadWeapon();

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/* Components : Health */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* HealthComponent;

	/* Components : Weapon */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	class UWeaponSlot* FirstWeaponSlot;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	class UWeaponSlot* SecondWeaponSlot;
	
public:
	// This array for items, with witch player can interact
	UPROPERTY(BlueprintReadWrite, Category = Items)
	TArray<AActor*> ItemsInRad;
};

