// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "AI/BanditController.h"
#include "AIController.h"
#include "BoolChange.generated.h"

/**
 * 
 */
UCLASS()
class MAX_API UBoolChange : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;
	
public:
	AAIController* Controller;
	ABanditController* CurrentBanditController;

	bool PlayerNearby;

	bool PlayerSpotted;
	
	
	
};
