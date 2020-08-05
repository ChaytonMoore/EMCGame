// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CineCameraActor.h"
#include "CinematicEntity.h"
#include "Components/TextRenderComponent.h"
#include "Components/SceneComponent.h"
#include "Blueprint/UserWidget.h"
#include "CinematicController.generated.h"


USTRUCT(BlueprintType)
struct FCutsceneCameraTeleportsStruct
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		float Time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FVector Location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FRotator Rotation;

};

USTRUCT(BlueprintType)
struct FCutsceneDialogueStruct
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		float AppearTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		float DisappearTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FText Contents;
};

USTRUCT(BlueprintType)
struct FCameraMovementStruct
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		float StartTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		float EndTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FVector DeltaMovement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FRotator DeltaRotation;

};

UCLASS()
class EMCGAME_API ACinematicController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACinematicController();
	UTextRenderComponent * TextRender;
	
	USceneComponent* BaseComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FText CurrentText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		TSubclassOf<UUserWidget> WidgetToSpawn;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FName LevelToLoad;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		float Endtime;

private:
	UPROPERTY()
		float Timer;
	UPROPERTY(EditAnywhere)
		ACineCameraActor* Camera;
	UPROPERTY(EditAnywhere)
		TArray<FCameraMovementStruct> MovementData;
	UPROPERTY(EditAnywhere)
		TArray<FCutsceneDialogueStruct> DialogueData;
	UPROPERTY(EditAnywhere)
		TArray<FCutsceneCameraTeleportsStruct> TeleportData;
	UPROPERTY(EditAnywhere)
		TArray<FTransform> StartEntites;
	UPROPERTY(EditAnywhere)
		TArray< TSubclassOf<ACinematicEntity>> StartEntityClases;
		

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
