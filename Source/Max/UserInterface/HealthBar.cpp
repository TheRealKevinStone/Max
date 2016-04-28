// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "HealthBar.h"
#include "Engine/Canvas.h"



AHealthBar::AHealthBar(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> TextPath(TEXT("/Game/UI/RedTemp"));

	HealthBarTexture = TextPath.Object;
}

void AHealthBar::DrawHUD()
{
	Super::DrawHUD();

	DrawHealthBar();
}

void AHealthBar::DrawHealthBar()
{
	float ScaleHealthUI = Canvas->ClipY / Canvas->ClipX;

	FCanvasIcon HealthBarIcon = UCanvas::MakeIcon(HealthBarTexture, 20, 20, 0);

	Canvas->DrawIcon(HealthBarIcon, Canvas->SizeX, 50);
}
