// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Humanoid.h"
#include "Entity.h"
#include "DataBase.h"
#include "Engine/StaticMesh.h"
#include "Particles/ParticleSystem.h"
#include "Materials/Material.h"
#include "Engine/SkeletalMesh.h"
#include "GenericFunctions.generated.h"

/**
 * 
 */

UENUM()
enum SpellType
{
	Annihilation UMETA(DisplayName = "Annihilation"),
	MindTrickery UMETA(DisplayName = "Mind Trickery"),
	MagicalControl UMETA(DisplayName = "MagicalControl"),
	Healing UMETA(DisplayName = "Healing")
};

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

USTRUCT(BlueprintType) //There is also a version of this in blueprints. Should remove it though
struct FArmourStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FString Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		USkeletalMesh* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		USkeletalMesh* FemaleMeshVarient;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		UStaticMesh* HelmetMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool RemoveRespectiveEntityMesh = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		UMaterial* AlternativeMaterial;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int ArmourValue;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FString SoundType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool femaleOnly;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool maleOnly;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int wType;//This is weight class, 1 = light, 2 = medium and 3 = heavy.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool Outfit;
};

UENUM()
enum MeleeAttackTypes
{
	Stopped     UMETA(DisplayName = "1h"),
	Moving      UMETA(DisplayName = "2h"),
	Attacking   UMETA(DisplayName = "polearm")
};

USTRUCT(BlueprintType) //There is also a version of this in blueprints. Should remove it though
struct FWeaponStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FString type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		TEnumAsByte<MeleeAttackTypes> MeleeType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		TSubclassOf<AActor> OnHitEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		float SpeedCoef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FString DamageType;
};


USTRUCT(BlueprintType) //There is also a version of this in blueprints.
struct FMagicSpellFXStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		TSubclassOf<ABaseSpell> FXscript;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int FXCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int FXEssence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		TArray<TSubclassOf<UParticleSystem>> Particles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		TEnumAsByte<SpellType> Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool InvisibleComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FText Desc;

};


USTRUCT(BlueprintType) //There is also a version of this in blueprints.
struct FMagicSpellStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		TArray<FMagicSpellFXStruct> Effects;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int FXCostOveride;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int FXEssenceOveride;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		TEnumAsByte<SpellType> Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		TMap<TEnumAsByte<SpellType>, int> SkillReq;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		int LevelReq;
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

USTRUCT(BlueprintType)
struct FItemStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		float value;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		UStaticMesh* mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool usable; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FString type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool dropable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FName weaponRef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FName armourRef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		AActor* Script;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		UMaterial* AltMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		float Weight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		USkeletalMesh* AltSK;

};

UCLASS()
class EMCGAME_API UGenericFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


public:
		UFUNCTION(BlueprintCallable, Category = "item")
		static bool PlayerPickingUp (AActor* caller,bool overlaping);
	UFUNCTION(BlueprintCallable, Category = "item")
		static TMap<FString, int> AddItemToInventory(TMap<FString, int> Inventory, FString Item, int Number);
	//UFUNCTION(BlueprintPure, Category = "Actor", meta = (DefaultToSelf = Target))
		//static AHumanoid* GetPlayerHumanoid();
	//UFUNCTION(BlueprintCallable, Category = "Actor")
		//static AHumanoid* getPlayerH();

	UFUNCTION(BlueprintPure,BlueprintCallable, Category = "item")
		static ADataBase* GetDataBase(UObject* Caller);

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

	UFUNCTION(BlueprintCallable, Category = "NPC")
		static void TeleportPlayer(AActor* Location);

	UFUNCTION(BlueprintCallable, Category = "NPC")
		static void TeleportPlayerParams(AActor* Location, float MagicChange, float StaminaChange, float HealthChange);
	
	UFUNCTION(BlueprintCallable, Category = "NPC")
		static bool TryTeleportPlayer(AActor* Location, float MagicChange, float StaminaChange, float HealthChange);

	UFUNCTION(BlueprintCallable, Category = "NPC")
		static bool SimpleEntityMoveScript(AEntity* EntityToMove, FVector Location, bool IgnoreAgro);

	UFUNCTION(BlueprintCallable, Category = "NPC")
		static bool CanCastSpell(FMagicSpellStruct spell, AHumanoid* Caller);

	UFUNCTION(BlueprintCallable, Category = "NPC")
		static int SpellCost(FMagicSpellStruct spell);

	UFUNCTION(BlueprintCallable, Category = "NPC")
		static bool CastSpell(FMagicSpellStruct spell, AHumanoid* Caller,FRotator DesiredRotation); //Will need to check to see if this succedes, if it doesn't play a sound or something in the blueprints.


	UFUNCTION(BlueprintCallable, Category = "NPC")
		static bool HealEntity(AEntity* Caller, float amount);


	UFUNCTION(BlueprintCallable, Category = "NPC")
		static bool RestoreStaminaEntity(AEntity* Caller, float amount);

	UFUNCTION(BlueprintCallable, Category = "NPC")
		static bool RestoreEssenceEntity(AEntity* Caller, float amount);


	UFUNCTION(BlueprintCallable, Category = "NPC")
		static void CalculateStats(AHumanoid* Caller);

	UFUNCTION(BlueprintCallable, Category = "Utility")
		static TArray<FString> RemoveElementsFromArrayString(TArray<FString> Main, TArray<FString> Remove);

	UFUNCTION(BlueprintCallable, Category = "Utility")
		static void MagicAtZeroRefil(AHumanoid* Caller);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utility")
		static FRotator AddRotator(FRotator first, FRotator second);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utility")
		static int SumInt(TArray<int> values);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utility")
		static bool ApproxFloat(float a, float b);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utility")
		static FVector RandomVectorInRadius(FVector Start, int Radius);//Not for AI

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utility")
		static bool HasSimilarString(TArray<FString> a,TArray<FString> b);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utility")
		static TArray<AActor*> PureRemoveItem(TArray<AActor*> list, AActor* item);

	UFUNCTION(BlueprintCallable,  Category = "NPC")
		static void SetNPCHumanHealthOnAttack(AHumanoid* Human, float Damage, class UDataTable* Armour);

	UFUNCTION(BlueprintCallable, Category = "NPC")
		static float HealthFromAttack(class UDataTable* Items, class UDataTable* Weapons, class UDataTable* Armour, AHumanoid* Attacker, AHumanoid* Defender);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utility")
		static AEntity* NearestEntity(TArray<AEntity*> Entities, AActor* selfRef);

	UFUNCTION(BlueprintCallable, Category = "Utility")
		void Reinitconstructor(AActor* toReinit);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utility")
		static AActor* GetNearestActor(AActor* selfRef, TArray<AActor*> Others);

	//UFUNCTION()
		//int Randint(int low, int high);
};
