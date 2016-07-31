// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "MaxSpellbook.h"

MaxSpellbook::MaxSpellbook()
{
}

MaxSpellbook::~MaxSpellbook()
{
}

void MaxSpellbook::RockPunch(FVector OriginPoint, FRotator ForwardRotation)
{
	//const FVector StartTrace = OriginPoint; // trace start is the camera location
	//const FVector Direction = ForwardRotation.Vector(); // Get a unit vector pointing forward from our start location
	//const FVector EndTrace = StartTrace + Direction * 500; // Define the distance of the Trace

	//// Perform trace to retrieve hit info
	//FCollisionQueryParams TraceParams(FName(TEXT("GrabTrace")), true, this);
	//TraceParams.bTraceAsyncScene = true;
	//TraceParams.bReturnPhysicalMaterial = true;

	//FHitResult ObjectHit(ForceInit);
	//GetWorld()->LineTraceSingleByChannel(ObjectHit, StartTrace, EndTrace, COLLISION_INTERACTABLE, TraceParams); // simple trace function
}