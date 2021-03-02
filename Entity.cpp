// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NavigationSystem.h"
#include "GameFramework/Pawn.h"
#include "HumanAIController.h"
#include "GameFramework/Controller.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "GenericFunctions.h"
#include "Scripting/FarmingNode.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"






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
	AIControllerClass = AHumanAIController::StaticClass();
	SensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent0"));
	//AEntity::SpawnDefaultController();
	//Controller = GetWorld()->SpawnActor<AHumanAIController>(AHumanAIController::StaticClass());
	//Controller = GetWorld()->SpawnActor<AController>(AController::StaticClass());

	static ConstructorHelpers::FObjectFinder<UDataTable> FactionDatabase(TEXT("DataTable'/Game/Mechanics/Factions/FactionData.FactionData'"));
	if (FactionDatabase.Succeeded())
	{
		FactionData = FactionDatabase.Object;
	}
	else
	{
		FactionData = nullptr;
	}

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


bool AEntity::GotoRandomFarmingNode()
{
	//If there isn't something to do maybe return to idle state.

	TArray<AActor*> TempActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFarmingNode::StaticClass(),TempActors);
	bool ViableFound = false;
	int count = 0;
	AFarmingNode* TempNode = nullptr;
	if (TempActors.Num() > 0)
	{
		while (!ViableFound)
		{
			count += 1;
			TempNode = (AFarmingNode*)TempActors[rand() % TempActors.Num()];
			if (TempNode->isOccupied == false && TempNode->OwnerSettlement == Settlement)
			{
				ViableFound = true;
			}

			else if (count == TempActors.Num() + 3) //Yes it won't check some but that'll add an element of randomness
			{
				ViableFound = true;
			}
		}
	}

	if (TempNode)
	{
		//Procedes to tell the entity to do work.
		UNavigationSystemV1* NavSystem;
		NavSystem = UNavigationSystemV1::GetCurrent(this);
		AHumanAIController* EntityController = Cast<AHumanAIController>(GetController());

		if (GetController())
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Controller Valid for farm"));
		}
		if (EntityController)
		{
			//Make sure of a successful cast.
			EntityController->MoveToLocation(TempNode->GetActorLocation());
			TempNode->isOccupied = true;
			TempNode->User = this;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		State = "Waking";
		return false;
	}
}

bool AEntity::SimpleEntityMoveToLocation(FVector Location)
{
	UNavigationSystemV1* NavSystem;
	NavSystem = UNavigationSystemV1::GetCurrent(this);

	AHumanAIController* EntityController = Cast<AHumanAIController>(GetController());

	if (GetController())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Controller Valid for character"));
	}
	if (EntityController)
	{
		//Make sure of a successful cast.
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("I want to move"));
		EntityController->MoveToLocation(Location);
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("I actually ran"));
	return false;
}


void AEntity::RandomShortWalkAround()
{
	if (! inDialogue)
	{

		UNavigationSystemV1* NavSystem;
		NavSystem = UNavigationSystemV1::GetCurrent(this);

		FNavLocation RandomLocation;
		bool LocFound = NavSystem->GetRandomReachablePointInRadius(this->GetActorLocation(), 2250.0f, RandomLocation);
		if (LocFound)
		{
			//Something drastic might have to happen if a suitable location is not found.
			AHumanAIController* EntityController = Cast<AHumanAIController>(GetController());

			//if (GetController())
			//{
			//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Controller Valid"));
			//}
			if (EntityController)
			{
				//Make sure of a successful cast.
				EntityController->MoveToLocation(RandomLocation);
			}

		}
		
	}
}

void AEntity::RandomLongWalkAround()
{
	if (!inDialogue)
	{

		UNavigationSystemV1* NavSystem;
		NavSystem = UNavigationSystemV1::GetCurrent(this);

		FNavLocation RandomLocation;
		bool LocFound = NavSystem->GetRandomReachablePointInRadius(this->GetActorLocation(), 8250.0f, RandomLocation);
		if (LocFound)
		{
			//Something drastic might have to happen if a suitable location is not found.
			AHumanAIController* EntityController = Cast<AHumanAIController>(GetController());

			//if (GetController())
			//{
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Controller Valid"));
			//}
			if (EntityController)
			{
				//Make sure of a successful cast.
				EntityController->MoveToLocation(RandomLocation);
			}

		}

	}
}

