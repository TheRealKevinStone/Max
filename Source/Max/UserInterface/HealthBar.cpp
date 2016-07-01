// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "HealthBar.h"
#include "CharacterControls/MaxCharacter.h"
#include "Engine/Canvas.h"

AHealthBar::AHealthBar(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> HealthTextPath(TEXT("/Game/UI/TempHealth"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> ManaTextPath(TEXT("/Game/UI/TempMana"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> StaminaTextPath(TEXT("/Game/UI/TempStamina"));

	HealthBarTexture = HealthTextPath.Object;
	ManaBarTexture = ManaTextPath.Object;
	StaminaBarTexture = StaminaTextPath.Object;
}

int32 TestHealth = 350;
int32 TestMana = 350;
int32 TestStamina = 350;


void AHealthBar::DrawHUD()
{
	Super::DrawHUD();

	DrawHealthBar();
	
	DrawManaBar();
	
	DrawStaminaBar();
}

void AHealthBar::DrawHealthBar()
{

	/*if (!HealthBarTexture)
	{
		HealthBarTexture = LoadAsset("/Game/UI/TempHealth");
		
		if (!HealthBarTexture)
		{
			return;
		}
	}*/

	float ScaleHealthUI = Canvas->ClipY / Canvas->ClipX;

	/*if (GetAsyncKeyState(VK_NUMPAD7) != 0 && TestHealth < 96)
	{
		TestHealth += 5;
	}

	if (GetAsyncKeyState(VK_NUMPAD4) != 0 && TestHealth > 5)
	{
		TestHealth -= 5;
	}*/

	FCanvasIcon HealthBarIcon = UCanvas::MakeIcon(HealthBarTexture, 0, 0, TestHealth, 20);

	Canvas->DrawIcon(HealthBarIcon, (Canvas->SizeX)/ 10, 20, ScaleHealthUI);
}

void AHealthBar::DrawManaBar()
{

	/*if (!ManaBarTexture)
	{
		ManaBarTexture = LoadAsset("/Game/UI/TempMana");

		if (!ManaBarTexture)
		{
			return;
		}
	}*/

	float ScaleManaUI = Canvas->ClipY / Canvas->ClipX;

	if (GetAsyncKeyState(VK_NUMPAD8) != 0 && TestMana < 96)
	{
		TestMana += 5;
	}

	if (GetAsyncKeyState(VK_NUMPAD5) != 0 && TestMana > 5)
	{
		TestMana -= 5;
	}

	FCanvasIcon ManaBarIcon = UCanvas::MakeIcon(ManaBarTexture, 0, 0, TestMana, 20);

	Canvas->DrawIcon(ManaBarIcon, (Canvas->SizeX) / 10, 40, ScaleManaUI);
}


void AHealthBar::DrawStaminaBar()
{
	/*if (!StaminaBarTexture)
	{
		StaminaBarTexture = LoadAsset("/Game/UI/StaminaBarTexture");

		if (!StaminaBarTexture)
		{
			return;
		}
	}*/

	float ScaleStaminaUI = Canvas->ClipY / Canvas->ClipX;

	if (GetAsyncKeyState(VK_NUMPAD9) != 0 && TestStamina < 96)
	{
		TestStamina += 5;
	}

	if (GetAsyncKeyState(VK_NUMPAD6) != 0 && TestStamina > 5)
	{
		TestStamina -= 5;
	}

	FCanvasIcon StaminaBarIcon = UCanvas::MakeIcon(StaminaBarTexture, 0, 0, TestStamina, 20);

	Canvas->DrawIcon(StaminaBarIcon, (Canvas->SizeX) / 10, 60, ScaleStaminaUI);
}

//UTexture2D* AHealthBar::LoadAsset(FString aPath)
//{
//
//	FStreamableManager* stream = new FStreamableManager;
//	
//	FStringAssetReference ref(aPath);
//
//	return Cast<UTexture2D>(stream->SynchronousLoad(ref));
//}
