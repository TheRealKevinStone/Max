// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BanditController.generated.h"

/**
 * 
 */
UCLASS()
class MAX_API ABanditController : public AAIController
{
	GENERATED_BODY()
	
public:
	ABanditController();
	virtual void Possess(APawn* Pawn)override;

protected:
	UPROPERTY(VisibleAnywhere)
	UBehaviorTreeComponent* BehaviorTreeComp;

	UPROPERTY(VisibleAnywhere)
	UBlackboardComponent* BlackboardComp;
	
};
