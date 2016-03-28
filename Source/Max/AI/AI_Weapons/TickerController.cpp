// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "TickerController.h"

ATickerController::ATickerController(const FObjectInitializer& ObjectInitializer)
{
	BehaviorTreeTicker= CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeTicker"));
	BlackboardTicker= CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardTicker"));
}

void ATickerController::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AMaxCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player)
	{
		BlackboardTicker->SetValueAsObject(TEXT("Player"), Player);
	}
}

void ATickerController::Possess(APawn * Pawn)
{
	Super::Possess(Pawn);

	ABaseTicker* BaseTicker = Cast<ABaseTicker>(Pawn);

	if (BaseTicker&&BaseTicker->BehaviorTreeBaseTick)
	{
		BlackboardTicker->InitializeBlackboard(*BaseTicker->BehaviorTreeBaseTick->BlackboardAsset);
		BehaviorTreeTicker->StartTree(*BaseTicker->BehaviorTreeBaseTick);
	}
}

void ATickerController::UpdateControlRotation(float DeltaTime, bool bUpdatePawn)
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
