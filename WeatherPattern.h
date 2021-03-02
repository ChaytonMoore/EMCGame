// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "WeatherPattern.generated.h"

UCLASS()
class EMCGAME_API AWeatherPattern : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeatherPattern();
	UBoxComponent* CollisionBox;
	UPROPERTY()
		bool UpdateTick = false;
	UPROPERTY()
		bool isNight;
	UPROPERTY()
		float Severity;
	UPROPERTY()
		FString Type;
	UFUNCTION(BlueprintCallable)
		void FogNightTickEvent();
	UFUNCTION(BlueprintCallable)
		void HeavyFogNightTickEvent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
