// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CharacterControls/MaxCharacter.h"
#include "BaseTicker.h"
#include "TickerController.generated.h"

/**
 * 
 */
UCLASS()
class MAX_API ATickerController : public AAIController
{
	GENERATED_BODY()
	
public:
	ATickerController(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Possess(APawn* Pawn)override;

	virtual void UpdateControlRotation(float DeltaTime, bool bUpdatePawn = true) override;
protected:
	UPROPERTY(VisibleAnywhere)
	UBehaviorTreeComponent* BehaviorTreeTicker;

	UPROPERTY(VisibleAnywhere)
	UBlackboardComponent* BlackboardTicker;
	
	AMaxCharacter* Player;

public:
	/*    Returns BlackboardComp Subobject   */
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardTicker; }
	/** Returns BehaviorComp subobject **/
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp() const { return BehaviorTreeTicker; }
};
