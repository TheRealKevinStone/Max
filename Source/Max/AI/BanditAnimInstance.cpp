// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "BanditCharacter.h"
#include "BanditAnimInstance.h"


void UBanditAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	ABanditCharacter* Owner = Cast<ABanditCharacter>(TryGetPawnOwner());

	if (Owner)
	{
		Speed = Owner->GetVelocity().Size();

	}

}

