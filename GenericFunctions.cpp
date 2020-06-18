// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericFunctions.h"
#include "CoreMinimal.h"
#include "Engine.h"
#include "EngineMinimal.h"
#include "Engine/World.h"
#include "..\Public\GenericFunctions.h"
#include "UObject/NameTypes.h"

bool UGenericFunctions::PlayerPickingUp(AActor* caller, bool overlaping)
{
	//caller->GetWorld()->GetFirstPlayerController->GetPawn();
	return false;
}

TMap<FString, int> UGenericFunctions::AddItemToInventory(TMap<FString, int> Inventory, FString Item, int Number)
{
	if (Number > 0)
	{


		if (Inventory.Contains(Item)) {
			int* tmpVal = Inventory.Find(Item);
			Inventory.Remove(Item);
			Inventory.Add(FString(Item), (*tmpVal) + Number);
		}
		else {
			Inventory.Add(FString(Item), Number);
		}
	}
	return TMap<FString, int>(Inventory);
}

ADataBase * UGenericFunctions::GetDataBase(AActor* Caller)
{
	TArray<AActor*> OutputList; //This function requires an input it will crash if it doesn't have one.
	UGameplayStatics::GetAllActorsOfClass(Caller->GetWorld(),ADataBase::StaticClass(),OutputList);
	ADataBase* TempDataBase;
	ADataBase* Output = nullptr;
	for (size_t i = 0; i < (OutputList.Num()); i++)
	{
		TempDataBase = (ADataBase*)OutputList[i];
		if (! TempDataBase->bBackup)
		{
			Output = TempDataBase;
		}

		if (Output == nullptr)
		{
			Output = (ADataBase*)OutputList[0];  
		}
	}
	//This means that a scenario where there is no database doesn't crash the game.
	return Output;
}

float UGenericFunctions::GetEntityMoneyValue(AEntity * Entity)
{
	float Output = 0;
	Output += 0.1 * Entity->Inventory.FindRef(FString("penny"));
	Output += 1.2 * Entity->Inventory.FindRef(FString("shilling"));
	Output += 36 * Entity->Inventory.FindRef(FString("mankas")); //Yes it is a strange money system.

	return Output;
}

TMap<FString, int> UGenericFunctions::ChangeMoneyValue(TMap<FString, int> OriginalInventory, float MoneyChange)
{
	//Just the integer amount as it has been multiplied by 10
	//I think the maths above should work.
	if (MoneyChange < 0)
	{
		int IntMoney = abs(MoneyChange * 10);
		int MankasNum = div(MoneyChange, 360).quot;
		int ShillingNum = div(div(MoneyChange, 360).rem, 12).quot;
		int PennyNum = IntMoney - (MankasNum * 360 + ShillingNum * 12);

		OriginalInventory = RemoveItemFromInventory(OriginalInventory, "mankas", MankasNum);
		OriginalInventory = RemoveItemFromInventory(OriginalInventory, "shilling", ShillingNum);
		OriginalInventory = RemoveItemFromInventory(OriginalInventory, "penny", PennyNum);
		//Remove each item from inventory
	}
	else
	{
		int IntMoney = MoneyChange * 10;
		int MankasNum = div(MoneyChange, 360).quot;
		int ShillingNum = div(div(MoneyChange, 360).rem, 12).quot;
		int PennyNum = IntMoney - (MankasNum * 360 + ShillingNum * 12);

		OriginalInventory = AddItemToInventory(OriginalInventory, "mankas", MankasNum);
		OriginalInventory = AddItemToInventory(OriginalInventory, "shilling", ShillingNum);
		OriginalInventory = AddItemToInventory(OriginalInventory, "penny", PennyNum);
	}

	return TMap<FString, int>(OriginalInventory);
}

void UGenericFunctions::EatSimpleFood(AEntity * Caller)
{
	Caller->Health = Caller->Health + 5;
	Caller->Stamina = Caller->Stamina - 4;
	if (Caller->Health>Caller->MaxHealth)
	{
		Caller->Health = Caller->MaxHealth;
	}
	if (Caller->Stamina<0)
	{
		Caller->Stamina = 0;
	}
}

