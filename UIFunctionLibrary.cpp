// Fill out your copyright notice in the Description page of Project Settings.


#include "UIFunctionLibrary.h"
#include "..\Public\UIFunctionLibrary.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GenericFunctions.h"
#include "Engine/DataTable.h"
#include "Containers/Map.h"
#include "Engine.h"

FString UUIFunctionLibrary::childhoodTextGeneration(int stage, int cultureidx, bool gender, FString choice1, int choice2, int choice3, int choice4,int choice1i)
{
	FString fsOutput;
	FString fsForeText;
	FString regionPicker[9] = { "Hyalfx","Cauldcis","Jukt","Maeherium","Samna","the south of the Ascan","Phocaea","the north of the Ascan","Gherebia" };//strings for the regions. I don't know if I should make it localisable
	FString FatherText[9] = { "You grew up hearing stories of the wars that he'd fought in. You always see him training and would even join in ","You grew up around goods from all over the world. In this way you saw how things were handled.","Perhaps at one of the local courts or he may have been part of a guild, or even owned his own tower.","Your father was a druid, he lived in the woods, almost in harmoney with them.","Your father was a hunter, he know he way around nature and how to exploit it.","Your father was a farmer, he worked all his life to grow food, which you usually helped with.","Your father was a craftsman, you watched him create the things that he paid to."};
	if (stage == 1) {//This is choosing your fathers proffesion
		fsForeText = "You grew up in " + regionPicker[cultureidx] + ", your father was a " + choice1+".";
		fsOutput = fsForeText + FatherText[choice1i];
		if (cultureidx == 1){
			fsOutput = fsOutput + "Of course being a mage in Cauldcis land was highly illegal so you were lucky you didn't get killed.";
		}
	}
	if (stage == 2) {//This is for what you did in your early childhood.
		if (choice2 == 0){
			if (choice1 == "knight" && gender == false) {
				fsOutput = "Following in the footsteps of your father you trained in the use of arms, however being young it was only mock fights among your kin with wooden swords.";
			}
			else {
				fsOutput = "While you most likely weren't destined for a martial life you non the less decided to take up arms with your young kin, though only with wooden swords.";
			}
		}
		if (choice2 == 1) {
			if (choice1 == "hunter" || choice1 == "druid") {
				fsOutput = "Your father lived in the woods and so at a young age you learnt about nature.";
			}
			else {
				fsOutput = "You may not have grown up that much in nature but at a young age you learnt much about it.";
			}

		}
		if (choice2 == 2) {
			fsOutput = "You learnt well in your youth spending much of your time developing your intellect.";

		}
		if (choice2 == 3) {
			if (choice1 == "knight" || choice1 == "mage") {
				fsOutput = "Your family fell on hard times and you had to work to earn you bread through work.";
			}
			else {
				if (gender == true) {
					fsOutput = "You spent much of your younger years following in the foot steps of you mother.";
				}
				else {
					fsOutput = "You spent much of your younger years following in the foot steps of you father.";
				}
			}
		}
		if (choice2 == 4) {
			fsOutput = "You spent much of your time perfecting your social skills and getting to understand adults better.";
		}
	}
	if (stage == 3) {
		if (choice3 == 0) {
			fsOutput = "You trained at arms in your early teenage years.";
			if (gender == true) {
				fsOutput = "While your mother and father insisted that you put your time to better use you trained at arms in your teenage years.";
			}
		}
		if (choice3 == 1) {
			fsOutput = "You spent a great deal of your time learning to scout.";
		}
		if (choice3 == 2) {
			fsOutput = "You rode and took care of horses most of the time. This gave you a great understanding of animals especially horses.";
		}
		if (choice3 == 3) {
			fsOutput = "You found work as an apprentice learning a trade at a young age.";
		}
		if (choice3 == 4) {
			if (choice1 == "druid" || choice1 == "mage") {
				fsOutput = "In your fathers foot steps you began to learn maigc such that you could better manipulate the world.";
			}
			else {
				fsOutput = "While you weren't destined for magic you practised it non the less.";
			}
			if (cultureidx == 1) {
				fsOutput = "While your people had a great hatred for magic, you practised it in secret knowing that if found out you could be killed.";
			}
		}
		if (choice3 == 5) {
			fsOutput = "You worked to earn money growing strong in the process.";
		}
	}
	if (stage == 4) {
		if (choice4 == 0) {
			fsOutput = "You being from a good family became a squire in your youth, learning how to fight and the workings of armour.";
		}
		if (choice4 == 1) {
			fsOutput = "You went hunting almost everyday, becoming a hunter. You learnt the way of animals and of the bow.";
		}
		if (choice4 == 2) {
			fsOutput = "You managed to get into university where you learnt all that the university could teach.";
		}
		if (choice4 == 3) {
			fsOutput = "You became a semi-proffesional mage, making a living helping people with magic";
			if (cultureidx == 1) {
				fsOutput = "You learnt to hide your magical abilities well yet still made money with magic.";
			}
		}
		if (choice4 == 4) {
			fsOutput = "You used herbs to heal people, thus making good money.";
		}
		if (choice4 == 5) {
			fsOutput = "You work to make money and help you family.";
		}
		if (choice4 == 6) {
			fsOutput = "Instead of pursuing an honourable carear, you became a thief learning to take what was not yours.";
		}
	}
	if (stage == 5)
	{
		fsOutput = "For what ever reason you decided to go to Eragrim a country beset with civil war: perhaps it was to make your fortune adventuring or serve as a mercenary. You set sail on a ship.";
	}
		
	return FString(fsOutput);
}

