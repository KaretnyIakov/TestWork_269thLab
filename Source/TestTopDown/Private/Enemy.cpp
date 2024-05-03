// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;
	// Create a HealthComponent
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->SetupAttachment(RootComponent);

	//StartLocation = GetActorLocation();
}

void AEnemy::OnDmd_Implementation(float Dmg)
{
	HealthComponent->GetDmg(Dmg);
}

void AEnemy::OnHeal_Implementation(float Heal)
{
	HealthComponent->GetHeal(Heal);
}

void AEnemy::OnDeath_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("I Die"));
}


// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

