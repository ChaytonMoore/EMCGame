// Fill out your copyright notice in the Description page of Project Settings.


#include "DataBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "SettlementNode.h"

// Sets default values
ADataBase::ADataBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADataBase::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> TempActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ASettlementNode::StaticClass(),TempActors);

	for (size_t i = 0; i < TempActors.Num(); i++) //Should now have all the references.
	{
		Settlements.Add(Cast<ASettlementNode>(TempActors[i]));
		SettlementNames.Add(Settlements[i]->SettlementName);
	}
	UpdateSunLocation(LightSource, Time);
}

// Called every frame
void ADataBase::Tick(float DeltaTime)
{
	//Might make it so that time progresses faster at night such that the night isn't as long.
	Super::Tick(DeltaTime);
	if (Time >= 24)
	{
		Time = 0;
		DayNumber += 1;
	}

	//I think the if statements need error margins
	if ((Time >= 6 && Time <= 6.22)&& isNight)
	{
		isNight = false;
	}
	
	//This one also needs error margins
	if (Time >= 18 && Time <= 18.22 && isNight == false)
	{
		isNight = true;
	}


	WeatherTickAmount += DeltaTime;
	TimeTickAmount += DeltaTime;
	if (WeatherTickAmount >= 5)
	{
		WeatherTickAmount = 0;
		for (size_t i = 0; i < WeatherObjs.Num(); i++)
		{
			WeatherObjs[i]->UpdateTick = true;
			WeatherObjs[i]->isNight = isNight;
		}
	}

	if (TimeTickAmount >= 10)
	{
		TimeTickAmount = 0;
		Time += 0.2;
		UpdateSunLocation(LightSource,Time);
	}

}

ASettlementNode * ADataBase::FindSettlementFromName(FName SpecificName)
{
	
	ASettlementNode* SpecificSettlementNode;
	SpecificSettlementNode = Settlements[SettlementNames.Find(SpecificName)];

	return SpecificSettlementNode;
}

void ADataBase::UpdateSunLocation(AActor* Sun, float Suntime)
{
	float OSunTime = Suntime;
	//Checks if it can find a valid reference to sun, incase it is indoors.
	if (Sun)
	{
		//This code is used to change the angle of the light source. However it also makes it so that the sun moves at different speeds.

		if (isNight)
		{
			if (Suntime >= 18)
			{
				Suntime = Suntime - 24;
			}
			Suntime = (Suntime + 6) / 12;
		}
		else
		{
			Suntime = (Suntime - 6) / 12;
		}
		float fSuntime = (log10(Suntime / (1 - Suntime)) + 3.53994) * 3.38989;
		
		Sun->SetActorRotation(FRotator(fSuntime*(-15) + (90 + 180*(isNight)), 90, 90), ETeleportType::None);

	}
}


float ADataBase::SunDayTimeIntensity()
{
	//How bright the sun should be.
	return 10 * pow((-pow(((Time-12.5)/6.5),2)+1), 0.25);
}
