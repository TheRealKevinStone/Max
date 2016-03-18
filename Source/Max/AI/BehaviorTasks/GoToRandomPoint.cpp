// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "GoToRandomPoint.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

EBTNodeResult::Type UGoToRandomPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	else
	{
		Origin = CurrentBanditController->GetCharacter()->GetActorLocation();
		const float SearchRadius = 500.f;
		const FVector RandomLocation = UNavigationSystem::GetRandomReachablePointInRadius(CurrentBanditController, Origin, SearchRadius);

		if (RandomLocation != FVector::ZeroVector)
		{
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID(), RandomLocation);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
	

}

