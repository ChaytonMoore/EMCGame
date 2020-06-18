// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelChangeLocator.h"
#include "Engine/World.h"
#include "CoreMinimal.h"
#include "Engine.h"
#include "EngineMinimal.h"
#include "Entity.h"
#include "Components/ArrowComponent.h"

// Sets default values
ALevelChangeLocator::ALevelChangeLocator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("The arrow component"));


}

// Called when the game starts or when spawned
void ALevelChangeLocator::BeginPlay()
{
	Super::BeginPlay();
	UWorld*  world = GetWorld(); //I'm not sure it might be best if this is in event tick though it might be too much.
	AController* cont = world->GetFirstPlayerController();
	APawn* PPawn = cont->GetPawn();
	AEntity* Player = Cast<AEntity>(PPawn);
	if (Player->TransportString == TransitionString)
	{
		Player->SetActorLocation(GetActorLocation(),false); //I think this sets the player location to the actor location.
		Player->TransportString = "Invalid";

	}
	
}

// Called every frame
void ALevelChangeLocator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

