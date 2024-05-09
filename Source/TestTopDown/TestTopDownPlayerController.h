// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "TestTopdown/TestTopDownCharacter.h"
#include "TestTopdown/Public/WeaponSlot.h"
#include "TestTopdown/Public/ShootingInterface.h"
#include "TestTopDownPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class ATestTopDownPlayerController : public APlayerController, public IShootingInterface
{
	GENERATED_BODY()

public:
	ATestTopDownPlayerController();

	/** Controlled Pawn reference */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = References)
	ATestTopDownCharacter* ControlPawn;

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	/** Input Actions */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SetReloadAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SetInteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SetSelectFirstWeaponSlotAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SetSelectSecondWeaponSlotAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SetPauseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SetMoveTopAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SetMoveDownAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SetRightAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SetLeftAction;


	virtual void Shooting_Implementation() override;
	virtual void StopShooting_Implementation() override;

	/** Implemented in Blueprint : Pawn Rotation Function */
	UFUNCTION(BlueprintImplementableEvent)
	void RotatePawnToAim(FVector location);

	/** Implemented in Blueprint : Select Weapon from Slot */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ActivateSelectedWeaponSlot(UWeaponSlot* WeaponSlot);

	/** Implemented in Blueprint : Get Item for Inventory */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	bool GetNewItem(AActor* Item);

	/** Implemented in Blueprint : Start Pause and open menu */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OpenPauseMenuWidget();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

	/** Input handlers */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();

	void OnInputReloadTriggered();
	void OnInputInteractTriggered();
	void OnInputSelectFirstWeaponSlotTriggered();
	void OnInputSelectSecondWeaponSlotTriggered();
	void OnInputPauseTriggered();

	void OnInputMoveStarted();
	void OnMoveTopTriggered();
	void OnMoveDownTriggered();
	void OnMoveRightTriggered();
	void OnMoveLeftTriggered();
	void OnMoveRealeased();

private:
	FVector CachedDestination;

	float MoveSpeed = 1.0f;
};


