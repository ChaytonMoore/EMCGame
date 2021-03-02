// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericFunctions.h"
#include "CoreMinimal.h"
#include "Engine.h"

#include "EngineMinimal.h"
#include "Engine/World.h"
#include "..\Public\GenericFunctions.h"
#include "UObject/NameTypes.h"
#include "NavigationSystem.h"
#include "HumanAIController.h"
#include "BaseSpell.h"
#include "Containers/UnrealString.h"

bool UGenericFunctions::PlayerPickingUp(AActor* caller, bool overlaping)
{
	//caller->GetWorld()->GetFirstPlayerController->GetPawn();
	return false;
}

 void UGenericFunctions::SetNPCHumanHealthOnAttack(AHumanoid* Human, float Damage,class UDataTable* Armour)
{
	 int TotalArmour;

	 FString ContextString;
	 int helm = 0, chest = 0, hands = 0, feet = 0, legs = 0;
	 if (Armour->FindRow<FArmourStruct>(Human->HelmA, ContextString, true))
	 {
		 helm = Armour->FindRow<FArmourStruct>(Human->HelmA, ContextString, true)->ArmourValue;
	 }
	 if (Armour->FindRow<FArmourStruct>(Human->BodyA, ContextString, true))
	 {
		 chest = Armour->FindRow<FArmourStruct>(Human->BodyA, ContextString, true)->ArmourValue;
	 }
	 if (Armour->FindRow<FArmourStruct>(Human->HandsA, ContextString, true))
	 {
		 hands = Armour->FindRow<FArmourStruct>(Human->HandsA, ContextString, true)->ArmourValue;
	 }
	 if (Armour->FindRow<FArmourStruct>(Human->BootsA, ContextString, true))
	 {
		 feet = Armour->FindRow<FArmourStruct>(Human->BootsA, ContextString, true)->ArmourValue;
	 }
	 if (Armour->FindRow<FArmourStruct>(Human->LegsA, ContextString, true))
	 {
		 legs = Armour->FindRow<FArmourStruct>(Human->LegsA, ContextString, true)->ArmourValue;
	 }
	 TotalArmour = (helm * 2 + chest * 2 + hands + feet + legs) / 7;
	 
	 Damage = Damage - ((float)TotalArmour / 100);
	 Human->Health -= Damage;
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

ADataBase * UGenericFunctions::GetDataBase(UObject* Caller)
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
		int TotalValue = (*OriginalInventory.Find("mankas")) * 360 + (*OriginalInventory.Find("shilling")) * 12 + (*OriginalInventory.Find("penny"));
		TotalValue += MoneyChange * 10;
		if (TotalValue>1)
		{
			int MankasValue = (TotalValue / 360);
			int ShillingValue = (TotalValue - MankasValue / 12);
			int PennyValue = TotalValue - MankasValue * 360 - ShillingValue * 12;

			//OriginalInventory.Remove("mankas");
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("penny %f"), float(PennyValue)));
			//OriginalInventory = AddItemToInventory(OriginalInventory, "mankas", MankasValue);
			//OriginalInventory = AddItemToInventory(OriginalInventory, "shilling", ShillingValue);
			//OriginalInventory = AddItemToInventory(OriginalInventory, "penny", PennyValue);
		}
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

bool UGenericFunctions::SimpleEntityMoveScript(AEntity * EntityToMove, FVector Location, bool IgnoreAgro)
{
	AHumanAIController* EntityController = Cast<AHumanAIController>(EntityToMove->GetController());

	if (EntityToMove->GetController())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("yes"));
	}
	if (EntityController)
	{
		//Make sure of a successful cast.
		EntityController->MoveToLocation(Location);
		return true;
	}
	else
	{
		return false;
	}
}

void UGenericFunctions::TeleportPlayer(AActor* Location)
{
	if (Location)
	{
		AHumanoid* PlayerCharacter = (AHumanoid*)UGameplayStatics::GetPlayerPawn(Location, 0);

		PlayerCharacter->SetActorLocation(Location->GetActorLocation());
		PlayerCharacter->SetActorRotation(Location->GetActorRotation());
	}
}

void UGenericFunctions::TeleportPlayerParams(AActor* Location, float MagicChange, float StaminaChange, float HealthChange)
{
	//Same of the normal function, except this overload allows for changes to the users stats, aka climbing a ladder taskes stamina.
	if (Location)
	{
		AHumanoid* PlayerCharacter = (AHumanoid*)UGameplayStatics::GetPlayerPawn(Location, 0);

		PlayerCharacter->SetActorLocation(Location->GetActorLocation());
		PlayerCharacter->SetActorRotation(Location->GetActorRotation());
		PlayerCharacter->Health = PlayerCharacter->Health - HealthChange;
		PlayerCharacter->Magic = PlayerCharacter->Magic - MagicChange;
		PlayerCharacter->Stamina = PlayerCharacter->Stamina - StaminaChange;
	}
}

