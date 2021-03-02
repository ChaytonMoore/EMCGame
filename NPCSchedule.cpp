// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCSchedule.h"

void UNPCSchedule::ScheduleDecider(AEntity * Caller, FString PreviousState, FString NewState)
{
	//This will contain the state transitions.
	//I think how combat will work is that factions will have other factions they are enemies with and will fight them. 
	//Since right now the factions struct is in blueprints I might move it to a new UObject just for storing data.


	if (!Caller->Agro) //Just check the ai is not fighting to stop weird stuff from happening.
	{
		if (PreviousState == "None") //State transitions, if the AI doesn't have anything 
		{
			if (NewState == "GoHome")
			{
				Caller->State = "GoHome";
			}
		}
	}
}



