// Fill out your copyright notice in the Description page of Project Settings.


#include "PublicScripting/BarracksDoor.h"
#include "Kismet/GameplayStatics.h"

ABarracksDoor::ABarracksDoor()
{
	TArray<AActor*> OutputList; //This function requires an input it will crash if it doesn't have one.
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADataBase::StaticClass(), OutputList);
	ADataBase* TempDataBase;
	ADataBase* Output = nullptr;
	for (size_t i = 0; i < (OutputList.Num()); i++)
	{
		TempDataBase = (ADataBase*)OutputList[i];
		if (!TempDataBase->bBackup)
		{
			Output = TempDataBase;
		}

		if (Output == nullptr)
		{
			Output = (ADataBase*)OutputList[0];
		}
	}
	DataBase = Output;
}

void ABarracksDoor::DelayedSpawnGuard()
{
	//After a short wait the guard will be spawned, this is used to stop the guards from clipping through each other

}


void ABarracksDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Now to see if it is day, if it is day and there is a guard in the barracks then they should be spawned and the number of guards decreased.
	if (DataBase->isNight == false && GuardNumber > 0)
	{
		GuardNumber -= 1;
		bSpawnerOccupied = true;

	}

}
