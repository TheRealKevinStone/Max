// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "HealthBar.generated.h"

/**
 * 
 */
UCLASS()
class MAX_API AHealthBar : public AHUD
{
	GENERATED_UCLASS_BODY()

	virtual void DrawHUD() override;

	void DrawHealthBar();
	
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* HealthBarTexture;
	
	
	
};
