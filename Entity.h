// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Entity.generated.h"


//Here are the structures for magic. Spell struct and the fx struct
//fx struct

USTRUCT(BlueprintType) //I might try to see if it is possible to have a BP struct identitcle to this one and let them interact.
struct FSpellFX
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> FXscript;
	UPROPERTY(EditAnywhere)
		int FXCost;
	UPROPERTY(EditAnywhere)
		int FXEssence;
	UPROPERTY(EditAnywhere)
		TArray<UParticleSystem*> Particles;
	UPROPERTY(EditAnywhere)
		FText Name;
};

USTRUCT(BlueprintType)
struct FSpell
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
		TArray<FSpellFX> Effects;
	UPROPERTY(EditAnywhere) //These are only meant to be used as an override.
		int FXCostOveride;
	UPROPERTY(EditAnywhere)
		int FXEssenceOveride;
	UPROPERTY(EditAnywhere)
		FString Type;
	UPROPERTY(EditAnywhere)
		int SkillReq;
	UPROPERTY(EditAnywhere)
		int LevelReq;
	UPROPERTY(EditAnywhere)
		FText Name;

};

UCLASS()
class EMCGAME_API AEntity : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEntity();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		float Stamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		float MaxStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		float Magic;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		float MaxMagic;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool ExposeInventoryOnDeath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int TotalXP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		TArray<FString> Spells;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		TMap<FString, int> Inventory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		TMap<FString, int> Factions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool Agro;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FString TransportString;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FString State = "None";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		TArray<FString> EntityTags;
	UFUNCTION()
		TMap<FString, int> DefaultMerchantRefillInventory(TMap<FString, int> InitalInventory, TArray<FString> MerchantTags);
	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



};
