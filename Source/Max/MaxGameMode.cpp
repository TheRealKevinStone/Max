// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "MaxGameMode.h"
#include "CharacterControls/MaxCharacter.h"
#include "Max/UserInterface/HealthBar.h"

AMaxGameMode::AMaxGameMode()
{
	//// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/CharacterControls/MyMaxCharacter.MyMaxCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}

	HUDClass = AHealthBar::StaticClass();

}