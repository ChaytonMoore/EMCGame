// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FollowingTextrender.h"
#include "WorldFunctions.generated.h"

/**
 * 
 */
UCLASS()
class EMCGAME_API UWorldFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		UFUNCTION(BlueprintCallable, Category = "cpp script")
		static void InitBeachLevel(UUserWidget* caller);
	UFUNCTION(BlueprintCallable, Category = "cpp script")
		static void InitStreamLevel(UObject* caller,FName Level, TArray<FName> UnloadLevel);
	UFUNCTION(BlueprintCallable, Category = "item")
		static TMap<FString, int> WFChangeMoneyValue(TMap<FString, int> OriginalInventory, float MoneyChange);
	UFUNCTION(BlueprintCallable, Category = "NPC")
		static void SpawnFollwingtextRender(FText TextToSpawn, AActor* Actor, float TimeToLast);
};
