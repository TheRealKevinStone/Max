// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI/BanditCharacter.h"
#include "AI/AI_Weapons/BaseTicker.h"
#include "TickerBandit.generated.h"

/**
 * 
 */
UCLASS()
class MAX_API ATickerBandit : public ABanditCharacter
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "TickerBandit")
	void ThrowTicker();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TickerImpulse;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseTicker> TickerClass;

	
};
