// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "MyBTTask_ResetStatusAilment.h"

EBTNodeResult::Type UMyBTTask_ResetStatusAilment::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!GetWorld())
	{
		return EBTNodeResult::Failed;
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("isFrozen"), false);
		return EBTNodeResult::Succeeded;
	}
}



