// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity.h"
#include "Quadraped.generated.h"

/**
 * 
 */

UCLASS()
class EMCGAME_API AQuadraped : public AEntity
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		TArray<AQuadraped*> Group;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool grazing = true;
	//Will have variable for group even if a lone creature

protected:
	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "NPC")
		TArray<AEntity*> GetEnemiesinRadius(float Radius);
	UFUNCTION(BlueprintCallable, Category = "NPC")
		void RunFromEnemies(TArray<AEntity*> Enemies);

};