FSkills UUIFunctionLibrary::SkillsInit(int cultureidx, int choice1i, int choice2, int choice3, int choice4)
{
	FSkills Output;
	if (cultureidx == 0) {//Hyalfxian culture
		Output.Polearms += 10;
		Output.Unarmed += 5;
		Output.MediumArmour += 5;
	}
	if (cultureidx == 1) {//Cauldcis culture
		Output.LightArmour += 5;
		Output.Charisma += 5;
		Output.Throwing += 10;
		Output.Stealth += 5;
		Output.Healing -= 10; // The cauldcis can't really be mages however healing is less bad. Might want to change these later for balance.
		Output.Annihilation -= 20;
		Output.MagicalControl -= 20;
		Output.MindTrickery -= 25;
	}
	if (cultureidx == 2) {//Jukt culture
		Output.Riding += 10;
		Output.Block += 5;
		Output.Healing += 5;
	}
	if (cultureidx == 3) {//Maeherium culture
		Output.Annihilation += 5;
		Output.MindTrickery += 5;
		Output.Acrobatics += 10;

	}
	if (cultureidx == 4) {//Samna culture
		Output.MagicalControl += 5;
		Output.HeavyArmour += 10;
		Output.OneHanded += 5;

	}
	if (cultureidx == 5) {//South ascan culture
		Output.TwoHanded += 5;
		Output.Annihilation += 5;
		Output.Stealth += 10;
	}
	if (cultureidx == 6) {//phochaea culture
		Output.Archery += 5;
		Output.Polearms += 5;
		Output.Healing += 10;
	}
	if (cultureidx == 7) {//north ascan culture
		Output.Riding += 5;
		Output.HeavyArmour += 5;
		Output.MagicalControl += 5;
	}
	if (cultureidx == 8) {//Ghereb culture
		Output.Thievery += 10;
		Output.Healing += 5;
		Output.MindTrickery += 5;
	}


	//Player father
	if (choice1i == 0) {//knight
		Output.Riding += 5;
		Output.TwoHanded += 5;
	}
	if (choice1i == 1) {//merchant
		Output.Charisma += 10;
	}
	if (choice1i == 2) {//mage
		Output.Healing += 5;
		Output.MagicalControl += 5;
		Output.MindTrickery += 5;
		Output.HeavyArmour -= 5;
	}
	if (choice1i == 3) {//druid
		Output.Healing += 5;
		Output.Alchemy += 5;
	}
	if (choice1i == 4) {//hunter
		Output.Stealth += 5;
		Output.Archery += 5;
	}
	if (choice1i == 5) {//farmer
		Output.Polearms += 5; // This option needs to get extra attribute bonuses
	}
	if (choice1i == 6) {//craftsman
		Output.Unarmed += 5;
		Output.Charisma += 5;
	}

	//Early childhood
	if (choice2 == 0) {//arms
		Output.OneHanded += 5;
		Output.Block += 5;
	}
	if (choice2 == 1) {//nature
		Output.Alchemy += 5;
		Output.Stealth += 5;
	}
	if (choice2 == 2) {//intellect
		Output.MindTrickery += 5; //Should get extra bonus in attributes
	}
	if (choice2 == 3) {//work
		Output.Unarmed += 5;
		Output.Acrobatics += 5;
	}
	if (choice2 == 4) {//social
		Output.Charisma += 10;
	}

	//Late childhood
	if (choice3 == 0) {//arms
		Output.TwoHanded += 5;
		Output.Polearms += 5;
	}
	if (choice3 == 1) {//scouting
		Output.Acrobatics += 5;
		Output.Stealth += 5;
	}
	if (choice3 == 2) {//horses
		Output.Riding += 10;
	}
	if (choice3 == 3) {//apprentice
		Output.Unarmed += 5; // recieve bonus
	}
	if (choice3 == 4) {//magic
		Output.MindTrickery += 5;
		Output.Healing += 5;
		Output.Annihilation += 5;
		Output.Charisma -= 5;
	}
	if (choice3 == 5) {//work
		Output.Acrobatics += 5; // recieve bonus
	}

	//youth -- each one of these recieves a bonus of 25 points.
	if (choice4 == 0){//squire
		Output.Riding += 5;
		Output.HeavyArmour += 10;
		Output.MediumArmour += 5;
		Output.OneHanded += 5;

	}
	if (choice4 == 1) {//hunter
		Output.Stealth += 10;
		Output.Archery += 15;
	}
	if (choice4 == 2) {//student
		Output.Unarmed += 5;//recieve bonus
		Output.Alchemy += 5;
	}
	if (choice4 == 3) {//mage
		Output.Alchemy += 5;
		Output.MindTrickery += 5;
		Output.Annihilation += 5;
		Output.Healing += 10;
		Output.MagicalControl += 5;
		Output.Unarmed -= 5;
	}
	if (choice4 == 4) {//alchemy
		Output.Alchemy += 20;
		Output.Healing += 5;
	}
	if (choice4 == 5) {//work
		Output.Unarmed += 5;
		Output.Polearms += 5; //recieve bonus
	}
	if (choice4 == 6) {//thievery
		Output.Stealth += 10;
		Output.Thievery += 15;
	}



	return FSkills(Output);
}

