// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "BanditCharacter.h"
#include "Navigation/JumpPathComponent.h"
#include "BanditController.h"

ABanditController::ABanditController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<UJumpPathComponent>(TEXT("PathFollowingComponent")))
{
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

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
}

