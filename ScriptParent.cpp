// Fill out your copyright notice in the Description page of Project Settings.


#include "Quadraped.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Humanoid.h"
#include "NavigationSystem.h"
#include "HumanAIController.h"
#include "Engine/EngineTypes.h"




TArray<AEntity*> AQuadraped::GetEnemiesinRadius(float Radius)
{
	TArray<AActor*> TempActors;
	TArray<AActor*> ignore;
	UClass* seekClass = AEntity::StaticClass();
	TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;
	traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	UKismetSystemLibrary::SphereOverlapActors(this, this->GetActorLocation(), Radius,traceObjectTypes, seekClass, ignore, TempActors);


	AEntity* Entity;
	//Now for the prosedure to check if they are enemies.
	for (size_t i = 0; i < TempActors.Num(); i++)
	{
		Entity = (AEntity*)TempActors[i];
		//This loop will go through each actor and test various parameters
		if ((AHumanoid*)Entity)
		{
			//If the actor is a humanoid it'll be removed only if it has the Nature faction, dryads and spriggians would have this faction.
			if (Entity->Factions.Contains("Nature"))
			{
				TempActors.Remove(Entity);
			}
		}
		else
		{
			//Need to check that its valid
			if (Entity)
			{
				if (!Entity->Factions.Contains("Predator"))
				{
					TempActors.Remove(Entity);
				}
			}
			else
			{
				TempActors.Remove(TempActors[i]);
				//If it's not valid then best for it to be removed
			}

		}
	}
	//Not my first choice for casting
	TArray<AEntity*> output;
	for (size_t i = 0; i < TempActors.Num(); i++)
	{
		output.Add((AEntity*)TempActors[i]);
	}
	return output;
}


void AQuadraped::RunFromEnemies(TArray<AEntity*> Enemies)
{
	//Makes them run from the player etc
	grazing = false;
	for (size_t i = 0; i < Group.Num(); i++)
	{
		if (Group[i]->grazing && GetHorizontalDistanceTo(Group[i]) < 1500)
		{
			Group[i]->RunFromEnemies(Enemies);
		}
	}
	//They will warn other things in the nearby area and make them run. It'll cause a chain reaction
	UNavigationSystemV1* NavSystem;
	NavSystem = UNavigationSystemV1::GetCurrent(this);

	FNavLocation RandomLocation;
	bool LocFound = NavSystem->GetRandomReachablePointInRadius(this->GetActorForwardVector() * 2000 + this->GetActorLocation(), 150.0f, RandomLocation);
	if (LocFound)
	{
		//Something drastic might have to happen if a suitable location is not found.
		AHumanAIController* EntityController = Cast<AHumanAIController>(GetController());

		if (GetController())
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("deer Controller Valid"));
		}
		if (EntityController)
		{
			//Make sure of a successful cast.
			EntityController->MoveToLocation(RandomLocation);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("happenn't! invalid"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("maybe the region is too small"));
		//This can happen sometimes, best to have some other stuff that it can do.
		LocFound = NavSystem->GetRandomReachablePointInRadius(this->GetActorForwardVector() * 1500 + this->GetActorLocation(), 350.0f, RandomLocation);
		if (LocFound)
		{
			//Need to run the same things
			AHumanAIController* EntityController = Cast<AHumanAIController>(GetController());

			if (GetController())
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("deer Controller Valid"));
			}
			if (EntityController)
			{
				//Make sure of a successful cast.
				EntityController->MoveToLocation(RandomLocation);
			}
			else
			{
				LocFound = NavSystem->GetRandomReachablePointInRadius(this->GetActorForwardVector() + this->GetActorLocation(), 850.0f, RandomLocation);
				if (GetController())
				{
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("deer Controller Valid"));
				}
				if (EntityController)
				{
					//Make sure of a successful cast.
					EntityController->MoveToLocation(RandomLocation);
				}
			}

		}
	}
}


