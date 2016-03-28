// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "TickerBandit.h"


void ATickerBandit::ThrowTicker()
{
	if (TickerClass)
	{
		FVector Forward = ProjectilePoint->GetForwardVector();
		FVector Up = ProjectilePoint->GetUpVector();
		FVector Curve = Forward + Up;
		ABaseTicker* Ticker=GetWorld()->SpawnActor<ABaseTicker>(TickerClass, ProjectilePoint->GetComponentLocation(), ProjectilePoint->GetComponentRotation());
		
		if (Ticker)
		{
			//Ticker->CapsuleComponent->AddImpulse(Curve);
		}
	}
}

