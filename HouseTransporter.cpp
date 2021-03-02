// Fill out your copyright notice in the Description page of Project Settings.


#include "HouseTransporter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"

// Sets default values
AHouseTransporter::AHouseTransporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TriggerCapsule = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Capsule"));
	//TriggerCapsule->InitBoxSize(55.f, 96.0f);;
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetupAttachment(RootComponent);

	//TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &AHouseTransporter::OnOverlapBegin);
	playerchar = (AEntity*)UGameplayStatics::GetPlayerCharacter(this, 0);


}

// Called when the game starts or when spawned
void AHouseTransporter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHouseTransporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//The bool overlapping is set in the playerclass blueprint.
	//if (overlapping && playerchar->activate)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Transere through door"));
		//playerchar->activate = false;
		//FLatentActionInfo LatentInfo;
		//UGameplayStatics::LoadStreamLevel(this, level, true, true, LatentInfo);
		//UGameplayStatics::UnloadStreamLevel(this, "Main2", LatentInfo, true);
		//Need someway to transfer data, will use the database.

	//}

}

//void AHouseTransporter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
	//if (OtherActor && (OtherActor != this) && OtherComp)
	//{
		//ACharacter* playerchar = UGameplayStatics::GetPlayerCharacter(this, 0);
		//Code elsewhere will mean that a ui element appears 
		
	//}
//}

