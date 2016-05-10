// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "HealthBar.h"
#include "Engine/Canvas.h"



AHealthBar::AHealthBar(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> TextPath(TEXT("/Game/UI/TempHealth"));

	HealthBarTexture = TextPath.Object;
}

int32 TestHealth = 200;

void AHealthBar::DrawHUD()
{
	Super::DrawHUD();

	DrawHealthBar();
}

void AHealthBar::DrawHealthBar()
{
	float ScaleHealthUI = Canvas->ClipY / Canvas->ClipX;

	if (GetAsyncKeyState(VK_NUMPAD7) != 0 && TestHealth < 196)
	{
		TestHealth += 5;
	}

	if (GetAsyncKeyState(VK_NUMPAD4) != 0 && TestHealth > 5)
	{
		TestHealth -= 5;
	}



	FCanvasIcon HealthBarIcon = UCanvas::MakeIcon(HealthBarTexture, 0, 0, TestHealth, 20);

	Canvas->DrawIcon(HealthBarIcon, (Canvas->SizeX)/5, 20, ScaleHealthUI);
}