void AEntity::EnterDialogueMotion()
{

	//All motion is going to need to stop
	if (GetController())
	{
		GetController()->StopMovement();
	}
	FRotator LookatRot = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());
	//FRotator LookatRot = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), GetWE);
	GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorRotation(LookatRot);
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
	if (Health <= 0 && !Dead)
	{
		Dead = true;
		ExecuteOnDeath();
	}

	if (GetVelocity().Z < -1200)
	{
		FallDamageValue += ((this->GetVelocity().Z+1200)/6 * DeltaTime);
		if (this->GetVelocity().Z < -1800)
		{
			FallDamageValue -= 6 * DeltaTime;
		}
	}
	else
	{
		Health += FallDamageValue;
		FallDamageValue = 0;
	}

	if (DeathSinking)
	{
		AddActorLocalOffset(FVector(0,0,DeltaTime*(-1)));
	}
	//AI
	if (!EntityTags.Contains("NoAI") && !EntityTags.Contains("NonStandardAI") && !Dead)
	{
		//Run the AI response function
		AIResponce();
		Agro = AgroCheck();
	}

}


float AEntity::FindSafetyofPoint(TArray<AEntity*> Enemies, FVector Position)
{
	//This function finds the 1/d^2 value from each the smallest number is the safest place sort of like machine learning.
	float output = 0;
	FVector EnemyLoc;
	float dist;
	for (size_t i = 0; i < Enemies.Num(); i++)
	{
		//Find the 2D distance
		EnemyLoc = Enemies[i]->GetActorLocation();
		dist = pow(Position.Y - EnemyLoc.Y, 2) + pow(Position.X - EnemyLoc.X, 2);
		output += (1/dist);
	}

	return output;
}

bool AEntity::LocationNearEntity(FVector Location, float Distance, TArray<AEntity*> Entities)
{
	//returns true if all the entities are more than a certain distance away.
	bool output = true;
	for (size_t i = 0; i < Entities.Num(); i++)
	{
		if (Distance>FVector::Distance(Location,Entities[i]->GetActorLocation()))
		{
			output = false;
		}
	}
	return output;
}

bool AEntity::isEntityMoving()
{
	//Check to see if the entity is at all moving, it seems to work for ai movement.
	//I doubt they'll ever be much in the way of physics movement.
	float res1;
	FVector Vec1 = this->GetVelocity();
	Vec1.Normalize(0.001);
	
	res1 = FVector::DotProduct(this->GetActorForwardVector(),Vec1);
	return res1 != 0;
	
}

AEntity* AEntity::FindNearestEntityNotinFaction(float SphereSize)
{
	AEntity* Output = nullptr;
	//This will create a list of all the 
	TArray<AActor*> OverlappingActors;

	TArray<AActor*> ActorstoIgnore;
	ActorstoIgnore.Add(this);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	UKismetSystemLibrary::SphereOverlapActors(this,this->GetActorLocation(),SphereSize,ObjectTypes,nullptr,ActorstoIgnore,OverlappingActors);

	TArray<AEntity*> OverlappingEntities;
	AEntity* TempEntity;

	for (size_t i = 0; i < OverlappingActors.Num(); i++)
	{
		TempEntity = (AEntity*)OverlappingActors[i];
		if (TempEntity)
		{
			OverlappingEntities.Add(TempEntity);
		}
	}
	//The entities can't be outside of the sphere.
	float ClosestValue = SphereSize+1;
	TArray<FString> a, b;
	for (size_t i = 0; i < OverlappingEntities.Num(); i++)
	{
		this->Factions.GenerateKeyArray(a);
		OverlappingEntities[i]->Factions.GenerateKeyArray(b);
		if ((this->GetActorLocation() - OverlappingEntities[i]->GetActorLocation()).Size()<ClosestValue && ! UGenericFunctions::HasSimilarString(a,b))
		{
			Output = OverlappingEntities[i];
			ClosestValue = OverlappingEntities[i]->GetActorLocation().Size();
		}
	}
	//Finds the closest entity

	return Output;
	//Will return null if there is no entity that is in no similar factions in range.
}

TArray<AEntity*> AEntity::GetAlliesFromEntites(TArray<AEntity*> Entities)
{
	TArray<AEntity*> Output;
	//I swear this wasn't ment to work, haven't actually ran it yet might have to put in the construction script
	//static ConstructorHelpers::FObjectFinder<UDataTable> FactionDatabase(TEXT("DataTable'/Game/Mechanics/Factions/FactionData.FactionData'"));
		//class UDataTable* FactionData = FactionDatabase.Object;

		TArray<FString> Allies;
		FFactionStruct* EntityFaction;
		FString ContextString;

		TArray<FString> AllyFactions;

		TArray<FString> FactionKeys;
		Factions.GetKeys(FactionKeys);
		for (size_t i = 0; i < Factions.Num(); i++)
		{
			EntityFaction = FactionData->FindRow<FFactionStruct>(FName(*FactionKeys[i]), ContextString, true);
			AllyFactions.Append(EntityFaction->AlliedFactions);
		}
		//This will have gathered all the factions that the entity is an enemy of.
		bool TempValid = true;
		for (size_t i = 0; i < Entities.Num(); i++)
		{
			TempValid = true;
			for (size_t j = 0; j < AllyFactions.Num(); j++)
			{
				if (!Entities[i]->Factions.Contains(AllyFactions[j]))
				{
					TempValid = false;
				}
			}
			Output.Add(Entities[i]);
		}


	return Output;
}

