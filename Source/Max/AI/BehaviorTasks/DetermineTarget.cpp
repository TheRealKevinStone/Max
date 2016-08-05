// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "DetermineTarget.h"

EBTNodeResult::Type UDetermineTarget::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
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
	PlayerNearby = OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("PlayerNearby"));
	PlayerSpotted = OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("PlayerSpotted"));
	//DistanceToPlayer= OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("DistanceToPlayer"));
	if (PlayerSpotted) 
	{
		//Go to player
		AActor* Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Player")));
		CurrentTarget = Player->GetActorLocation();
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("CurrentTarget"), CurrentTarget);
		return EBTNodeResult::Succeeded;
	}
	else if (!PlayerSpotted&&PlayerNearby)
	{
		//Search for player
		CurrentTarget = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("PlayersLastknownLocation"));
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("CurrentTarget"), CurrentTarget);
		return EBTNodeResult::Succeeded;
	}
	else if (!PlayerNearby)
	{
		//Go back to start point
		CurrentTarget = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("StartPoint"));
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("CurrentTarget"), CurrentTarget);
		return EBTNodeResult::Succeeded;
	}
	//if (DistanceToPlayer >= 250.f)
	//{
	//	//Go to player
	//	AActor* Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Player")));
	//	CurrentTarget = Player->GetActorLocation();
	//	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("CurrentTarget"), CurrentTarget);
	//	OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("PlayerSpotted"), true);
	//	OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("PlayerNearby"), true);

	//	return EBTNodeResult::Succeeded;
	//}
	return EBTNodeResult::Succeeded;
}