bool UGenericFunctions::TryTeleportPlayer(AActor* Location, float MagicChange, float StaminaChange, float HealthChange)
{
	//Only allows the player to teleport if they have enough of a resource I imagine this'll mostly be magic for portals.
	AHumanoid* PlayerCharacter = (AHumanoid*)UGameplayStatics::GetPlayerPawn(Location, 0);
	bool output = false;
	if (PlayerCharacter->Magic >= MagicChange && PlayerCharacter->Stamina >= StaminaChange && PlayerCharacter->Health >= HealthChange)
	{
		output = true;
		TeleportPlayerParams(Location, MagicChange, StaminaChange, HealthChange);
	}

	return output;
}

bool UGenericFunctions::CanCastSpell(FMagicSpellStruct spell, AHumanoid* Caller)
{
	bool output = true;

	//In most games the player must have enough magic to cast a spell however in this one stamina and health can be traded for magic, however this can kill the player.
	if (SpellCost(spell) > (Caller->Magic + Caller->Health + Caller->Stamina * 0.2))//stamina isn't worth very much and is more of a warning that health will be taken.
	{
		output = false;
	}

	//They might be at a high enough level to cast it, will probably not use this too much.
	if (spell.LevelReq > Caller->Level)
	{
		output = false;
	}
	//Was going to use a string and parse out the data but had a better idea.
	//Split the map up and then see for each element if it is the right enum and if the value is correct, should lead to less errors.
	for (auto& Elem : spell.SkillReq)
	{
		if (Elem.Key == 3 && Elem.Value > Caller->Skills.Healing)
		{
			output = false;
		}
		if (Elem.Key == 2 && Elem.Value > Caller->Skills.MagicalControl)
		{
			output = false;
		}
		if (Elem.Key == 1 && Elem.Value > Caller->Skills.MindTrickery)
		{
			output = false;
		}
		if (Elem.Key == 0 && Elem.Value > Caller->Skills.Annihilation)
		{
			output = false;
		}
	}
	return output;
}

int UGenericFunctions::SpellCost(FMagicSpellStruct spell)
{
	int output = 0;
	if (spell.FXEssenceOveride > 0)
	{
		output = spell.FXEssenceOveride;
	}
	else
	{
		for (size_t i = 0; i < spell.Effects.Num(); i++)
		{
			output += spell.Effects[i].FXEssence;
		}
	}

	return output;
}
//int Randint(int low, int high)
//{
	//return  rand() % (high - low) + low;
//}
bool UGenericFunctions::CastSpell(FMagicSpellStruct spell, AHumanoid* Caller, FRotator DesiredRotation)
{
	bool success = UGenericFunctions::CanCastSpell(spell, Caller);
	//Made sure it can spawn
	ABaseSpell* SpellSpawned;
	if (success && Caller)
	{
		FActorSpawnParameters SpawnParams;
		for (size_t i = 0; i < spell.Effects.Num(); i++)
		{
		
			SpellSpawned = Caller->GetWorld()->SpawnActor<ABaseSpell>(spell.Effects[i].FXscript, Caller->GetActorLocation(), DesiredRotation, SpawnParams);
			SpellSpawned->Caller = Caller;
		}
		//Now to subtract the magic used from the users supply
		Caller->Magic -= SpellCost(spell);
		if (Caller->Magic < 0)
		{
			if (abs(Caller->Magic) > (Caller->Stamina * 0.2)) //stamina is worth less than health or essence(magic)
			{
				Caller->Stamina = 0;
				Caller->Health -= abs(Caller->Magic) - (Caller->Stamina * 0.2);

			}
			else
			{
				Caller->Stamina -= abs(Caller->Magic) * 5;
			}
			Caller->Magic = 0;
		}
		//The chance of getting xp decreases with the difference in level between player and spell, hence removing level farming to some degree
		int chance = rand() % (10 +(spell.LevelReq - Caller->Level));
		if (chance == 0)
		{
			Caller->TotalXP += 50 + spell.LevelReq*5;
		}
		//The player also needs a small change to increase their skill
		chance = rand() % (15 + (spell.LevelReq - Caller->Level) * 3);
		if(chance == 0)
		{
			//Now to select which skill needs to be updated.
			if (spell.Type == 0)
			{
				Caller->Skills.Annihilation += 1;
			}
			else if(spell.Type == 1)
			{
				Caller->Skills.MindTrickery += 1;
			}
			else if(spell.Type == 2)
			{
				Caller->Skills.MagicalControl += 1;
			}
			else
			{
				Caller->Skills.Healing += 1;
			}
		}

	}


	return success;
}

