// Fill out your copyright notice in the Description page of Project Settings.


#include "Humanoid.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "NavigationSystem.h"
#include "Components/SkeletalMeshComponent.h"
#include "GenericFunctions.h"
#include "Engine/DataTable.h"
#include "Containers/Array.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/EngineTypes.h"
#include "Components/StaticMeshComponent.h"
#include "Containers/Map.h"
#include "GenericFunctions.h"


AHumanoid::AHumanoid()
{
	PrimaryActorTick.bCanEverTick = true;
	//Creating the two equipment slot objects
	ObjectRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Equipment Slot"));
	ObjectLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Equipment Slot"));
	//Attaching them to the mesh
	ObjectLeft->SetupAttachment(GetMesh());
	ObjectLeft->AttachToComponent(Mesh,FAttachmentTransformRules::KeepRelativeTransform);
	ObjectRight->AttachToComponent(Mesh, FAttachmentTransformRules::KeepWorldTransform, TEXT("Bone_019"));
	ObjectRight->SetupAttachment(Mesh);
	//ObjectRight->AttachTo();
	//Get the data table
	static ConstructorHelpers::FObjectFinder<UDataTable>ItemsRef(TEXT("DataTable'/Game/Mechanics/items/InventoryItems2.InventoryItems2'"));
	UDataTable* items;
	

	if (ItemsRef.Succeeded())
	{
		items = ItemsRef.Object;
		
		//EquipmentRight = "ironsword";
		FItemStruct* objectDataR = items->FindRow<FItemStruct>(EquipmentRight, "", true);
		
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("the table is found"));
		//TArray<FName> rnames = items->GetRowNames();
		//for (int i = 0; i < rnames.Num(); i++)
		//{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("My Name: %s"), *rnames[i].ToString());
		//}
		//if (rnames.Contains(EquipmentRight))
		//{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("contains item"));
		//}
		//else
		//{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("My Name: %s"), *EquipmentRight.ToString());
		//}
		//EquipmentLeft = "ironsword";
		if (objectDataR)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("the row is found"));
			if (objectDataR->mesh)
			{
				ObjectRight->SetStaticMesh((*objectDataR).mesh);
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("something should happen"));
			}
		}
		FItemStruct* objectDataL = items->FindRow<FItemStruct>(EquipmentLeft, "", true);
		if (objectDataL)
		{
			if (objectDataL->mesh)
			{
				ObjectLeft->SetStaticMesh(objectDataL->mesh);
			}
		}
		//The if statements are just validation, otherwise it causes an error because sometimes null objects will exist.
	}

	
}


//This will only be executed as long as the entity is not agro.
void AHumanoid::SimpleActivity()
{
	if (EntityTags.Contains("Farmer"))
	{
		//For all that the person does will be executed every so often.
		if (UGenericFunctions::GetDataBase(this)->isNight)
		{
			//When it is night they will go to bed, which usually invovles going to their house and disappearing all night.
			if (State != "Sleeping" && State != "GoingToSleep")
			{
				State = "GoingToSleep";
			}
		}
		else
		{
			//When it is day it'll check to see if the entity is going to sleep
			if (State == "Sleeping" || State == "GoingToSleep")
			{
				State = "Waking";
				//A state where they walk around near to themselves randomly for a short while.
			}
			if (State == "Waking")
			{
				//Now the state will be set to farming
				State = "Farming";
			}
		}
	}
}


void AHumanoid::DocileWalk(float radius)
{
	//Choose an appropriate location and then move there.
	UNavigationSystemV1* NavSystem;
	NavSystem = UNavigationSystemV1::GetCurrent(this);
	FNavLocation RandomLocation;
	NavSystem->GetRandomReachablePointInRadius(this->GetActorLocation(), 2250.0f, RandomLocation);
	SimpleEntityMoveToLocation(RandomLocation);
}

