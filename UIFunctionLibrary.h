// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Humanoid.h"
#include "Components/PanelWidget.h"
#include "Engine/DataTable.h"
#include "UIFunctionLibrary.generated.h"

UCLASS()
class EMCGAME_API UUIFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		UFUNCTION(BlueprintCallable, Category = "UI Function")
		static FString childhoodTextGeneration(int stage, int cultureidx, bool gender, FString choice1, int choice2, int choice3, int choice4, int choice1i);
	UFUNCTION(BlueprintCallable, Category = "UI Function")
		static FSkills SkillsInit(int cultureidx, int choice1i, int choice2, int choice3, int choice4);
	UFUNCTION(BlueprintCallable, Category = "UI Function")
		static FAttribution AttributesInit(int cultureidx, int choice1i, int choice2, int choice3, int choice4, bool gender);
	
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Dialogue")
		static bool DialogueCheck(TArray<FString> PlayerNeed, TArray<FString> PlayerCant, TArray<FString> NPCNeed, TArray<FString> NPCCant, TArray<FString> WorldNeed, TArray<FString> WorldCant, TArray<FString> PlayerObjs, TArray<FString> NPCObjs, TArray<FString> WorldObjs);
	
	UFUNCTION(BlueprintCallable, Category = "UI Function")
		static void RemoveChildren(UPanelWidget* ParentObject);

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "UI Function")
		static TArray<FString> DialogueAddRemoveObjs(TArray<FString> MainArray, TArray<FString> AddObjs, TArray<FString> RemoveObjs);

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Merchant Function")
		static float LocalItemPrice(float OriginalPrice, int SellerPersonality, int BuyerPersonality, int SellerIntelligence, int BuyerIntelligence, int SellerCharisma, int BuyerCharisma);
	

	UFUNCTION(BlueprintCallable, Category = "UI Function")
		static void PartiallyRemoveWidget(UUserWidget* Caller);

	UFUNCTION(BlueprintCallable, Category = "UI Function")
		static FText GetQuestTitle(TMap<class UDataTable*, int> Quests, int idx);

	UFUNCTION(BlueprintCallable, Category = "UI Function")
		static FText GetQuestDescription(TMap<class UDataTable*, int> Quests, int idx);
};
