// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "AI/TestTargetPoint.h"
#include "AI/BanditController.h"
#include "AIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "GoToWaypoint.h"

EBTNodeResult::Type UGoToWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!GetWorld())
	{
		return EBTNodeResult::Failed;
	}
	AAIController* MyController = OwnerComp.GetAIOwner();
	ABanditController* CurrBanditController = Cast<ABanditController>(MyController);

	if (CurrBanditController)
	{
		ATestTargetPoint* CurrentWaypoint = CurrBanditController->CurrentWaypoint();
		if (CurrentWaypoint)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("CurrentTarget"), CurrentWaypoint);
			return EBTNodeResult::Succeeded;
		}
		else
		{
			return EBTNodeResult::Failed;
		}
	}
	else
	{
		return EBTNodeResult::Failed;
	}
	//for (TActorIterator<ATestTargetPoint> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	//{
	//	ATestTargetPoint* Waypoint = *ActorItr;
	//	if (Waypoint)
	//	{
	//		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target1"), Waypoint);
	//		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("CurrentTarget"), Waypoint);
	//		
	//		return EBTNodeResult::Succeeded;
	//	}
	//}
	return EBTNodeResult::Failed;
}


