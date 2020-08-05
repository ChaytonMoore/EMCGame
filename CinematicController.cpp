// Fill out your copyright notice in the Description page of Project Settings.


#include "CinematicController.h"
#include "GenericFunctions.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACinematicController::ACinematicController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("RootScene"));
	RootComponent = BaseComponent;

	TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("BaseComponent"));
	//TextRender->AttachToComponent(BaseComponent, FAttachmentTransformRules::);
	TextRender->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	TextRender->XScale = 0.9;
	TextRender->WorldSize = 8;
	TextRender->Mobility = EComponentMobility::Movable;
	TextRender->SetRelativeLocation(FVector(-95,0,-40));
	TextRender->SetRelativeRotation(FRotator(0, 0, 180));
	

}

// Called when the game starts or when spawned
void ACinematicController::BeginPlay()
{
	Super::BeginPlay();
	//Sets the camera being used to the cinematic one
	UUserWidget* SpawnedWidget;
	if (WidgetToSpawn)
	{
		SpawnedWidget = CreateWidget(GetWorld(), WidgetToSpawn);
		/** Make sure widget was created */
		if (SpawnedWidget)
		{
			/** Add it to the viewport */
			SpawnedWidget->AddToViewport();
		}
	}
	if (Camera)
	{
		UGameplayStatics::GetPlayerController(this, 0)->SetViewTargetWithBlend(Camera, 0);
	}

	//Now to spawn the actors that are needed for the start of the cinematic.
	FActorSpawnParameters SpawnParams;
	for (size_t i = 0; i < StartEntityClases.Num(); i++)
	{
		//For this the lists must be the same size.
		if (StartEntityClases[i] && StartEntites.Num() > i) // Check if valid
		{

			this->GetWorld()->SpawnActor<ACinematicEntity>(StartEntityClases[i], StartEntites[i].GetLocation(), StartEntites[i].GetRotation().Rotator(), SpawnParams);
		}
	}
}

// Called every frame
void ACinematicController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timer += DeltaTime;

	for (size_t i = 0; i < DialogueData.Num(); i++)
	{
		if (UGenericFunctions::ApproxFloat(Timer,DialogueData[i].AppearTime))
		{
			TextRender->SetText(DialogueData[i].Contents);
			CurrentText = DialogueData[i].Contents;
		}
		else if (UGenericFunctions::ApproxFloat(Timer, DialogueData[i].DisappearTime))
		{
			TextRender->SetText(FText::FromString(""));
			CurrentText = FText::FromString("");
		}

	}

	for (size_t i = 0; i < TeleportData.Num(); i++)
	{
		if (UGenericFunctions::ApproxFloat(TeleportData[i].Time, Timer))
		{
			Camera->TeleportTo(TeleportData[i].Location,TeleportData[i].Rotation);
		}
	}

	for (size_t i = 0; i < MovementData.Num(); i++)
	{
		if (Timer>MovementData[i].StartTime && Timer<MovementData[i].EndTime)
		{
			Camera->AddActorWorldOffset(MovementData[i].DeltaMovement * DeltaTime);
			Camera->AddActorWorldRotation(MovementData[i].DeltaRotation * DeltaTime);
			//AddActorWorldRotation(FRotator((MovementData[i].DeltaRotation * DeltaTime).Roll,0, 0));
			
			
		}
	}

	if (Timer > Endtime)
	{
		FLatentActionInfo LatentInfo;
		UGameplayStatics::LoadStreamLevel(this->GetWorld(), LevelToLoad, true, true, LatentInfo);

	}

	//SetActorLocation(FVector(Camera->GetActorLocation().X - 1000, Camera->GetActorLocation().Y, Camera->GetActorLocation().Z - 100));
	//FTransform a;
	//a = FTransform(FQuat(0,0,0,0),FVector(0,0,-700),FVector(0,0,180));
	//FVector a = FVector(-95, 0, -40);
	//FVector b = Camera->GetActorForwardVector();
	//b = Camera->GetActorLocation() + a * b;
	//SetActorLocation(Camera->GetActorLocation());
	//AddActorLocalOffset(FTransform::TransformVector(FVector(-95,0,-40)));
	//FRotator c = FRotator(0, 0,Camera->GetActorRotation().Yaw +180);


	//AddActorLocalOffset(Camera->GetTransform().TransformVector(FVector(95,0,-40)));
	//SetActorRelativeRotation(c);
	//SetActorRotation(FRotator(0,0,0));
	//SetActorTransform(Camera->GetActorTransform());

	//AddActorLocalRotation(FRotator(0,0, GetActorRotation().Yaw + 180));
	//if (Camera->GetActorRotation() == FRotator(0,0,0))
	//{
	//	SetActorRotation(FRotator(0,0,0));
		//Resets the rotation if it can to try to avoid it going too far of.
	//}
}

