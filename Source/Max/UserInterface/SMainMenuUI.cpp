// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "SMainMenuUI.h"
#include "SlateOptMacros.h"
#include "Engine.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMainMenuUI::Construct(const FArguments& args)
{

	MainMenuHUD = args._MainMenuHUD;

	//child slot operator will define widgets that are children of
	//the custom (compound) widget; SNew(____)
	ChildSlot
	[
		//
		SNew(SOverlay)
		+ SOverlay::Slot()
		.HAlign(HAlign_Center) //text position (horizontal center)
		.VAlign(VAlign_Top) //text position (vertical top)
		[
			SNew(STextBlock) //where text will fit in
			.ColorAndOpacity(FLinearColor::White) //text color
			.ShadowColorAndOpacity(FLinearColor::Black) //offset shadow underlay color
			.ShadowOffset(FIntPoint(-1, 1)) //offset shadow underlay position
			.Font(FSlateFontInfo("Arial", 26)) //text font and size
			.Text(FText::FromString("Main Menu")) //the text itself (where game title will go)
		]
		+ SOverlay::Slot()
				.HAlign(HAlign_Right)
				.VAlign(VAlign_Bottom)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					[
						SNew(SButton)
						.Text(FText::FromString("Start")) //start button text (to start game)
						.OnClicked(this, &SMainMenuUI::StartButtonClicked)	
					]
					+ SVerticalBox::Slot()
							[
								SNew(SButton)
								.Text(FText::FromString("Quit Game"))
								.OnClicked(this, &SMainMenuUI::ExitButtonClicked)
							]
				]
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FReply SMainMenuUI::StartButtonClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("StartButtonClicked"));
	}

		// actually the BlueprintImplementable function of the HUD is not called; 
		//uncomment if you want to handle the OnClick via Blueprint

		//MainMenuHUD->StartButtonClicked();
		return FReply::Handled(); //to know we've handled the click events
}

FReply SMainMenuUI::ExitButtonClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("ExitButtonClicked"));
	}
	// actually the BlueprintImplementable function of the HUD is not called; 
	//uncomment if you want to handle the OnClick via Blueprint

	//MainMenuHUD->StartButtonClicked();
	return FReply::Handled(); //to know we've handled the click events
}