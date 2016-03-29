// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class MAX_API SMainMenuUI : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMainMenuUI)
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<class AMainMenuHUD>, MainMenuHUD)
	SLATE_END_ARGS()

		//constructs and lays out the main menu UI widget
	/** Constructs this widget with InArgs */
	void Construct(const FArguments& args);

	//Handler for start game, called MainMenuUI's start button event/function
	FReply StartButtonClicked();

	//Handler for start game, called MainMenuUI's start button event/function
	FReply ExitButtonClicked();

	//Stores a weak reference to the HUD controlling this class.
	TWeakObjectPtr<class AMainMenuHUD> MainMenuHUD;
};
