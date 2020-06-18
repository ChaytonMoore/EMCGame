// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCreationInit.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"


//Lets not use this code as for somereason the asset can't be found despite the fact it exists in the correct place.
// Sets default values
ACharacterCreationInit::ACharacterCreationInit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true; 
	static ConstructorHelpers::FObjectFinder<UUserWidget> WidgetRef(TEXT("WidgetBlueprint'/Game/Mechanics/CharacterCreator/CharacterCreator.CharacterCreator'")); 
	//This is going to need to succeed.
	UUserWidget* a = WidgetRef.Object;
	WidgetToCreateClass = a->StaticClass();
	//TSubclassOf<UUserWidget> b = a::StaticClass();
}

// Called when the game starts or when spawned
void ACharacterCreationInit::BeginPlay()
{
	Super::BeginPlay();
	FLatentActionInfo LatentInfo;
	CreateWidgetObj = CreateWidget<UUserWidget>(GetWorld(), WidgetToCreateClass);
	UGameplayStatics::LoadStreamLevel(this, "CharCreationSpace", true, true, LatentInfo);
	CreateWidgetObj->AddToViewport();
	APlayerController* PlayerControllerRef = GetWorld()->GetFirstPlayerController();
	PlayerControllerRef->bShowMouseCursor = true;
}

// Called every frame
void ACharacterCreationInit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

