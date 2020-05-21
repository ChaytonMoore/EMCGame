// Fill out your copyright notice in the Description page of Project Settings.


#include "SettlementNode.h"
#include "Containers/Map.h"
#include "Engine/DataTable.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"
#include "UObject/NameTypes.h"
#include "GenericFunctions.h"
#include <cmath>

// Sets default values


//I think I'll have to create a struct in C++ for the items.


ASettlementNode::ASettlementNode()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASettlementNode::BeginPlay()
{
	Super::BeginPlay();
	//GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &RecalculateLocalEconemy(), 240.0f, true, 360.0f);
	
}



// Called every frame
void ASettlementNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float GetEntityMoneyValue(AEntity * Entity)
{
	float Output = 0;
	Output += 0.1 * Entity->Inventory.FindRef(FString("penny"));
	Output += 1.2 * Entity->Inventory.FindRef(FString("shilling"));
	Output += 36 * Entity->Inventory.FindRef(FString("mankas"));

	return Output;
}

float ASettlementNode::FindFoodCoef(TArray<AGoodsStore*> StorePlaces, TArray<AHumanoid*> People) //What this does is find the price which food should be sold at. We can assume that to some degree everyone has access to all food and it's really how long the food would last.
{
	//Importing the items database.
	static ConstructorHelpers::FObjectFinder<UDataTable> ItemDatabase(TEXT("DataTable'/Game/Mechanics/items/InventoryItems.InventoryItems'"));
	float output = 1; //I think I'll make it so that price also depends on average wealth. It might be a good idea to divide up larger settlements if they exist and make sure there are connections.
	TMap<FString, int> TempItems;
	TArray<FString> TempKeys;
	TArray<int> TempValues;
	int FoodNumber = 0;

	UDataTable* DataTable;

	DataTable = ItemDatabase.Object;

		//I think we'll take each food type to be equal. We'll take a person to need 6 pieces of food a day.
	TArray<FName> Rows;
	FItemsCPP TableRow;

	Rows = DataTable->GetRowNames();
	FItemsCPP* TempRow;
	static const FString ContextDataString(TEXT("Settlement readjust food value based on amount of food in stores")); //Nobody actually has any idea what this is for but it is needed.
	TArray<FString> FoodTypes;
	for (size_t i = 0; i < Rows.Num(); i++)
	{
		TempRow = DataTable->FindRow<FItemsCPP>(Rows[i],ContextDataString,true);
		if (TempRow->type == FString("food")) {
			FoodTypes.Add(Rows[i].ToString());
		}
		//so know I know what type of things can be food. This means that it can be dynamic.

	}

	for (size_t i = 0; i < StorePlaces.Num(); i++)
	{
		TempItems = StorePlaces[i]->Items;
		TempItems.GetKeys(TempKeys);
		TempItems.GenerateValueArray(TempValues);
		for (size_t j = 0; j < TempKeys.Num(); j++ ) 
		{
			if (FoodTypes.Contains(TempKeys[i])) {
				FoodNumber += TempValues[i];
			}

		}


	}
	//We should now have all the food items, I should probably find a better way of doing this but I'll make that a generic function.

	float FoodLast;
	FoodLast = FoodNumber / (People.Num()*7); //People eat 7 food things a day on average this might need to be changed as I do plan to make this a gameplay element.
	//the price coefficient can then be determined based on number of days left.
	//>3 they almost definitly won't sell
	//>7 will sell for a lot
	//> 21 normal range
	// > 40 very cheap
	//^ these are only general guide lines and will be found in other ways.
	
	//The average wealth of the people in the settlement will need to be found.
	float Wealth = 0;
	for (size_t i = 0; i < People.Num(); i++)
	{
		Wealth += GetEntityMoneyValue(People[i]);
	}
	Wealth = Wealth / People.Num();
	//Now the average wealth will be very hard to know right now but I'll try to get some values now.
	// < 10 very poor
	// < 50 poor
	// < 100 average
	// < 250 rich
	// < 600 very rich obviosuly richer places will sell stuff for more but it shouldn't be particularily significant compared to scarsity.
	//The equation (1/(1+e^(-x/100)))+0.8 all over 2 seems to work. Using the exact value of e isn't necesarry.
	float WealthCoef = 0 - (Wealth / 100); WealthCoef = std::pow(2.72, WealthCoef); WealthCoef = 1 / (1 + WealthCoef); WealthCoef = std::pow(WealthCoef, 2) / 2;
	FoodLast = (1/(0.08*FoodLast));
	//^Yes this is strange but pow is strange
	output = WealthCoef * FoodLast;

	return output;
}

