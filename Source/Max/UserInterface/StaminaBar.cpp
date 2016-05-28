// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "StaminaBar.h"
#include "Engine/Canvas.h"

AStaminaBar::AStaminaBar(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> TextPath(TEXT("/Game/UI/TempStamina"));

	StaminaBarTexture = TextPath.Object;
}

int32 TestStamina = 200;

void AStaminaBar::DrawHUD()
{
	Super::DrawHUD();

	DrawStaminaBar();
}

void AStaminaBar::DrawStaminaBar()
{
	float ScaleManaUI = Canvas->ClipY / Canvas->ClipX;

	if (GetAsyncKeyState(VK_NUMPAD9) != 0 && TestStamina < 196)
	{
		TestStamina += 5;
	}

	if (GetAsyncKeyState(VK_NUMPAD6) != 0 && TestStamina > 5)
	{
		TestStamina -= 5;
	}

	FCanvasIcon StaminaBarIcon = UCanvas::MakeIcon(StaminaBarTexture, 0, 0, TestStamina, 20);

	Canvas->DrawIcon(StaminaBarIcon, (Canvas->SizeX) / 7.5, 20, ScaleManaUI);
}




