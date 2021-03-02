// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnOverworldcheat.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

// Sets default values
ASpawnOverworldcheat::ASpawnOverworldcheat()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnOverworldcheat::BeginPlay()
{
	Super::BeginPlay();
	//What needs to happen is the player should be teleported to just outside of caer athweddne.
	FLatentActionInfo LatentInfo;
	UGameplayStatics::LoadStreamLevel(this, "Main2", true, true, LatentInfo);
	UGameplayStatics::UnloadStreamLevel(this, "MainMenuLevel", LatentInfo, true);

	ACharacter* playerchar = UGameplayStatics::GetPlayerCharacter(this, 0);
	playerchar->SetActorLocation(FVector(93025.0, 231595.0, 3355.0),false,false);

	Destroy();
}

// Called every frame
void ASpawnOverworldcheat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

