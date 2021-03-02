// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericCollider.h"
#include "PlayerComment.generated.h"

/**
 * 
 */
UCLASS()
class EMCGAME_API APlayerComment : public AGenericCollider
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Default")
		TArray<FText> Speech;
	UPROPERTY(EditAnywhere, Category = "Default")
		TArray<float> Times;

	UPROPERTY(EditAnywhere, Category = "Default")
		TArray<FString> PlayerNeeds;
	UPROPERTY(EditAnywhere, Category = "Default")
		TArray<FString> PlayerCant;
	UPROPERTY(EditAnywhere, Category = "Default")
		TArray<FString> WorldNeeds;
	UPROPERTY(EditAnywhere, Category = "Default")
		TArray<FString> WorldCant;
	UPROPERTY(EditAnywhere, Category = "Default")
		TArray<FString> WorldAdd;
	UPROPERTY(EditAnywhere, Category = "Default")
		TArray<FString> WorldRemove;
	UPROPERTY(EditAnywhere, Category = "Default")
		TArray<FString> PlayerAdd;
	UPROPERTY(EditAnywhere, Category = "Default")
		TArray<FString> PlayerRemove;

public:

		virtual void PlayerCollide() override;
};
