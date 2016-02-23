// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "BanditAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MAX_API UBanditAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bEnableDamageState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bEnableDeathState;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool EnableShoot;
public:
	virtual void NativeUpdateAnimation(float DeltaTime) override;
	
	
};
