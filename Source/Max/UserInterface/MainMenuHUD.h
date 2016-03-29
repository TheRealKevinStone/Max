// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class MAX_API AMainMenuHUD : public AHUD
{
	//GENERATED_BODY()
	GENERATED_UCLASS_BODY()

	//Initializes the Slate UI, adds it as a widget content to game viewport
	virtual void PostInitializeComponents() override;

	//Called when Start is clicked
	UFUNCTION(BlueprintImplementableEvent, Category = "Menus|Main Menu")
		 void StartButtonClicked();

	//Called when Exit is clicked
	UFUNCTION(BlueprintImplementableEvent, Category = "Menus|Main Menu")
		 void ExitButtonClicked();

	//Reference to the Main Menu Slate UI
	TSharedPtr<class SMainMenuUI> MainMenuUI;

	//void LoginFailed(const FString& log);

	
	
	
	
};
