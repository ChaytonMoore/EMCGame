// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Scripting/PointObject.h"
#include "FarmingNode.generated.h"

/**
 * 
 */
UCLASS()
class EMCGAME_API AFarmingNode : public APointObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FString ActivityType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FName OwnerSettlement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool isRotationRelavent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool isOccupied;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		AActor* User;

};
