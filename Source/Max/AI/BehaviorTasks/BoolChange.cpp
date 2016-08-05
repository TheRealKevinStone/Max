// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BoolChange.h"

EBTNodeResult::Type UBoolChange::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!GetWorld())
	{
		return EBTNodeResult::Failed;
	}
	if (!CurrentBanditController)
	{
		Controller = OwnerComp.GetAIOwner();
		CurrentBanditController = Cast<ABanditController>(Controller);
	}
	if (CurrentBanditController)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("PlayerSpotted"), true);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("PlayerNearby"), true);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
