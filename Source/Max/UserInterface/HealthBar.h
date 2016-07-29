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

public:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ValueUpdate(uint16 BarIndex, float BarValue);

	virtual void DrawHUD() override;

	void DrawHealthBar();
	
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* HealthBarTexture;

	void DrawManaBar();

	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* ManaBarTexture;

	void DrawStaminaBar();

	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* StaminaBarTexture;



	//UTexture2D* LoadAsset(FString aPath);

	float TestHealth;
	float TestMana;
	float TestStamina;
};
