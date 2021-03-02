// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "UObject/ConstructorHelpers.h"
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

USTRUCT(BlueprintType) //There is also a version of this in blueprints.
struct FFactionStruct : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		TArray<FString> EnemyFactions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		TArray<FString> AlliedFactions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FString DevDescription;
};

UCLASS()
class EMCGAME_API AEntity : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEntity();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		UPawnSensingComponent* SensingComponent;

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
		bool Dead;
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
		bool activate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FString TransportString;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FString State = "None";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		TArray<FString> EntityTags;
	UFUNCTION()
		TMap<FString, int> DefaultMerchantRefillInventory(TMap<FString, int> InitalInventory, TArray<FString> MerchantTags);

	UFUNCTION(BlueprintCallable, Category = "NPC")
		void RandomShortWalkAround();

	UFUNCTION(BlueprintCallable, Category = "NPC")
		void RandomLongWalkAround();

	UFUNCTION(BlueprintCallable, Category = "NPC")
		void EnterDialogueMotion();

	UFUNCTION(BlueprintCallable, Category = "NPC")
		bool GotoRandomFarmingNode();

	UFUNCTION(BlueprintCallable, Category = "NPC")
		bool SimpleEntityMoveToLocation(FVector Location);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "NPC")
		float FindSafetyofPoint(TArray<AEntity*> Enemies, FVector Position);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utility")
		bool isEntityMoving();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "NPC")
		void BlueprintNPCCombatTick();

	UFUNCTION(BlueprintCallable, Category = "NPC")
		void NPCCombatTick();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FString ActiveSpell;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool inDialogue = true;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FName Settlement;
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "NPC")
		void ExecuteOnDeath();

	UFUNCTION(BlueprintCallable, Category = "NPC")
		AEntity* FindNearestEntityNotinFaction(float SphereSize);

	UFUNCTION(BlueprintCallable, Category = "NPC")
		TArray<AEntity*> GetNearByEntities(float SphereSize);

	UFUNCTION(BlueprintCallable, Category = "NPC")
		TArray<AEntity*> GetEnemiesFromEntites(TArray<AEntity*> Entities);

	UFUNCTION(BlueprintCallable, Category = "NPC")
		TArray<AEntity*> GetAlliesFromEntites(TArray<AEntity*> Entities);

	UFUNCTION(BlueprintCallable, Category = "NPC")
		void MonsterProwl(float radius);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool isAttacking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		AEntity* AIAttackTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		TArray<AEntity*> AITargets;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "NPC")
		bool CalculateFightOrFlight(TArray<AEntity*> Allies, TArray<AEntity*> Enemies);

	UFUNCTION(BlueprintCallable, Category = "NPC")
		void RunAway();

	UFUNCTION(BlueprintCallable, Category = "NPC")
		bool LocationNearEntity(FVector Location, float Distance, TArray<AEntity*> Entities);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (AllowPrivateAccess = "true"))
		float FallDamageValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (AllowPrivateAccess = "true"))
		bool DeathSinking;

	UFUNCTION(BlueprintCallable, Category = "NPC")
		void AIStateHandling();

	UFUNCTION(BlueprintCallable, Category = "NPC")
		void AIResponce();

	UFUNCTION(BlueprintCallable, Category = "NPC")
		bool AgroCheck();

	UPROPERTY(EditAnywhere, Category = "Default")
		class UDataTable* FactionData;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



};
