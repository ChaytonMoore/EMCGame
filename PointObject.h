// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "PointObject.generated.h"

UCLASS()
class EMCGAME_API APointObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APointObject();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		APointObject* NextNode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool ReInit;
	UPROPERTY()
		UArrowComponent* Arrow1;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

};
