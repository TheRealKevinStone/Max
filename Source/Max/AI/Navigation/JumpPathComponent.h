// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Navigation/PathFollowingComponent.h"
#include "JumpPathComponent.generated.h"

/**
 * 
 This will create a custom path following component to handle jumping. 
  The function we need to override to be able to detect jumping is SetMoveSegment so let's declare that as well.
 */

class UNavMovementComponent;
class UCharacterMovementComponent;


UCLASS()
class MAX_API UJumpPathComponent : public UPathFollowingComponent
{
	GENERATED_BODY()
	
protected:

	//Cached UCharacterMovementComponent
	UPROPERTY(transient)
	UCharacterMovementComponent* CharacterMoveComp;

public:
	//used to detect properties of a path's segment a character is about to follow 
	virtual void SetMoveSegment(int32 SegmentStartIndex) override;

	//used to cache UCharacterMovementComponent we're using in SetMoveSegment implementation
	virtual void SetMovementComponent(UNavMovementComponent* MoveComp) override;
	
	
};
