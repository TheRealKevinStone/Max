// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "BaseTicker.h"
#include "Ticker_AnimInstance.h"

void UTicker_AnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	ABaseTicker* Owner = Cast<ABaseTicker>(TryGetPawnOwner());

	if (Owner)
	{
		Speed = Owner->GetVelocity().Size();
	}
}
