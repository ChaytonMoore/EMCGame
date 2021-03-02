// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerComment.h"
#include "Engine.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"


void APlayerComment::PlayerCollide()
{
	static ConstructorHelpers::FObjectFinder<class UUserWidget> SpeechWidgetRef(TEXT("WidgetBlueprint'/Game/Mechanics/PlayerCharacter/PlayerSpeech.PlayerSpeech'"));

	//if (SpeechWidgetRef.Succeeded)
	//{
		//TSubclassOf<class UUserWidget> midstateVar = SpeechWidgetRef.GetReferencerName;
	//	TSubclassOf<UUserWidget>* SpeechWidget = CreateWidget<TSubclassOf<UUserWidget>>(GetWorld(), midstateVar, FName(TEXT("UIWidgetSpeech")));
	//}

}