TMap<FString, int> UGenericFunctions::RemoveItemFromInventory(TMap<FString, int> Inventory, FString Item, int Number)
{
	if (Inventory.Contains(Item)) //Why would I be removing this just won't work.
	{
		int idxnum = *(Inventory.Find(Item));

		if (Number >= idxnum)
		{
			Inventory.Remove(Item);
		}
		else
		{
			Inventory.Remove(Item);
			Inventory.Add(FString(Item),idxnum-Number);
		}

	}


	return TMap<FString, int>(Inventory);
}

bool UGenericFunctions::RenameEntity(AEntity * Caller, FText NewName)
{
	bool SameName = false;
	//You can't compare FText so they have to be turned to strings. FText is weird, mainly because it can be translated into different languages, would hope it doesn't crash in a symbolic language etc.
	if (Caller->Name.ToString() == NewName.ToString()) 
	{
		SameName = true;
	}
	
	Caller->Name = NewName;

	return SameName;
}

void UGenericFunctions::InitNoviceMage(AHumanoid * Caller)
{
	//Chooses whether the novice will be male or female, more likely to be male.
	int iChoice = rand() % 10;
	if (iChoice > 5)
	{
		Caller->isFemale = true;
	}

	//It will return the mage's highest skill is as its type.
	Caller->Attributes.Essence = rand() % 10 + 10;
	Caller->Attributes.Intelligence = rand() % 15 + 5;


	Caller->Skills.Alchemy = rand() % 25 + 5;
	Caller->Skills.Annihilation = rand() % 25 + 5;
	Caller->Skills.Healing = rand() % 25 + 5;
	Caller->Skills.MagicalControl = rand() % 25 + 5;
	Caller->Skills.MindTrickery = rand() % 20;
	Caller->Skills.OneHanded = rand() % 5 + 5;

	FString Output;
	if (Caller->Skills.Alchemy > Caller->Skills.Annihilation && Caller->Skills.Alchemy > Caller->Skills.Healing && Caller->Skills.Alchemy > Caller->Skills.MagicalControl && Caller->Skills.Alchemy > Caller->Skills.MindTrickery)
	{
		Caller->EntityTags.Add("Alchemist");
	}
	else if (Caller->Skills.Annihilation > Caller->Skills.Alchemy && Caller->Skills.Annihilation > Caller->Skills.Healing && Caller->Skills.Annihilation > Caller->Skills.MagicalControl && Caller->Skills.Annihilation > Caller->Skills.MindTrickery)
	{
		Caller->EntityTags.Add("BattleMage");
	}
	else if (Caller->Skills.Healing > Caller->Skills.Alchemy && Caller->Skills.Healing > Caller->Skills.Annihilation && Caller->Skills.Healing > Caller->Skills.MagicalControl && Caller->Skills.Healing > Caller->Skills.MindTrickery)
	{
		Caller->EntityTags.Add("Healer");
	}
	else if (Caller->Skills.MagicalControl > Caller->Skills.Alchemy && Caller->Skills.MagicalControl > Caller->Skills.Healing && Caller->Skills.MagicalControl > Caller->Skills.Annihilation && Caller->Skills.MagicalControl > Caller->Skills.MindTrickery)
	{
		Caller->EntityTags.Add("Alterer");
	}
	else
	{
		Caller->EntityTags.Add("Illusionist");
	}

}

void UGenericFunctions::EntityRestoreHealth(AEntity * Caller)
{
	Caller->Health = Caller->MaxHealth;
}

bool UGenericFunctions::EntityHealTick(AEntity * Caller)
{
	//Returns true when it is full such that it can be stopped.
	bool Output = false;
	if (Caller->Health + 1 <= Caller->MaxHealth)
	{
		Caller->Health += 1;
	}
	else
	{
		Output = true;
	}
	return Output;
}








//AHumanoid * UGenericFunctions::GetPlayerHumanoid()
//{
//	AHumanoid* Output = Cast<AHumanoid>(UGameplayStatics::GetPlayerPawn);
	//return AHumanoid* (Output);
//}

//AHumanoid * UGenericFunctions::getPlayerH()
//{
	//AHumanoid* Output = Cast<AHumanoid>(UGameplayStatics::GetPlayerPawn());
	//UGameplayStatics::GetPlayerCharacter((GEngine->GetWorldContexts()[0].World()),0);
	//return nullptr;
//}


