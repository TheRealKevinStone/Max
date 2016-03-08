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
			GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Black, TEXT("Found Player!"));
			BlackboardComp->SetValueAsObject(PlayerKeyName, Player);
		}
	}

}
