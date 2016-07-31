// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Spells/FireDart.h"

/**
 * 
 */
class MAX_API MaxSpellbook
{
public:
	MaxSpellbook();
	~MaxSpellbook();

public:
	AFireDart* FireDart;

	float FireDartMana = FireDart->ReturnManaCost();

	void RockPunch(FVector OriginPoint, FRotator ForwardRotation);
};
