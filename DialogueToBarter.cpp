// Fill out your copyright notice in the Description page of Project Settings.


#include "Scripting/DialogueToBarter.h"
#include "UObject/ConstructorHelpers.h"


ADialogueToBarter::ADialogueToBarter()
{
	static ConstructorHelpers::FObjectFinder<UUserWidget> WidgetToSpawnRef(TEXT("WidgetBlueprint'/Game/Mechanics/Barter/BarterWidget.BarterWidget'"));
	if (WidgetToSpawnRef.Succeeded())
	{
		WidgetToSpawn = WidgetToSpawnRef.Object;
	}
}

void ADialogueToBarter::BeginPlay()
{
	Super::BeginPlay();
	//UUserWidget* WidgetRef = CreateWidget<UUserWidget>(this, WidgetToSpawn);
	
}

