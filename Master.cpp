// Fill out your copyright notice in the Description page of Project Settings.


#include "Master.h"
#include "Cell.h"
#include "Engine/World.h"
#include <fstream>

// Sets default values
AMaster::AMaster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMaster::BeginPlay()
{
	Super::BeginPlay();
	FActorSpawnParameters SpawnParams;
	AActor* TempActor;
	for (size_t x = 0; x < 10; x++)
	{
		for (size_t y = 0; y < 10; y++)
		{
			for (size_t z = 0; z < 10; z++)
			{
				TempActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, FVector(100*x,100*y,100*z), FRotator(0,0,0),SpawnParams);

			}

		}
	}
}

// Called every frame
void AMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

