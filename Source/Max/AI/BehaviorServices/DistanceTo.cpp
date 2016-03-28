// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "DistanceTo.h"

void UDistanceTo::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//if (BanditController != NULL)
	//{
	//	BanditController = Cast<ABanditController>(Blackboard->GetOwner());
	//}
	//if (TickerController != NULL)
	//{
	//	TickerController = Cast<ATickerController>(Blackboard->GetOwner());
	//}
	//Grabbing blackboard from current bandit

	if (!Blackboard)
	{
		Blackboard = OwnerComp.GetBlackboardComponent();
	}
	else
	{
		if (BanditController)
		{
			if (!Player)
			{
				Player = Cast<AMaxCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			}


			if (Player && BanditController)
			{
				Distance = FVector::Dist(Player->GetActorLocation(), BanditController->GetPawn()->GetActorLocation());
				Blackboard->SetValueAsFloat(TEXT("DistanceToPlayer"), Distance);
			}
		}
		else
		{
			BanditController = Cast<ABanditController>(Blackboard->GetOwner());
		}

		if (TickerController)
		{
			if (!Player)
			{
				Player = Cast<AMaxCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			}

			if (Player && TickerController)
			{
				Distance = FVector::Dist(Player->GetActorLocation(), TickerController->GetPawn()->GetActorLocation());
				Blackboard->SetValueAsFloat(TEXT("DistanceToPlayer"), Distance);
			}
		}
		else
		{
			TickerController = Cast<ATickerController>(Blackboard->GetOwner());
		}
	}



}
