// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "StopBehaviorTree.h"

EBTNodeResult::Type UStopBehaviorTree::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!GetWorld())
	{
		return EBTNodeResult::Failed;
	}

	AAIController* DefaultController = OwnerComp.GetAIOwner();
	ATickerController* CurrTickerController = Cast<ATickerController>(DefaultController);

	if (CurrTickerController)
	{
		CurrTickerController->Sleep();
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;

	}
	return EBTNodeResult::Succeeded;
}