FAttribution UUIFunctionLibrary::AttributesInit(int cultureidx, int choice1i, int choice2, int choice3, int choice4, bool gender)
{
	FAttribution Output;

	if (cultureidx == 0) {//hyalfx
		Output.Endurance += 1;
	}
	if (cultureidx == 1) {//cauldcis
		Output.Dexterity += 1;
	}
	if (cultureidx == 2) {//jukt
		Output.Aggresion += 1;
	}
	if (cultureidx == 3) {//maeherium
		Output.Essence += 1;
	}
	if (cultureidx == 4) {//samna
		Output.Strength += 1;
	}
	if (cultureidx == 5) {//south ascan
		Output.Dexterity += 1;
	}
	if (cultureidx == 6) {//phocaea
		Output.Personality += 1;
	}
	if (cultureidx == 7) {//north ascan
		Output.Strength += 1;
	}
	if (cultureidx == 8) {//gherebia
		Output.Essence += 1;
	}

	if (choice1i == 0) {//knight
		Output.Strength += 1;
	}
	if (choice1i == 1) {//merchant
		Output.Personality += 1;
	}
	if (choice1i == 2) {//mage
		Output.Essence += 1;
	}
	if (choice1i == 3) {//druid
		Output.Perception += 1;
	}
	if (choice1i == 4) {//hunter
		Output.Endurance += 1;
	}
	if (choice1i == 5) {//farmer
		Output.Endurance += 1;
		Output.Strength += 1;
	}
	if (choice1i == 6) {//craftsman
		Output.Dexterity += 1;
	}

	if (choice2 == 2) {//intellect (only bonus for young childhood)
		Output.Intelligence += 1;
	}

	//old childhood
	if (choice3 == 0) {//arms
		Output.Aggresion += 1;
	}
	if (choice3 == 1) {//scouting
		Output.Perception += 1;
	}
	if (choice3 == 2) {//horses
		Output.Personality += 1;
	}
	if (choice3 == 3) {//apprentice
		Output.Dexterity += 2;
	}
	if (choice3 == 4) {//magic
		Output.Essence += 1;
	}
	if (choice3 == 5) {//work
		Output.Strength += 1;
		Output.Endurance += 1;
	}

	//youth -- Each of these will get +3(bonuses +4)
	if (choice4 == 0) {//squire
		Output.Aggresion += 1;
		Output.Strength += 2;
	}
	if (choice4 == 1) {//hunter
		Output.Strength += 1;
		Output.Perception += 2;
	}
	if (choice4 == 2) {//student
		Output.Intelligence += 3;
		Output.Personality += 1;
	}
	if (choice4 == 3) {//mage
		Output.Essence += 3;
	}
	if (choice4 == 4) {//alchemy
		Output.Dexterity += 1;
		Output.Intelligence += 1;
		Output.Perception += 1;
	}
	if (choice4 == 5) {//work
		Output.Strength += 2;
		Output.Endurance += 2;
	}
	if (choice4 == 6) {//thievery
		Output.Perception += 1;
		Output.Dexterity += 2;
	}

	//Gender differences
	if (gender) {
		Output.Dexterity += 1;
	}
	else {
		Output.Strength += 1;
	}

	return FAttribution(Output);
}

