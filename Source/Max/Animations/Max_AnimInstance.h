// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "Max_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MAX_API UMax_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDash;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsJumping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSpellOne;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSpellTwo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSpellThree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSpellFour;

public:
	virtual void NativeUpdateAnimation(float DeltaTime) override;
	


	
	
};