FText AHumanoid::ChooseInteractDialogue()
{
	FText Output;
	TArray<int> values = FAmbientInteractDialogue::ComposeIntArray(PlayerInteractDialogueAmbient);
	if (UGenericFunctions::SumInt(FAmbientInteractDialogue::ComposeIntArray(PlayerInteractDialogueAmbient)) > 0)
	{
		int randomNum = rand() % (UGenericFunctions::SumInt(FAmbientInteractDialogue::ComposeIntArray(PlayerInteractDialogueAmbient)));
		int idx = 0;
		while (randomNum > 0)
		{
			randomNum -= values[idx];
			if (randomNum <= 0)
			{
				idx += 1;
			}
		}
		Output = PlayerInteractDialogueAmbient[idx].Dialogue;
	}

	return Output;
}

float AHumanoid::AmbientDLGTimeToSay(FText ElementDialogue)
{
	float output = 4;
	for (size_t i = 0; i < PlayerInteractDialogueAmbient.Num(); i++)
	{
		if (PlayerInteractDialogueAmbient[i].Dialogue.ToString() == ElementDialogue.ToString())
		{
			output = PlayerInteractDialogueAmbient[i].TimeToSay;
			break;
		}
	}

	return output;
}

FString AHumanoid::GoblinTickEvent()
{
	
	return State;
}


bool AHumanoid::CanSeeEntity(AHumanoid* looker, AHumanoid* seen)
{
	float SeenCoef;
	SeenCoef = (seen->Attributes.Dexterity + seen->Skills.Acrobatics + seen->Skills.Stealth * 5)/((float)(looker->Attributes.Perception*5 + looker->Skills.MagicalControl + looker->Skills.Stealth));
	SeenCoef = SeenCoef * ((seen->GetActorLocation() - looker->GetActorLocation()).Size()/( 1200 + looker->Attributes.Perception * 10)); //1 so no divide by 0
	
	return  SeenCoef < 1; // SeenCoef < 1;
}

void AHumanoid::OnDeathParamsHumanoid(AHumanoid* Attacker)
{
	//First declare the humanoid as dead.
	Dead = true;
	//Now the attacker needs to get their well earned xp
	//The equation is (TotalXP+ attacker aggresion) *( def str/attacker str)*(def int/attacker int)  , such that killing stronger and smarter enemies will give more xp
	int earnedXP = (TotalXP + Attacker->Attributes.Aggresion) * (Attributes.Strength/Attacker->Attributes.Strength)*(Attributes.Intelligence/Attacker->Attributes.Intelligence);
	earnedXP = earnedXP == 0 + earnedXP != 0 * earnedXP;
	//Just to make sure the attacker atleast gets some xp
	Attacker->TotalXP += earnedXP;
	//Might add more to do with crime later.
	
}

float AHumanoid::CalculateHealth()
{
	float output;
	output = 1 + this->Attributes.Endurance * 9 + this->Attributes.Strength * 2;

	return output;
}

float AHumanoid::CalculateMagic()
{
	float output;
	output = 1 + this->Attributes.Essence * 4 + this->Skills.MagicalControl + this->Skills.MindTrickery + this->Skills.Healing + this->Skills.Annihilation + this->Attributes.Intelligence * 2;

	return output;
}

float AHumanoid::CalculateStamina()
{
	float output;
	output = 1 + this->Attributes.Endurance * 10 + this->Attributes.Strength * 3 + this->Skills.Acrobatics * 2;

	return output;
}

TMap<FString, int> AHumanoid::GenerateGoblinInventory(int GoblinWealth)
{
	TMap<FString, int> output;
	if (rand() % 5 == 0 || GoblinWealth > 5 && rand() % 3 == 0)
	{
		output.Add("wildberries", trunc(GoblinWealth/2) + rand() % 6 +1);
	}
	if (rand() % 4 == 0)
	{
		output.Add("bread", 1);
	}
	if (rand() % 4 == 0 || GoblinWealth == 10)
	{
		output.Add("apple", rand() % 2 + 1);
	}
	if (rand() % 2 == 0)
	{
		output.Add("penny", rand() % 15 + GoblinWealth + 1);
	}

	return output;
}