bool UUIFunctionLibrary::DialogueCheck(TArray<FString> PlayerNeed, TArray<FString> PlayerCant, TArray<FString> NPCNeed, TArray<FString> NPCCant, TArray<FString> WorldNeed, TArray<FString> WorldCant, TArray<FString> PlayerObjs, TArray<FString> NPCObjs, TArray<FString> WorldObjs)
{
	bool Output = true;
	
	for (size_t i = 0; i < (PlayerNeed.Num()); i++)		//Checks to make sure that all of the required objs are there
	{
		if (! PlayerObjs.Contains(PlayerNeed[i])) 
		{
			Output = false;
		}
	}

	for (size_t i = 0; i < (NPCNeed.Num()); i++)
	{
		if (! PlayerObjs.Contains(NPCNeed[i])) {
			Output = false;
		}
	}

	for (size_t i = 0; i < (WorldNeed.Num()); i++)
	{
		if (! PlayerObjs.Contains(WorldNeed[i])) {
			Output = false;
		}
	}


	for (size_t i = 0; i < (PlayerCant.Num()); i++)			//Checks to make sure you don't have anything you shouldn't or the npc or the world
	{
		if (PlayerObjs.Contains(PlayerCant[i])) {
			Output = false;
		}
	}

	for (size_t i = 0; i < (NPCCant.Num()); i++)		
	{
		if (PlayerObjs.Contains(NPCCant[i])) {
			Output = false;
		}
	}

	for (size_t i = 0; i < (PlayerCant.Num()); i++)			
	{
		if (PlayerObjs.Contains(PlayerCant[i])) {
			Output = false;
		}
	}

	return Output;
}

