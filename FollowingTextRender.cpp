// Fill out your copyright notice in the Description page of Project Settings.


#include "FollowingTextRender.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFollowingTextRender::AFollowingTextRender()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("BaseComponent"));
	RootComponent = TextRender;
	TextRender->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	TextRender->XScale = 0.9;
	TextRender->WorldSize = 12;
	//TextRender->SetText(TextToRender);
}

// Called when the game starts or when spawned
void AFollowingTextRender::BeginPlay()
{
	Super::BeginPlay();
	TextRender->Text = TextToRender;
	
}

// Called every frame
void AFollowingTextRender::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(ActorToFollow->GetActorLocation()+FVector(0,0,115));
	float YawRot;
	YawRot = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetControlRotation().Yaw;
	YawRot = 180 - (YawRot*(-1));
	SetActorRotation(FRotator(0, YawRot,0));
	Time -= DeltaTime;
	TextRender->SetText(TextToRender);
	if (Time<0)
	{
		Destroy();
	}
}

