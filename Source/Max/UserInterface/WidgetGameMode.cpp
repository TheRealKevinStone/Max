// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "WidgetGameMode.h"
#include "MainMenuHUD.h"

AWidgetGameMode::AWidgetGameMode(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	HUDClass = AMainMenuHUD::StaticClass();

}