bool UGenericFunctions::HealEntity(AEntity* Caller, float amount)
{
	bool output = false;
	if (Caller)
	{
		Caller->Health += amount;
		output = true;
	}
	return output;
	
}

bool UGenericFunctions::RestoreStaminaEntity(AEntity* Caller, float amount)
{
	bool output = false;
	if (Caller)
	{
		Caller->Stamina += amount;
		output = true;
	}
	return output;

}

bool UGenericFunctions::RestoreEssenceEntity(AEntity* Caller, float amount)
{
	bool output = false;
	if (Caller)
	{
		Caller->Magic += amount;
		output = true;
	}
	return output;
}

void UGenericFunctions::CalculateStats(AHumanoid* Caller)
{
	//Here is where primary stats of the player are calculated. Magic is the skills and the essence
	Caller->MaxMagic = Caller->Attributes.Essence * 5 + Caller->Attributes.Intelligence + Caller->Skills.Healing + Caller->Skills.Annihilation + Caller->Skills.MindTrickery + Caller->Skills.MagicalControl;
	//Health is endurance and strength but acrobatics factos in aka dodging and block as how well can you take a hit.
	Caller->MaxHealth = Caller->Skills.Acrobatics + Caller->Skills.Block + Caller->Attributes.Endurance * 9 + Caller->Attributes.Strength * 9;
	//stamina is mainly endurance but strength helps. Acrobatics and dexterity is basicly efficiency(how well you can use it)
	Caller->MaxStamina = Caller->Attributes.Endurance * 16 + Caller->Attributes.Strength * 2 + Caller->Skills.Acrobatics + Caller->Attributes.Dexterity;
}

TArray<FString> UGenericFunctions::RemoveElementsFromArrayString(TArray<FString> Main, TArray<FString> RemoveElems)
{
	for (size_t i = 0; i < RemoveElems.Num(); i++)
	{
		if (Main.Contains(RemoveElems[i]))
		{
			Main.Remove(RemoveElems[i]);
		}
	}
	return Main;
}


void UGenericFunctions::MagicAtZeroRefil(AHumanoid* Caller)
{
	//This function checks if the player has an amulet of restore magic, if they do it is used to resture their magic to full but has a chance of breaking.
	if (Caller->Inventory.Contains("Magicamulet"))
	{
		Caller->Magic = Caller->MaxMagic;
		if (rand() % 4 == 0)
		{
			Caller->Inventory = RemoveItemFromInventory(Caller->Inventory, "Magicamulet",1);
		}
	}

}

FRotator UGenericFunctions::AddRotator(FRotator first, FRotator second)
{
	first.Pitch += second.Pitch;
	first.Yaw += second.Yaw;
	first.Roll += second.Roll;

	return first;
}

int UGenericFunctions::SumInt(TArray<int> values)
{
	int output = 0;
	for (size_t i = 0; i < values.Num(); i++)
	{
		output += values[i];
	}
	
	return output;
}


bool UGenericFunctions::ApproxFloat(float a, float b)
{
	//is it within 0.1 of the other float
	return abs(a - b) <= 0.1;
}

FVector UGenericFunctions::RandomVectorInRadius(FVector Start, int Radius)
{
	//Not for AI. This is flat 2D and not local
	int a = rand() % Radius - Radius / 2;
	int b = rand() % Radius - Radius / 2;

	Start.X += a;
	Start.Y += b;

	return Start;
}

bool UGenericFunctions::HasSimilarString(TArray<FString> a, TArray<FString> b)
{
	bool output = false;
	for (size_t i = 0; i < a.Num(); i++)
	{
		if (b.Contains(a[i]))
		{
			output = true;
			break;
		}
	}

	return output;
}

