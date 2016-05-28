// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "StaminaBar.generated.h"

/**
 * 
 */
UCLASS()
class MAX_API AStaminaBar : public AHUD
{
	GENERATED_UCLASS_BODY()
	
	virtual void DrawHUD() override;

	void DrawStaminaBar();

	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* StaminaBarTexture;
};
