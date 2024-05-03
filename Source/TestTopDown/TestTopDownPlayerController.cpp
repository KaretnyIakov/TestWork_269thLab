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
	// Call the base class  
	Super::BeginPlay();

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
	// set up gameplay key bindings
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
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}



void ATestTopDownPlayerController::OnInputStarted()
{
	UE_LOG(LogTemp, Error, TEXT("I ready for shoot"));
	MoveSpeed = 0.5f;
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

void ATestTopDownPlayerController::OnInputMoveStarted()
{
	//UE_LOG(LogTemp, Error, TEXT("I got input"));
}

// Add Pawn movement on triggers
void ATestTopDownPlayerController::OnMoveTopTriggered()
{
	if (GetPawn())
	{
		GetPawn()->AddMovementInput(FVector(1, 0, 0), MoveSpeed);
	}
}
void ATestTopDownPlayerController::OnMoveDownTriggered()
{
	if (GetPawn())
	{
		GetPawn()->AddMovementInput(FVector(1, 0, 0), -MoveSpeed);
	}
}
void ATestTopDownPlayerController::OnMoveRightTriggered()
{
	if (GetPawn())
	{
		GetPawn()->AddMovementInput(FVector(0, 1, 0), MoveSpeed);
	}
}
void ATestTopDownPlayerController::OnMoveLeftTriggered()
{
	if (GetPawn())
	{
		GetPawn()->AddMovementInput(FVector(0, 1, 0), -MoveSpeed);
	}
}

void ATestTopDownPlayerController::OnMoveRealeased()
{
	//UE_LOG(LogTemp, Error, TEXT("I realeased input"));
}