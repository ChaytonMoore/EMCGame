// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldFunctions.h"
#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

void UWorldFunctions::InitBeachLevel(UUserWidget* caller)
{
	FName LevelToLoad = "StartBeach";
	FLatentActionInfo LatentInfo;
	//UGameplayStatics::LoadStreamLevel(caller->GetWorld(), LevelToLoad, true, true, LatentInfo);
	UGameplayStatics::LoadStreamLevel(caller->GetWorld(), "Main", true, true, LatentInfo);
	UGameplayStatics::UnloadStreamLevel(caller->GetWorld(), "CharCreationSpace", LatentInfo, false);
	APlayerController* PlayerControllerRef = caller->GetWorld()->GetFirstPlayerController();
	PlayerControllerRef->bShowMouseCursor = false;
	APawn* PlayerPawnRef = PlayerControllerRef->GetPawn();
	PlayerPawnRef->SetActorLocation(FVector(-350,-850,1285));
}

void UWorldFunctions::InitStreamLevel(UObject* caller, FName Level,TArray<FName> UnloadLevel)
{
	FLatentActionInfo LatentInfo;
	UGameplayStatics::LoadStreamLevel(caller->GetWorld(), Level, true, true, LatentInfo);
	for (size_t i = 0; i < UnloadLevel.Num(); i++)
	{
		UGameplayStatics::UnloadStreamLevel(caller->GetWorld(), UnloadLevel[i], LatentInfo, false);
	}
	
}
