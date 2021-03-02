// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSpell.h"

// Sets default values
ABaseSpell::ABaseSpell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//UParticleSystemComponent* temp; //Might use this stuff later if what more control from in the data table
	//for (size_t i = 0; i < length; i++)
	//{
	//	temp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("main"));
	//}
	particleFx = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("main"));
	RootComponent = particleFx;
}

// Called when the game starts or when spawned
void ABaseSpell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseSpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

