// Fill out your copyright notice in the Description page of Project Settings.


#include "CinematicEntity.h"

ACinematicEntity::ACinematicEntity()
{


}

void ACinematicEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timer += DeltaTime;
}
