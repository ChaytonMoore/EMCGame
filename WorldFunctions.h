#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
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
};
