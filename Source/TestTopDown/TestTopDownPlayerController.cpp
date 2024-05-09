// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestTopDownPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "TestTopDownCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "InputModifiers.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ATestTopDownPlayerController::ATestTopDownPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
}

void ATestTopDownPlayerController::BeginPlay()
{  

	Super::BeginPlay();

	// Cast Character
	ControlPawn = Cast<ATestTopDownCharacter>(GetPawn());

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}


void ATestTopDownPlayerController::Shooting_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("I shoot"));
}

void ATestTopDownPlayerController::StopShooting_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("I stop shoot"));
}



void ATestTopDownPlayerController::SetupInputComponent()
{
	// Set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ATestTopDownPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ATestTopDownPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ATestTopDownPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ATestTopDownPlayerController::OnSetDestinationReleased);

		// Setup move top and down input events
		EnhancedInputComponent->BindAction(SetMoveTopAction, ETriggerEvent::Started, this, &ATestTopDownPlayerController::OnInputMoveStarted);
		EnhancedInputComponent->BindAction(SetMoveTopAction, ETriggerEvent::Triggered, this, &ATestTopDownPlayerController::OnMoveTopTriggered);
		EnhancedInputComponent->BindAction(SetMoveTopAction, ETriggerEvent::Completed, this, &ATestTopDownPlayerController::OnMoveRealeased);
		EnhancedInputComponent->BindAction(SetMoveTopAction, ETriggerEvent::Canceled, this, &ATestTopDownPlayerController::OnMoveRealeased);

		EnhancedInputComponent->BindAction(SetMoveDownAction, ETriggerEvent::Started, this, &ATestTopDownPlayerController::OnInputMoveStarted);
		EnhancedInputComponent->BindAction(SetMoveDownAction, ETriggerEvent::Triggered, this, &ATestTopDownPlayerController::OnMoveDownTriggered);
		EnhancedInputComponent->BindAction(SetMoveDownAction, ETriggerEvent::Completed, this, &ATestTopDownPlayerController::OnMoveRealeased);
		EnhancedInputComponent->BindAction(SetMoveDownAction, ETriggerEvent::Canceled, this, &ATestTopDownPlayerController::OnMoveRealeased);

		// Setup move right and left input events
		EnhancedInputComponent->BindAction(SetRightAction, ETriggerEvent::Started, this, &ATestTopDownPlayerController::OnInputMoveStarted);
		EnhancedInputComponent->BindAction(SetRightAction, ETriggerEvent::Triggered, this, &ATestTopDownPlayerController::OnMoveRightTriggered);
		EnhancedInputComponent->BindAction(SetRightAction, ETriggerEvent::Completed, this, &ATestTopDownPlayerController::OnMoveRealeased);
		EnhancedInputComponent->BindAction(SetRightAction, ETriggerEvent::Canceled, this, &ATestTopDownPlayerController::OnMoveRealeased);

		EnhancedInputComponent->BindAction(SetLeftAction, ETriggerEvent::Started, this, &ATestTopDownPlayerController::OnInputMoveStarted);
		EnhancedInputComponent->BindAction(SetLeftAction, ETriggerEvent::Triggered, this, &ATestTopDownPlayerController::OnMoveLeftTriggered);
		EnhancedInputComponent->BindAction(SetLeftAction, ETriggerEvent::Completed, this, &ATestTopDownPlayerController::OnMoveRealeased);
		EnhancedInputComponent->BindAction(SetLeftAction, ETriggerEvent::Canceled, this, &ATestTopDownPlayerController::OnMoveRealeased);

		// Setup reload weapon
		EnhancedInputComponent->BindAction(SetReloadAction, ETriggerEvent::Triggered, this, &ATestTopDownPlayerController::OnInputReloadTriggered);

		// Setup interact
		EnhancedInputComponent->BindAction(SetInteractAction, ETriggerEvent::Triggered, this, &ATestTopDownPlayerController::OnInputInteractTriggered);

		// Setup weapon slots
		EnhancedInputComponent->BindAction(SetSelectFirstWeaponSlotAction, ETriggerEvent::Triggered, this, &ATestTopDownPlayerController::OnInputSelectFirstWeaponSlotTriggered);
		EnhancedInputComponent->BindAction(SetSelectSecondWeaponSlotAction, ETriggerEvent::Triggered, this, &ATestTopDownPlayerController::OnInputSelectSecondWeaponSlotTriggered);

		// Setup pause
		EnhancedInputComponent->BindAction(SetPauseAction, ETriggerEvent::Completed, this, &ATestTopDownPlayerController::OnInputPauseTriggered);
		
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}



