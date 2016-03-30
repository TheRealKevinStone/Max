// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "AI/AI_Weapons/TickerController.h"
#include "AIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "StopBehaviorTree.generated.h"

/**
 * 
 */
UCLASS()
class MAX_API UStopBehaviorTree : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;
	
	
};
