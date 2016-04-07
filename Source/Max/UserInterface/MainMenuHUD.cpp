// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "MainMenuHUD.h"
#include "SMainMenuUI.h"
#include "Engine.h"

AMainMenuHUD::AMainMenuHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)

{
}

void AMainMenuHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SAssignNew(MainMenuUI, SMainMenuUI).MainMenuHUD(this);

	if (GEngine->IsValidLowLevel())
	{
		GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(MainMenuUI.ToSharedRef()));
	}
}