void ATestTopDownPlayerController::OnInputStarted()
{
	// Change moving speed on aiming start
	MoveSpeed = 0.5f;
	UE_LOG(LogTemp, Error, TEXT("I ready for shoot"));

}

// Triggered every frame when the input is held down
void ATestTopDownPlayerController::OnSetDestinationTriggered()
{

	 // We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	
	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	Execute_Shooting(this);
	RotatePawnToAim(CachedDestination);
}

void ATestTopDownPlayerController::OnSetDestinationReleased()
{
	Execute_StopShooting(this);
	MoveSpeed = 1.0f;
}

void ATestTopDownPlayerController::OnInputReloadTriggered()
{
	ControlPawn->ReloadWeapon();
}

void ATestTopDownPlayerController::OnInputInteractTriggered()
{
	if (ControlPawn)
	{
		for (int32 i = 0; i < ControlPawn->ItemsInRad.Num(); ++i)
		{
			AActor* Item = ControlPawn->ItemsInRad[i];
			if (Item && this->GetNewItem(Item))
			{
				if (i >= ControlPawn->ItemsInRad.Num())
				{
					break;
				}
				i--;
			}
		}
	}
}

void ATestTopDownPlayerController::OnInputSelectFirstWeaponSlotTriggered()
{
	if (ControlPawn && ControlPawn->GetFirstWeaponSlot()->IsWeaponValid())
	{
		this->ActivateSelectedWeaponSlot(ControlPawn->GetFirstWeaponSlot());
	}
}

void ATestTopDownPlayerController::OnInputSelectSecondWeaponSlotTriggered()
{
	if (ControlPawn && ControlPawn->GetSecondWeaponSlot()->IsWeaponValid())
	{
		this->ActivateSelectedWeaponSlot(ControlPawn->GetSecondWeaponSlot());
	}
}

void ATestTopDownPlayerController::OnInputPauseTriggered()
{
	UE_LOG(LogTemp, Error, TEXT("PAUSE"));
	
	OpenPauseMenuWidget();

	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); 

	this->SetInputMode(InputMode);
	SetPause(true);
}

void ATestTopDownPlayerController::OnInputMoveStarted()
{
	//UE_LOG(LogTemp, Error, TEXT("I got input"));
}

// Add Pawn movement on triggers
void ATestTopDownPlayerController::OnMoveTopTriggered()
{
	if (ControlPawn && !IsPaused())
	{
		GetPawn()->AddMovementInput(FVector(1, 0, 0), MoveSpeed);
	}
}
void ATestTopDownPlayerController::OnMoveDownTriggered()
{
	if (ControlPawn && !IsPaused())
	{
		GetPawn()->AddMovementInput(FVector(1, 0, 0), -MoveSpeed);
	}
}
void ATestTopDownPlayerController::OnMoveRightTriggered()
{
	if (ControlPawn && !IsPaused())
	{
		GetPawn()->AddMovementInput(FVector(0, 1, 0), MoveSpeed);
	}
}
void ATestTopDownPlayerController::OnMoveLeftTriggered()
{
	if (ControlPawn && !IsPaused())
	{
		GetPawn()->AddMovementInput(FVector(0, 1, 0), -MoveSpeed);
	}
}

void ATestTopDownPlayerController::OnMoveRealeased()
{
	//UE_LOG(LogTemp, Error, TEXT("I realeased input"));
}