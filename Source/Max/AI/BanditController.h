// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "BanditController.generated.h"

/**
 * 
 */
UCLASS()
class MAX_API ABanditController : public AAIController
{
	GENERATED_BODY()
	
public:
	ABanditController(const FObjectInitializer& ObjectInitializer);
	virtual void Possess(APawn* Pawn)override;

protected:
	UPROPERTY(VisibleAnywhere)
	UBehaviorTreeComponent* BehaviorTreeComp;

	UPROPERTY(VisibleAnywhere)
	UBlackboardComponent* BlackboardComp;

	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensing;

	UFUNCTION()
	void OnSeenPlayer(APawn* Player);
	
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SightRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName PlayerKeyName;
};
