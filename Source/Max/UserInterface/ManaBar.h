// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "ManaBar.generated.h"

/**
 * 
 */
UCLASS()
class MAX_API AManaBar : public AHUD
{
	GENERATED_UCLASS_BODY()
	
	virtual void DrawHUD() override;
	
	void DrawManaBar();

	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* ManaBarTexture;
};
