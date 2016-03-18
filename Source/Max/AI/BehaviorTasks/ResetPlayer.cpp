// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "ResetPlayer.h"

EBTNodeResult::Type UResetPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!GetWorld())
	{
		return EBTNodeResult::Failed;
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("MaxCharacter"), NULL);
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat(TEXT("DistanceToPlayer"), 0.f);
		return EBTNodeResult::Succeeded;
	}


}


