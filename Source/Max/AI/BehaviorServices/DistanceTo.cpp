// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "DistanceTo.h"

void UDistanceTo::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//Grabbing blackboard from current bandit
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	//Find player
	AActor* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	//Get controller of bandit
	ABanditController* AIController = Cast<ABanditController>(Blackboard->GetOwner());

	//check if their valid then get distance between player and bandit
	if (AIController && Player)
	{
		Distance = FVector::Dist(Player->GetActorLocation(), AIController->GetPawn()->GetActorLocation());

		Blackboard->SetValue<UBlackboardKeyType_Float>(BlackboardKey.GetSelectedKeyID(),Distance);
	}

}
