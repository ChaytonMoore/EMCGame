// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoodsStore.h"
#include "Humanoid.h" //This is only because human is a blueprint class so can't be referenced here easily.
#include "Materials/Material.h"
#include "SettlementNode.generated.h"


USTRUCT(BlueprintType)
struct FItemsCPP
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		FText Name;
	UPROPERTY(EditAnywhere)
		FText Description;
	UPROPERTY(EditAnywhere)
		float value;
	UPROPERTY(EditAnywhere)
		UStaticMesh* mesh;
	UPROPERTY(EditAnywhere)
		bool usable;
	UPROPERTY(EditAnywhere)
		FString type;
	UPROPERTY(EditAnywhere)
		bool dropable;
	UPROPERTY(EditAnywhere)
		FName weaponRef;
	UPROPERTY(EditAnywhere)
		FName armourRef;
	UPROPERTY(EditAnywhere)
		AActor* Script;
	UPROPERTY(EditAnywhere)
		UMaterial* AltMaterial;
	UPROPERTY(EditAnywhere)
		float weight;

};

UCLASS()
class EMCGAME_API ASettlementNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASettlementNode();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FString name = "Unnamed";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FString ownerEntity = "Unclaimed";

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		TArray<AGoodsStore*> GoodsStores; //This will be used to calculate the overall price of items in an area.

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default") //These will be coefficients for the prices of the trade goods.
		float FoodCoef; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default") //This basicly only exists so prices can be found.
		TArray<AHumanoid*> Residents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		float EquipmentCoef; //Armour and weapons

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		float LiveStockCoef; //No idea if I'll use this, if so it'll most likely just be for horses.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		float PropertyCoef; //Buying a house would be a nice thing but no idea if I need to look at the markets to decide on the price.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		float MiscCoef; //Everything else

	//void RecalculateLocalEconemy();
	//FTimerHandle MemberTimerHandle;
	UFUNCTION(Category = "item")
		static float FindFoodCoef(TArray<AGoodsStore*>StorePlaces,TArray<AHumanoid*> People);



};
