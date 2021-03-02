// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GenericCollider.generated.h"

UCLASS()
class EMCGAME_API AGenericCollider : public AActor
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
		class UBoxComponent* TriggerCapsule;
	
public:	
	// Sets default values for this actor's properties
	AGenericCollider();
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual void PlayerCollide();
	UFUNCTION()
		void NonPlayerCollide(AActor* OtherActor);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
