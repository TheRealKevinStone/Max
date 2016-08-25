// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "BanditCharacter.h"
#include "CharacterControls/MaxCharacter.h"
//#include "Navigation/JumpPathComponent.h"
#include "BanditController.h"

ABanditController::ABanditController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	CrowdComp = Cast<UCrowdFollowingComponent>(Cast<ABanditController>(this)->GetPathFollowingComponent());
	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSenseingComp"));
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
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
	PlayerSpotted = true;
	PlayerSightedNear = true;
	LastKnownLocation = Player->GetActorLocation();

	BlackboardComp->SetValueAsBool(PlayerSpottedKeyName, PlayerSpotted);
	BlackboardComp->SetValueAsBool(PlayerSightedNearKeyName, PlayerSightedNear);
	BlackboardComp->SetValueAsVector(LastKnownLocationKeyName, LastKnownLocation);
	



	//*******Attempt to code the last known position method but moved it to BP*************
	//FActorPerceptionBlueprintInfo Info;
	//AMaxCharacter* Max = Cast<AMaxCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	//GetAIPerceptionComponent()->GetActorsPerception(Max, Info);
	//if (Info.LastSensedStimuli.Num() > 0)
	//{
	//	const FAIStimulus Stimulus = Info.LastSensedStimuli[0];
	//	if (Stimulus.WasSuccessfullySensed())
	//	{
	//		//Player in sight
	//		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Blue, TEXT("Player In Sight"));
	//	}
	//	else
	//	{
	//		//Player not in sight
	//		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Blue, TEXT("Player Not in Sight"));
	//	}
	//}


	//******Sight with distance determination**********
	//float Distance = FVector::Dist(Player->GetActorLocation(), this->GetCharacter()->GetActorLocation());
	//if (Distance < SightRange)
	//{
	//	AMaxCharacter* Max = Cast<AMaxCharacter>(Player->GetController()->GetCharacter());
	//	if (Max)
	//	{
	//		//GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Black, TEXT("Found Player!"));
	//		BlackboardComp->SetValueAsObject(PlayerKeyName, Player);
	//		BlackboardComp->SetValueAsObject(TEXT("CurrentTarget"), Player);
	//	}
	//}

}

void ABanditController::UpdateControlRotation(float DeltaTime, bool bUpdatePawn)
{
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

	//Start the timer
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABanditController::ResetSight, 0.1f, true, 0.0f);
	

}

FVector ABanditController::GetCurrentTarget()
{
	CurrentTarget = BlackboardComp->GetValueAsVector(TEXT("CurrentTarget"));
	isItPlayer = BlackboardComp->GetValueAsBool(TEXT("PlayerSpotted"));
	if (isItPlayer)
	{
		AActor* Player =Cast<AActor>(BlackboardComp->GetValueAsObject(TEXT("Player")));
		CurrentTarget = Player->GetActorLocation();
	}
	return CurrentTarget;
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

void ABanditController::BanditFrozen()
{
	BlackboardComp->SetValueAsBool(TEXT("isFrozen"), true);
}

void ABanditController::ResetSight()
{
	TurnOffRotation = true;
	PlayerSpotted = false;
	BlackboardComp->SetValueAsBool(PlayerSpottedKeyName, PlayerSpotted);
}