TArray<AEntity*> AEntity::GetEnemiesFromEntites(TArray<AEntity*> Entities)
{
	//Ok this function is nearly the same as the last

	TArray<AEntity*> Output;
	//I swear this wasn't ment to work, haven't actually ran it yet might have to put in the construction script
	//static ConstructorHelpers::FObjectFinder<UDataTable> FactionDatabase(TEXT("DataTable'/Game/Mechanics/Factions/FactionData.FactionData'"));
	//This can't be used outside of a constructor, I'll have to change it, will actually make things more efficient.

		//class UDataTable* FactionData = FactionDatabase.Object;

		TArray<FString> Allies;
		FFactionStruct* EntityFaction;
		FString ContextString;

		TArray<FString> AllyFactions;

		TArray<FString> FactionKeys;
		Factions.GetKeys(FactionKeys);
		for (size_t i = 0; i < Factions.Num(); i++)
		{
			EntityFaction = FactionData->FindRow<FFactionStruct>(FName(*FactionKeys[i]), ContextString, true);
			if (EntityFaction->EnemyFactions.Num()>0)
			{
				AllyFactions.Append(EntityFaction->EnemyFactions);
			}
		}
		if (AllyFactions.Num()>0)
		{
			//This will have gathered all the factions that the entity is an enemy of.
			bool TempValid = true;
			for (size_t i = 0; i < Entities.Num(); i++)
			{
				TempValid = true;
				for (size_t j = 0; j < AllyFactions.Num(); j++)
				{
					if (!Entities[i]->Factions.Contains(AllyFactions[j]))
					{
						TempValid = false;
					}
				}
				if (TempValid)
				{
					Output.Add(Entities[i]);
				}

			}
		}

	return Output;
}

bool AEntity::CalculateFightOrFlight(TArray<AEntity*> Allies, TArray<AEntity*> Enemies)
{
	//If this function returns true it means fight if it returns false it means run
	float value, AllyStrength, EnemyStrength;
	AllyStrength = 0;
	EnemyStrength = 0;
	for (size_t i = 0; i < Allies.Num(); i++)
	{
		AllyStrength += Allies[i]->Health + Allies[i]->Magic;
	}
	for (size_t i = 0; i < Enemies.Num(); i++)
	{
		EnemyStrength += Enemies[i]->Health + Enemies[i]->Magic;
	}
	value = AllyStrength / EnemyStrength;
	value = value * ((Health + Magic)/(100 + Stamina));
	if (EntityTags.Contains("Prey") || EntityTags.Contains("Coward"))
	{
		value = 0;
	}
	if (EntityTags.Contains("Monster") || EntityTags.Contains("Brave"))
	{
		value = 2;
	}
	return value > 1; 
}

TArray<AEntity*> AEntity::GetNearByEntities(float SphereSize)
{
	TArray<AActor*> OverlappingActors;

	TArray<AActor*> ActorstoIgnore;
	ActorstoIgnore.Add(this);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	UKismetSystemLibrary::SphereOverlapActors(this, this->GetActorLocation(), SphereSize, ObjectTypes, nullptr, ActorstoIgnore, OverlappingActors);

	TArray<AEntity*> OverlappingEntities;
	AEntity* TempEntity;

	for (size_t i = 0; i < OverlappingActors.Num(); i++)
	{
		TempEntity = (AEntity*)OverlappingActors[i];
		if (TempEntity)
		{
			OverlappingEntities.Add(TempEntity);
		}
	}

	return OverlappingEntities;

}

void AEntity::AIStateHandling()
{
	//Find everything not in faction
	//Check can detect them will be added later ----
	//Calculate flight or fight
	//Run if flight and enter combat if fight or has monster tag
	//Run combat functions of the particular entity.
	//Basicly copy some stuff out of the blueprints

	AIAttackTarget = FindNearestEntityNotinFaction(1000);
	TArray<AEntity*> OverlappingEntities = GetNearByEntities(1000);
	TArray<AEntity*> Allies,Enemies;
	for (size_t i = 0; i < OverlappingEntities.Num(); i++)
	{

	}

}

