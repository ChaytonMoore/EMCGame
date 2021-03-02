// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterPackSpawner.h"
#include "Engine/World.h"

// Sets default values
AMonsterPackSpawner::AMonsterPackSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	flecha = CreateDefaultSubobject<UArrowComponent>(TEXT("flecha"));
	RootComponent = flecha;
}

void AMonsterPackSpawner::SpawnMonsters()
{
	int TempSpawnNum;
	TSubclassOf<AEntity> TempSpawnClass;
	FActorSpawnParameters SpawnInfo;
	FVector Location = GetActorLocation();
	FRotator Rotation = GetActorRotation();
	for (auto& Elem : MonsterPackStruct)
	{
		TempSpawnNum = Elem.Value;
		TempSpawnClass = Elem.Key;
		for (size_t i = 0; i < TempSpawnNum; i++)
		{
			MemberReferences.Add(GetWorld()->SpawnActor<AEntity>(TempSpawnClass, Location, Rotation, SpawnInfo));
		}
	}
	MembersAlive = MemberReferences.Num();
}

// Called when the game starts or when spawned
void AMonsterPackSpawner::BeginPlay()
{
	Super::BeginPlay();
	WaitTimer = 0;
	
}

// Called every frame
void AMonsterPackSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (MembersAlive == 0 && SpawnDelay > 0)
	{
		WaitTimer += DeltaTime;
		if (WaitTimer > SpawnDelay)
		{
			WaitTimer = 0;
			//Spawn all the monsters
			SpawnMonsters();
		}
	}
	MembersAlive = 0;
	for (size_t i = 0; i < MemberReferences.Num(); i++)
	{
		if (MemberReferences[i]->Dead == false && MemberReferences[i])
		{
			MembersAlive++;
		}
		//Remove any entity that has wandered far away from the spawner, to make quests lkess buggy, also herding monsters away sound "fun"
		if (GetDistanceTo(MemberReferences[i])>2000)
		{
			MemberReferences[i] = nullptr;
		}
	}

}

