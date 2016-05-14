// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "ManaBar.h"
#include "Engine/Canvas.h"

AManaBar::AManaBar(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> TextPath(TEXT("/Game/UI/TempMana"));

	ManaBarTexture = TextPath.Object;
}

int32 TestMana = 200;

void AManaBar::DrawHUD()
{
	Super::DrawHUD();

	DrawManaBar();
}

void AManaBar::DrawManaBar()
{
	float ScaleManaUI = Canvas->ClipY / Canvas->ClipX;

	if (GetAsyncKeyState(VK_NUMPAD8) != 0 && TestMana < 196)
	{
		TestMana += 5;
	}

	if (GetAsyncKeyState(VK_NUMPAD5) != 0 && TestMana > 5)
	{
		TestMana -= 5;
	}

	FCanvasIcon ManaBarIcon = UCanvas::MakeIcon(ManaBarTexture, 0, 0, TestMana, 20);

	Canvas->DrawIcon(ManaBarIcon, (Canvas->SizeX) / 2.5, 20, ScaleManaUI);
}


