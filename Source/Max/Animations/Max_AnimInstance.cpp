// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "CharacterControls/MaxCharacter.h"
#include "Max_AnimInstance.h"

void UMax_AnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	AMaxCharacter* Owner = Cast<AMaxCharacter>(TryGetPawnOwner());
	if (Owner)
	{
		
		Speed = Owner->GetVelocity().Size();
		bDash = Owner->isDashing;
		bIsJumping = Owner->IsJumpProvidingForce();
		bSpellOne = Owner->bIsCastingLightningBolt;
		bSpellTwo = Owner->bIsCastingRockPunch;
		bSpellThree = Owner->bIsCastingIceBlock;
		bSpellFour = Owner->bIsCastingFireBall;

	}
}


