// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "DistanceTo.h"

void UDistanceTo::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (!Blackboard)
	{
		Blackboard = OwnerComp.GetBlackboardComponent();
	}
	else
	{
		if (BanditController)
		{

			Player = Cast<AMaxCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

			if (Player)
			{
				FVector PlayerLocation = Player->GetActorLocation();
				FVector BanditLocation = BanditController->GetPawn()->GetActorLocation();
				Distance = FVector::Dist(PlayerLocation, BanditLocation);
				if (Distance)
				{
					Blackboard->SetValueAsFloat(TEXT("DistanceToPlayer"), Distance);
				}
			}
			else
			{
				return;
			}
		}
		else
		{
			BanditController = Cast<ABanditController>(Blackboard->GetOwner());
		}

		if (TickerController)
		{
			Player = Cast<AMaxCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			
			if (Player)
			{
				FVector PlayerLocation = Player->GetActorLocation();
				FVector TickerLocation = TickerController->GetTickerPosition();
				Distance = FVector::Dist(PlayerLocation, TickerLocation);
				if (Distance)
				{
					Blackboard->SetValueAsFloat(TEXT("DistanceToPlayer"), Distance);

				}
			}
			else
			{
				return;
			}
		}
		else
		{
			TickerController = Cast<ATickerController>(Blackboard->GetOwner());
		}
	}



}
