// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "Ticker_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MAX_API UTicker_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableExplodeState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableDeadState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isFrozen;

public:
	virtual void NativeUpdateAnimation(float DeltaTime) override;
	
	
};