void AEntity::MonsterProwl(float radius)
{
	
	if (! isEntityMoving())
	{
		UNavigationSystemV1* NavSystem;
		NavSystem = UNavigationSystemV1::GetCurrent(this);

		FNavLocation RandomLocation;
		bool LocFound = NavSystem->GetRandomReachablePointInRadius(this->GetActorLocation(), radius, RandomLocation);
		if (LocFound)
		{
			//Something drastic might have to happen if a suitable location is not found.
			AHumanAIController* EntityController = Cast<AHumanAIController>(GetController());
			//Might as well use the human controller has well for goblins because it does pretty much nothing


			if (EntityController)
			{
				//Make sure of a successful cast.
				EntityController->MoveToLocation(RandomLocation);
			}
		}
	}
}



void AEntity::RunAway()
{
	if (!isEntityMoving())
	{
		UNavigationSystemV1* NavSystem;
		NavSystem = UNavigationSystemV1::GetCurrent(this);

		FNavLocation RandomLocation;
		bool LocFound;
		TArray<AEntity*> Enemies = GetEnemiesFromEntites(GetNearByEntities(4000));
		int count = 0;
		do
		{
			LocFound = NavSystem->GetRandomReachablePointInRadius(this->GetActorLocation(), 3750, RandomLocation);
			if (LocationNearEntity(RandomLocation.Location,500, Enemies))
			{
				break;
			}
			count++;
		} while (count < 15);

		if (LocFound)
		{
			//Something drastic might have to happen if a suitable location is not found.
			AHumanAIController* EntityController = Cast<AHumanAIController>(GetController());
			//Might as well use the human controller has well for goblins because it does pretty much nothing

			if (GetController())
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT(""));
			}
			if (EntityController)
			{
				//Make sure of a successful cast.
				EntityController->MoveToLocation(RandomLocation);
			}

		}
		//If this fails it'll probably just be done again.

	}
}

void AEntity::NPCCombatTick()
{
	//This is meant to be over riden for most things, but other wise we'll just use a blueprint override by default.
	BlueprintNPCCombatTick();
}

bool AEntity::AgroCheck()
{
	//Firstly use the pawn sensing component to see nearby entities along with anything within 3 meters.
	TArray<AEntity*> NearbyEntities = GetNearByEntities(650);
	//Right now We'll just use any entity within 650 units, 350 is used for always sense.

	NearbyEntities = GetEnemiesFromEntites(NearbyEntities);
	//Strip out the things that aren't enemies.
	
	//Now remove all invalid entities from the list of targets, will make stuff quicker I think
	//This code was causing a crash, so I'll rewrite it
	TArray<AEntity*> InvalidEntities;
	for (size_t i = 0; i < AITargets.Num(); i++)
	{
		if (!InvalidEntities.Contains(AITargets[i]))
		{
			if (!AITargets[i])
			{
				InvalidEntities.Add(AITargets[i]);
			}
			else if (AITargets[i]->Dead || AITargets[i]->GetDistanceTo(this) > 1200)
			{
				InvalidEntities.Add(AITargets[i]);
			}
		}

	}

	//Now remove everything that shouldn't be there
	for (size_t i = 0; i < InvalidEntities.Num(); i++)
	{
		AITargets.Remove(InvalidEntities[i]);
	}


	//Add all the nearby entities that aren't in the list
	for (size_t i = 0; i < NearbyEntities.Num(); i++)
	{
		if (!AITargets.Contains(NearbyEntities[i]))
		{
			AITargets.Add(NearbyEntities[i]);
		}
	}

	//Is just to find out if the list size is greater than 0
	return AITargets.Num() > 0;
}

void AEntity::AIResponce()
{
	//This function should be executed every second unless the entity has the tag "noAI" or "OtherAI"
	if (Agro)
	{
		//If state not fight or run then calculate what to do
		if (State == "Fleeing")
		{
			//Fleeing code
			RunAway();
		}
		else if(State == "Fighting")
		{
			//Fighting code
			//Might want to use custom stuff here, for each class.
			NPCCombatTick();
		}
		else
		{
			//Calculate what state the AI should be in
			
			TArray<AEntity*> NearbyEntities = GetNearByEntities(2000);
			if (CalculateFightOrFlight(GetAlliesFromEntites(NearbyEntities),GetEnemiesFromEntites(NearbyEntities)))
			{
				State = "Fighting";
			}
			else
			{
				State = "Fleeing";
			}
		}
	}
	else
	{
		int a; //just something temp
		a = 0;
		//execute all the stuff to do with the daily life.
	}

}
//void AEntity::ExecuteOnDeath()
//{
	
	
//}

// Called to bind functionality to input
//void AEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

//}

