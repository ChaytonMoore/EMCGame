// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "FollowingTextRender.generated.h"

UCLASS()
class EMCGAME_API AFollowingTextRender : public AActor
{
	GENERATED_BODY()
	
	
public:	
	// Sets default values for this actor's properties
	AFollowingTextRender();
	UTextRenderComponent * TextRender;
	UPROPERTY()
		//When the actor is spawned it will have a time assigned to it, which will decrement until it reaches 0. when that happens the actor will be destroyed.
		float Time;
	UPROPERTY()
		FText TextToRender;
	UPROPERTY()
		AActor* ActorToFollow;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
