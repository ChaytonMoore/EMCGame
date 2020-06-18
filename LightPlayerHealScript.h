// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightPlayerHealScript.generated.h"

UCLASS()
class EMCGAME_API ALightPlayerHealScript : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightPlayerHealScript();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
		int IterationCount = 0;
	UFUNCTION()
		void IterateHeal();



};
