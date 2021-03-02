// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericCollider.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"

// Sets default values
AGenericCollider::AGenericCollider()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TriggerCapsule = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Capsule Component"));
	TriggerCapsule->InitBoxExtent(FVector(100,100,100));
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetupAttachment(RootComponent);
	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &AGenericCollider::OnOverlapBegin);

}

// Called when the game starts or when spawned
void AGenericCollider::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGenericCollider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGenericCollider::PlayerCollide()
{
#include "Engine.h"
}

void AGenericCollider::NonPlayerCollide(AActor* OtherActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin for non player")); //Hopefully this won't show up too much
}

void AGenericCollider::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp )
	{
		if (GetWorld()->GetFirstPlayerController()->GetPawn() == OtherActor)
		{
			//This is called if the collidin actor is the player.
			PlayerCollide();
		}
		else
		{
			NonPlayerCollide(OtherActor);
		}
	}
}

void Test()

{

}

