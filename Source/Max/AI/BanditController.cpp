// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "BanditCharacter.h"
#include "CharacterControls/MaxCharacter.h"
#include "Navigation/JumpPathComponent.h"
#include "BanditController.h"

ABanditController::ABanditController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<UJumpPathComponent>(TEXT("PathFollowingComponent")))
{
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSenseingComp"));
	WaypointArray.Reserve(ArrayMax);

}


void ABanditController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	ABanditCharacter* Bandit = Cast<ABanditCharacter>(Pawn);

	if (Bandit&&Bandit->BehaviorTree)
	{
		BlackboardComp->InitializeBlackboard(*Bandit->BehaviorTree->BlackboardAsset);
		BehaviorTreeComp->StartTree(*Bandit->BehaviorTree);
	}

	if (PawnSensing)
	{
		PawnSensing->OnSeePawn.AddDynamic(this, &ABanditController::OnSeenPlayer);
	}
}

void ABanditController::OnSeenPlayer(APawn* Player)
{
	float Distance = FVector::Dist(Player->GetActorLocation(), this->GetCharacter()->GetActorLocation());
	if (Distance < SightRange)
	{
		AMaxCharacter* Max = Cast<AMaxCharacter>(Player->GetController()->GetCharacter());

		if (Max)
		{
			//GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Black, TEXT("Found Player!"));
			BlackboardComp->SetValueAsObject(PlayerKeyName, Player);
			BlackboardComp->SetValueAsObject(TEXT("CurrentTarget"), Player);
		}
	}

}

void ABanditController::UpdateControlRotation(float DeltaTime, bool bUpdatePawn)
{
	//Look towards focus
	FVector FocalPoint = GetCurrentTarget();

	if (!FocalPoint.IsZero() && GetPawn())
	{
		FVector Direction = FocalPoint - GetPawn()->GetActorLocation();
		FRotator NewControlRotation = Direction.Rotation();

		NewControlRotation.Yaw = FRotator::ClampAxis(NewControlRotation.Yaw);
		SetControlRotation(NewControlRotation);
		
		APawn* const Pawn = GetPawn();
		if (Pawn&&bUpdatePawn)
		{
			Pawn->FaceRotation(NewControlRotation, DeltaTime);
		}
	}

}

FVector ABanditController::GetCurrentTarget()
{
	CurrentTarget = BlackboardComp->GetValueAsObject(TEXT("CurrentTarget"));
	if (CurrentTarget)
	{
		AActor* Target = Cast<AActor>(CurrentTarget);
		return Target->GetActorLocation();
	}
	return FVector::ZeroVector;
}

void ABanditController::SetWaypoint(ATestTargetPoint* Waypoint)
{
	WaypointArray.Add(Waypoint);
}



ATestTargetPoint* ABanditController::CurrentWaypoint()
{
	if (WaypointIndex <= WaypointArray.Num()-1)
	{
		ATestTargetPoint* CurrWaypoint = WaypointArray[WaypointIndex];
		WaypointIndex++;
		return CurrWaypoint;
	}
	else
	{
		if (WaypointArray.Num() >= 2)
		{
			WaypointIndex = 0;
			ATestTargetPoint* CurrWaypoint = WaypointArray[WaypointIndex];
			WaypointIndex++;
			return CurrWaypoint;
		}
		else
		{
			return NULL;
		}

	}
	
}

