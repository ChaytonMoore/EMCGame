// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Humanoid.h"
#include "Blueprint/UserWidget.h"
#include "DialogueToBarter.generated.h"

UCLASS()
class EMCGAME_API ADialogueToBarter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADialogueToBarter();
	UPROPERTY(EditAnywhere, Category = "Default") //Should be set on creation
		AHumanoid* Caller;

private:
	UPROPERTY()
		class UUserWidget* WidgetToSpawn;
		

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

};
