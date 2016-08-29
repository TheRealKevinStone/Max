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
	//Current Speed of player
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;

	//Is player dashing
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDash;
	
	//Is player jumping
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsJumping;

	//Is player casting anything?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isCasting;

	//FireDart/Gatling
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bLightningBolt;
	//Rock Punch
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRockPunch;
	//Ice Block
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIceBlock;
	//Fireball
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bFireBall;


public:
	virtual void NativeUpdateAnimation(float DeltaTime) override;
	


	
	
};
