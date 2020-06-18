// Fill out your copyright notice in the Description page of Project Settings.


#include "LightPlayerHealScript.h"
#include "Entity.h"
#include "GenericFunctions.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALightPlayerHealScript::ALightPlayerHealScript()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALightPlayerHealScript::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ALightPlayerHealScript::IterateHeal, 1.0f, false);
	
}

void ALightPlayerHealScript::IterateHeal()
{
	AEntity* Player = (AEntity*)UGameplayStatics::GetPlayerPawn(this, 0);
	if (Player->Health >= Player->MaxHealth)
	{
		this->Destroy();
	}
	else
	{
		Player->Health += 1;
	}
}