float UGenericFunctions::HealthFromAttack(class UDataTable* Items, class UDataTable* Weapons, class UDataTable* Armour, AHumanoid* Attacker, AHumanoid* Defender)
{
	float output = Defender->Health;
	//float Attack;
	//FName Right = Attacker->EquipmentRight;
	FString ContextString;
	FWeaponStruct* WeaponRowRef = Weapons->FindRow<FWeaponStruct>(Attacker->EquipmentRight, ContextString, true);
	float WeaponDamage = WeaponRowRef->Damage;

	//Now to calculate the armour value.
	//Armour works by each piece having an integer value between 0 and 100(non inclusive) this is what percentage of the damage it blocks. To calculate total armour the average of all pieces 
	//is found with the helmet and chestplate having a double weighting.
	int helm = 0, chest = 0, hands = 0, feet = 0, legs = 0;
	if (Armour->FindRow<FArmourStruct>(Defender->HelmA, ContextString, true))
	{
		helm = Armour->FindRow<FArmourStruct>(Defender->HelmA, ContextString, true)->ArmourValue; 
	}
	if (Armour->FindRow<FArmourStruct>(Defender->BodyA, ContextString, true))
	{
		chest = Armour->FindRow<FArmourStruct>(Defender->BodyA, ContextString, true)->ArmourValue;
	}
	if (Armour->FindRow<FArmourStruct>(Defender->HandsA, ContextString, true))
	{
		hands = Armour->FindRow<FArmourStruct>(Defender->HandsA, ContextString, true)->ArmourValue;
	}
	if (Armour->FindRow<FArmourStruct>(Defender->BootsA, ContextString, true))
	{
		feet = Armour->FindRow<FArmourStruct>(Defender->BootsA, ContextString, true)->ArmourValue;
	}
	if (Armour->FindRow<FArmourStruct>(Defender->LegsA, ContextString, true))
	{
		legs = Armour->FindRow<FArmourStruct>(Defender->LegsA, ContextString, true)->ArmourValue;
	}

	float TotalArmourValue = (helm * 2 + chest * 2 + hands + feet + legs) / 700.0;

	//Get relavent attack skill
	int AttackSkill = 0;
	if (WeaponRowRef->type == "1h_sword" || WeaponRowRef->type == "1h_axe"|| WeaponRowRef->type == "1h_blunt")
	{
		AttackSkill = Attacker->Skills.OneHanded;
	}
	else if(WeaponRowRef->type == "2h")
	{
		AttackSkill = Attacker->Skills.TwoHanded;
	}
	else
	{
		AttackSkill = Attacker->Skills.Polearms;
	}


	GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Yellow, FString::Printf(TEXT("skill: %f"), AttackSkill));
	GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Yellow, FString::Printf(TEXT("weapondaamage before: %f"), WeaponDamage));
	WeaponDamage = WeaponDamage * ((AttackSkill * 2) / (Defender->Skills.Acrobatics + Defender->Skills.Block)) * (1 - TotalArmourValue) *(((Attacker->Stamina)/(Attacker->MaxStamina)+1)/(1+(Defender->Stamina)/(Defender->MaxStamina)));


	GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Yellow, FString::Printf(TEXT("weapondaamage: %f"), WeaponDamage));
	output -= WeaponDamage;
	//Check if the entity has been killed
	if (Defender->Health <= 0)
	{
		Defender->OnDeathParamsHumanoid(Attacker);
	}
	//This is enough for right now
	output -= WeaponRowRef->Damage;
	return output;
}

TArray<AActor*> UGenericFunctions::PureRemoveItem(TArray<AActor*> list, AActor* item)
{
	if (list.Contains(item))
	{
		list.Remove(item);
	}
	return list;
}

AEntity* UGenericFunctions::NearestEntity(TArray<AEntity*> Entities, AActor* selfRef)
{
	if (Entities.Num() > 0)
	{
		AEntity* output;
		output = Entities[0];
		for (size_t i = 1; i < Entities.Num(); i++)
		{
			if (Entities[i]->GetDistanceTo(selfRef) < output->GetDistanceTo(selfRef))
			{
				output = Entities[i];
			}
		}
		return output;
	}
	else
	{
		return nullptr;
	}
}

void UGenericFunctions::Reinitconstructor(AActor * toReinit)
{
	toReinit->RerunConstructionScripts();
}

AActor*  UGenericFunctions::GetNearestActor(AActor* selfRef, TArray<AActor*> Others)
{
	float shortest = 1000000000;
	AActor* output = nullptr;
	for (size_t i = 0; i < Others.Num(); i++)
	{
		if (FVector::Dist(selfRef->GetActorLocation(),Others[i]->GetActorLocation())<shortest)
		{
			shortest = FVector::Dist(selfRef->GetActorLocation(), Others[i]->GetActorLocation());
			output = Others[i];
		}
	}
	return output;

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


