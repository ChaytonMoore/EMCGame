// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity.h"


TMap<FString, int> AddItemToInventory(TMap<FString, int> Inventory, FString Item, int Number)
{
	if (Inventory.Contains(Item)) {
		int* tmpVal = Inventory.Find(Item);
		Inventory.Remove(Item);
		Inventory.Add(FString(Item), (*tmpVal) + Number);
	}
	else {
		Inventory.Add(FString(Item), Number);
	}
	return TMap<FString, int>(Inventory);
}

// Sets default values
AEntity::AEntity()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

TMap<FString, int> AEntity::DefaultMerchantRefillInventory(TMap<FString, int> InitalInventory,TArray<FString> MerchantTags)
{
	if (MerchantTags.Contains("Farmer"))
	{
		//InitalInventory = AddItemToInventory(InitalInventory, "bread", rand() % 6); //Won't do it like this, could accumulate will just reset
		//InitalInventory = AddItemToInventory(InitalInventory, "wildberries", rand() % 2);
		InitalInventory.Add("bread",rand() % 8 ); //While I want a working econemy, this might be better.
		InitalInventory.Add("apple", rand() % 4);
		InitalInventory.Add("wildberries", rand() % 2);
		InitalInventory.Add("salt", rand() % 1);
	}

	if (MerchantTags.Contains("poor")) 
	{
		InitalInventory.Add("penny", 15 + rand() % 10);
		InitalInventory.Add("shilling", 4 + rand() % 6);
		InitalInventory.Add("mankas", rand() % 3);
	}
	else if (MerchantTags.Contains("rich"))
	{
		InitalInventory.Add("penny", 45 + rand() % 12);
		InitalInventory.Add("shilling", 14 + rand() % 10);
		InitalInventory.Add("mankas", 6 + rand() % 8);
	}
	else //Else assume the merchant is of average wealth
	{
		InitalInventory.Add("penny", 25 + rand() % 15);
		InitalInventory.Add("shilling", 8 + rand() % 12);
		InitalInventory.Add("mankas", 1+ rand() % 5);
	}

	if (MerchantTags.Contains("general"))
	{
		InitalInventory.Add("shirt", 2 + rand() % 3);
		InitalInventory.Add("clothcoif", rand() % 3);
	}

	return TMap<FString, int>(InitalInventory);
}

// Called when the game starts or when spawned
void AEntity::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
//void AEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

//}

