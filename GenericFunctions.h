// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Humanoid.h"
#include "DataBase.h"
#include "GenericFunctions.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType) //There is also a version of this in blueprints.
struct FBookStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (MultiLine = true))
		FText Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		TSubclassOf<AActor> Script;

};

USTRUCT(BlueprintType)
struct FQuestStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FText Name; //First row only I think
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int XPReward; //Really only for the last piece.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FString QuestType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FText Stage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		TSubclassOf<AActor> ScriptActor;

};


UCLASS()
class EMCGAME_API UGenericFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		UFUNCTION(BlueprintCallable, Category = "item")
		static bool PlayerPickingUp (AActor* caller,bool overlaping);
	UFUNCTION(BlueprintCallable, Category = "item")
		static TMap<FString, int> AddItemToInventory(TMap<FString, int> Inventory, FString Item, int Number);
	//UFUNCTION(BlueprintPure, Category = "Actor", meta = (DefaultToSelf = Target))
		//static AHumanoid* GetPlayerHumanoid();
	//UFUNCTION(BlueprintCallable, Category = "Actor")
		//static AHumanoid* getPlayerH();

	UFUNCTION(BlueprintPure,BlueprintCallable, Category = "item")
		static ADataBase* GetDataBase(AActor* Caller);

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "item")
		static float GetEntityMoneyValue(AEntity* Entity);

	UFUNCTION(BlueprintCallable, Category = "item")
		static TMap<FString, int> ChangeMoneyValue(TMap<FString, int> OriginalInventory, float MoneyChange);

	UFUNCTION(BlueprintCallable, Category = "item")
		static void EatSimpleFood(AEntity* Caller);

	UFUNCTION(BlueprintCallable, Category = "item")
		static TMap<FString, int> RemoveItemFromInventory(TMap<FString, int> Inventory, FString Item, int Number);

	UFUNCTION(BlueprintCallable, Category = "NPC")
		static bool RenameEntity(AEntity* Caller, FText NewName);

	UFUNCTION(BlueprintCallable, Category = "NPC")
		static void InitNoviceMage(AHumanoid* Caller);

	UFUNCTION(BlueprintCallable, Category = "NPC")
		static void EntityRestoreHealth(AEntity* Caller);

	UFUNCTION(BlueprintCallable, Category = "NPC")
		static bool EntityHealTick(AEntity* Caller);

};
