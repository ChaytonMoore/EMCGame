// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Entity.h"
#include "NPCSchedule.generated.h"



UCLASS()
class EMCGAME_API UNPCSchedule : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		//What happens here is that the NPC will call the functions that tells it what to do it will then be feed back those results.

		UFUNCTION(BlueprintCallable, Category = "Behavoir")
		void ScheduleDecider(AEntity* Caller, FString PreviousState, FString NewState);
	
};
