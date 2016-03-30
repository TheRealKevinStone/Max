// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "TickerController.h"

ATickerController::ATickerController(const FObjectInitializer& ObjectInitializer)
{
	//PrimaryActorTick.bCanEverTick = true;

	BehaviorTreeTicker= CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeTicker"));
	BlackboardTicker= CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardTicker"));
}

void ATickerController::BeginPlay()
{
	Super::BeginPlay();
	//ATickerController::SetActorTickEnabled(false);
	Player = Cast<AMaxCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player)
	{
		BlackboardTicker->SetValueAsObject(TEXT("Player"), Player);
	}
}

//void ATickerController::Tick(float DeltaSeconds)
//{
//	Super::Tick(DeltaSeconds);
//
//	if (Sleeping)
//	{
//		PlayerLocation = Player->GetActorLocation();
//		TickerLocation = GetPawn()->GetActorLocation();
//		DistanceDifference = FVector::Dist(TickerLocation, PlayerLocation);
//		if (DistanceDifference >= DetectionRadius)
//		{
//			Sleeping = false;
//			//BehaviorTreeTicker->StartTree(*Ticker->BehaviorTreeBaseTick);
//			ATickerController::SetActorTickEnabled(false);
//		}
//	}
//	
//}

void ATickerController::Possess(APawn * Pawn)
{
	Super::Possess(Pawn);

	Ticker = Cast<ABaseTicker>(Pawn);

	if (Ticker&&Ticker->BehaviorTreeBaseTick)
	{
		BlackboardTicker->InitializeBlackboard(*Ticker->BehaviorTreeBaseTick->BlackboardAsset);
		BehaviorTreeTicker->StartTree(*Ticker->BehaviorTreeBaseTick);
	}
}

void ATickerController::UpdateControlRotation(float DeltaTime, bool bUpdatePawn)
{
	if (Player)
	{
		FVector FocalPoint = Player->GetActorLocation();

		if (!FocalPoint.IsZero() && GetPawn())
		{
			//Get direction from ticker to player
			FVector Direction = FocalPoint - GetPawn()->GetActorLocation();

			//Get rotation from Direction
			FRotator NewControlRotation = Direction.Rotation();

			//Clamp the new rotation then set rotation
			NewControlRotation.Yaw = FRotator::ClampAxis(NewControlRotation.Yaw);
			SetControlRotation(NewControlRotation);

			//Checking for pawn and if it should updatePawn before making pawn face target
			APawn* const Pawn = GetPawn();
			if (Pawn&&bUpdatePawn)
			{
				Pawn->FaceRotation(NewControlRotation, DeltaTime);
			}
		}
	}

}

/*
What i was trying for Sleep()
-Attempt to check distance of player to be sure ticker is far enough
- Turn off Behavior Tree
- Turn on Tick Function
- During tick function check distance from tick to player in controller
- If player is near ticker then turn on behavior tree and turn off tick function
*/
void ATickerController::Sleep()
{

	/*BehaviorTreeTicker->StopTree();
	ATickerController::SetActorTickEnabled(true);
	Sleeping = true;*/
}


