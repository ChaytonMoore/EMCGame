// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataBase.h"
#include "PublicScripting/NPCHouseDoor.h"
#include "BarracksDoor.generated.h"

/**
 * 
 */
UCLASS()
class EMCGAME_API ABarracksDoor : public ANPCHouseDoor
{
	GENERATED_BODY()
		ABarracksDoor();
public:
	UPROPERTY(EditAnywhere)
		int GuardNumber;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> GuardType;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
		ADataBase* DataBase;
	UFUNCTION()
		void DelayedSpawnGuard();
	UPROPERTY()
		bool bSpawnerOccupied = false;

};
