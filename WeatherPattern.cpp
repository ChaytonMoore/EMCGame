// Fill out your copyright notice in the Description page of Project Settings.


#include "WeatherPattern.h"
#include "UObject/UObjectGlobals.h"

// Sets default values
AWeatherPattern::AWeatherPattern()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(FName(TEXT("Weather Collider")));
	CollisionBox->SetWorldScale3D(FVector(500,500,500));
	CollisionBox->SetCollisionObjectType(ECC_WorldDynamic);

}

void AWeatherPattern::FogNightTickEvent()
{
	//The fog will be increased by a random amount each tick
	if (Severity < 1)
	{
		Severity += (rand() % 3) / 50;
	}
	else
	{
		if (Severity > 1.05)
		{
			//The fog will become heavy in this scenario
			Type = "HeavyFog";
			Severity = 1;
		}
		else
		{
			//The fog will somewhat decay
			Severity -= 0.4;
		}
	}

	if (Severity > 0.3 && Severity < 0.9 && rand() % 8 == 0)
	{
		Type == "Rain";
	}
}

void AWeatherPattern::HeavyFogNightTickEvent()
{
	Severity += (rand() % 3 - 1) / 20;
	if (rand() % 35 == 1)//Random event where the fog increases a lot, might have some gameplay effects
	{
		Severity += 1.5;
	}

	if(Severity < 0.05)
	{
		Type = "LightFog";
	}
}

// Called when the game starts or when spawned
void AWeatherPattern::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void AWeatherPattern::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (UpdateTick == true)
	{
		UpdateTick = false;
		if (isNight)
		{
			//NightTickEvent();
			if (Type == "LightFog")
			{
				FogNightTickEvent();
			}
			else if (Type == "HeavyFog") //Needs to be elif or it will repeat the tick for different types of weather.
			{
				HeavyFogNightTickEvent();
			}
			else if (Type == "Rain")
			{
				Severity += (rand() % 3 - 1) / 25;
			}
		}
		else
		{
			//When it's day everything deterorates
			if(Type == "LightFog")
			{
				Severity -= 0.05;
			}
			else if(Type == "HeavyFog")
			{
				Severity -= 0.1;
			}
			else if(Type == "Rain")
			{
				Severity -= 0.02;
			}
		}
	}
}

