// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity.h"
#include "PublicScripting/NPCHouseDoor.h"
#include "Humanoid.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FSkills
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int OneHanded = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int TwoHanded = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int Polearms = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int LightArmour = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int MediumArmour = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int HeavyArmour = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int Charisma = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int Acrobatics = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int Unarmed = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int Riding = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int Thievery = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int Annihilation = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int Healing = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int MindTrickery = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int MagicalControl = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int Stealth = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int Throwing = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int Archery = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int Block = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int Alchemy = 5;
};

USTRUCT (BlueprintType)
struct FAttribution
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int Strength = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int Endurance = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int Essence = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int Aggresion = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int Personality = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int Dexterity = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int Perception = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int Intelligence = 5;
};

UCLASS()
class EMCGAME_API AHumanoid : public AEntity
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Default")
		TArray<FString> EntityObjects;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool isFemale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FSkills Skills;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FAttribution Attributes;
	//Search in the database which will contain all settlements.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FName Settlement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		ANPCHouseDoor* Home;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool bIsMounted;

	
};
