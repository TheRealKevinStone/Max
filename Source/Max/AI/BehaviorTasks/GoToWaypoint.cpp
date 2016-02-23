// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "AI/TestTargetPoint.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "GoToWaypoint.h"

EBTNodeResult::Type UGoToWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!GetWorld())
	{
		return EBTNodeResult::Failed;
	}

	for (TActorIterator<ATestTargetPoint> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ATestTargetPoint* Waypoint = *ActorItr;
		if (Waypoint)
		{
			//OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID(), Waypoint);
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), Waypoint);
			
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}