void UUIFunctionLibrary::RemoveChildren(UPanelWidget* ParentObject)
{
	TArray<UWidget*> ChildObjects;
	ChildObjects =  ParentObject->GetAllChildren();
	for (size_t i = 0; i < ChildObjects.Num(); i++)
	{
		ChildObjects[i]->RemoveFromParent();
	}
}

TArray<FString> UUIFunctionLibrary::DialogueAddRemoveObjs(TArray<FString> MainArray, TArray<FString> AddObjs, TArray<FString> RemoveObjs)
{
	for (size_t i = 0; int(i) < AddObjs.Num(); i++)
	{
		if (! MainArray.Contains(AddObjs[i]))
		{
			MainArray.Add(AddObjs[i]);
		}
	}
	for (size_t i = 0; int(i) < RemoveObjs.Num(); i++)
	{
		if (MainArray.Contains(RemoveObjs[i]))
		{
			MainArray.Remove(RemoveObjs[i]);
		}
	}

	return TArray<FString>(MainArray);
}

float UUIFunctionLibrary::LocalItemPrice(float OriginalPrice, int SellerPersonality, int BuyerPersonality, int SellerIntelligence, int BuyerIntelligence, int SellerCharisma, int BuyerCharisma)
{
	float Output;
	int BuyerStats;
	int SellerStats;

	BuyerStats = BuyerPersonality + (BuyerIntelligence * 1.1) + BuyerCharisma;
	SellerStats = SellerPersonality + (SellerIntelligence * 1.1) + SellerCharisma;
	//Make sure no divide by 0 happens
	if (BuyerStats == 0)
	{
		BuyerStats = 1;
	}

	if (SellerStats ==0)
	{
		SellerStats = 1;
	}


	Output = sqrt(sqrt(SellerStats) * 1/(sqrt(BuyerStats)));
	Output = Output * OriginalPrice;
	Output = truncf(Output * 10) / 10;

	return Output;
}

void UUIFunctionLibrary::PartiallyRemoveWidget(UUserWidget * Caller)
{
	Caller->GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
	Caller->RemoveFromParent();
}

FText UUIFunctionLibrary::GetQuestTitle(TMap<class UDataTable*, int> Quests, int idx)
{
	FText Output;
	FString ContextString; //This just makes it work
	TArray<class UDataTable*> DataTableRefs;
	Quests.GetKeys(DataTableRefs);
	FQuestStruct* DataRowRef = DataTableRefs[idx]->FindRow<FQuestStruct>(FName(TEXT("0")), ContextString, true);
	Output = DataRowRef->Name;

	return FText(Output);
}

FText UUIFunctionLibrary::GetQuestDescription(TMap<class UDataTable*, int> Quests, int idx)
{
	FText Output;
	FString ContextString;
	TArray<class UDataTable*> DataTableRefs;
	Quests.GetKeys(DataTableRefs);
	TArray<FName> RowNames = DataTableRefs[idx]->GetRowNames();

	FQuestStruct* DataRowRef = DataTableRefs[idx]->FindRow<FQuestStruct>(FName(TEXT("0")), ContextString, true); //The initial value
	Output = DataRowRef->Description;
	
	//Now for if there is a difference in the description for that quest

	TArray<int> QuestValues;
	Quests.GenerateValueArray(QuestValues);
	FName TempName = FName(*FString::FromInt(QuestValues[idx]));

	//Should probably do some validation here
	if (DataTableRefs[idx]->GetRowNames().Contains(TempName))
	{
		if (DataTableRefs[idx]->FindRow<FQuestStruct>(TempName, ContextString, true)->Description.ToString() != FString("")) //Checks to see if the description is not empty
		{
			Output = DataTableRefs[idx]->FindRow<FQuestStruct>(TempName, ContextString, true)->Description;
		}
	}


	return FText(Output);
}


