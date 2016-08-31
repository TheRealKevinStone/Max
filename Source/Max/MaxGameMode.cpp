// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "MaxGameMode.h"
#include "CharacterControls/MaxCharacter.h"
#include "UserInterface/HealthBar.h"
#include "Blueprint/UserWidget.h"

void AMaxGameMode::BeginPlay()
{
	//stuff
	ApplyHUDChanges();
}

AMaxGameMode::AMaxGameMode()
{
	//// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/CharacterControls/MyMaxCharacter.MyMaxCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}

	HUDClass = AHealthBar::StaticClass();

	HUDState = EHUDState::HS_Ingame;

}

void AMaxGameMode::ApplyHUDChanges()
{
	//remove previous hud since were applying a new one
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromParent();
	}

	//check hudstate, apply hud to whichever should be open
	switch (HUDState)
	{
		case EHUDState::HS_Ingame:
		{
			ApplyHUD(IngameHUDClass, false, false);
		}

		case EHUDState::HS_Item_Inven:
		{
			ApplyHUD(ItemInvenHUDClass, false, false);
		}

		case EHUDState::HS_Spell_Inven:
		{
			ApplyHUD(SpellInvenHUDClass, false, false);
		}

		default:
		{
			ApplyHUD(IngameHUDClass, false, false);
		}
	}

}

uint8 AMaxGameMode::GetHUDState()
{
	return HUDState;
}

void AMaxGameMode::ChangeHUDState(uint8 NewState)
{
	HUDState = NewState;
	ApplyHUDChanges();
}

bool AMaxGameMode::ApplyHUD(TSubclassOf<class UUserWidget> WidgetToApply, bool ShowMouseCursor, bool EnableClickEvents)
{
	//get refernce to player, and player controller
	//AMaxCharacter* MaxCharacter = Cast<AMaxCharacter>(*TActorIterator<AMaxCharacter>(GetWorld()));
	AMaxCharacter* MaxCharacter = Cast<AMaxCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	APlayerController* MyController = GetWorld()->GetFirstPlayerController();

	//check before applying widget
	if (WidgetToApply != nullptr)
	{
		//mouse events visibility
		MyController->bShowMouseCursor = ShowMouseCursor;
		MyController->bEnableClickEvents = EnableClickEvents;

		//creat widget
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetToApply);

		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
			return true;
		}
		else 
		{ 
			return false; 
		}
	}
	else 
	{ 
		return false; 
	}
}