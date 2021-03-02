// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Entity.h"
#include "LevelOwnership.generated.h"

UCLASS()
class EMCGAME_API ALevelOwnership : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelOwnership();
	UPROPERTY(EditAnywhere)
		AEntity* SpaceOwner;
	UPROPERTY(EditAnywhere)
		TArray<FString> AllowedFactions;
	UPROPERTY(EditAnywhere)
		int Security; //0 = non, 1 = go away, 2= immediatly illegal. Might not be included, no idea how level transition for guards is going to work.

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
