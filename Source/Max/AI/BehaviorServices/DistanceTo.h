// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "CharacterControls/MaxCharacter.h"
#include "AI/BanditController.h"
#include "DistanceTo.generated.h"

/**
 * 
 */
UCLASS()
class MAX_API UDistanceTo : public UBTService_BlackboardBase
{
	GENERATED_BODY()

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	float Distance = 0.0f;
	


	
};
