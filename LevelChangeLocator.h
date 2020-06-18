// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "LevelChangeLocator.generated.h"

UCLASS()
class EMCGAME_API ALevelChangeLocator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelChangeLocator();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FString TransitionString;

	UPROPERTY(VisibleAnywhere)
		class UArrowComponent* ArrowComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
