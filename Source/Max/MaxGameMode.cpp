// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "MaxGameMode.h"
#include "CharacterControls/MaxCharacter.h"
#include "UserInterface/HealthBar.h"
//#include "UserInterface/ManaBar.h"
//#include "UserInterface/StaminaBar.h"

AMaxGameMode::AMaxGameMode()
{
	//// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/CharacterControls/MyMaxCharacter.MyMaxCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}

	HUDClass = AHealthBar::StaticClass();
	/*HUDClass = AManaBar::StaticClass();
	HUDClass = AStaminaBar::StaticClass();*/

}