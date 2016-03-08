// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "JumpPathComponent.h"
#include "NavArea_Jump.h"

void UJumpPathComponent::SetMoveSegment(int32 SegmentStartIndex)
{
	Super::SetMoveSegment(SegmentStartIndex);

	if (CharacterMoveComp != NULL)
	{
		const FNavPathPoint& SegmentStart = Path->GetPathPoints()[MoveSegmentStartIndex];

		if (FNavAreaHelper::HasJumpFlag(SegmentStart))
		{
			//jump! well.. fly-in-straight-line!
			CharacterMoveComp->SetMovementMode(MOVE_Flying);
		}
		else
		{
			//regular move
			CharacterMoveComp->SetMovementMode(MOVE_Walking);
		}
	}

}

void UJumpPathComponent::SetMovementComponent(UNavMovementComponent* MoveComp)
{
	Super::SetMovementComponent(MoveComp);

	CharacterMoveComp = Cast<UCharacterMovementComponent>(MovementComp);
}
