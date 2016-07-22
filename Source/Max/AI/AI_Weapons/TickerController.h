// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "DetourCrowdAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CharacterControls/MaxCharacter.h"
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

	// Called every frame
	//virtual void Tick(float DeltaSeconds) override;

	virtual void Possess(APawn* Pawn)override;

	virtual void UpdateControlRotation(float DeltaTime, bool bUpdatePawn = true) override;

	void Sleep();

	void GotFrozen();

	void RandomMoveTo();

	FVector GetTickerPosition()
	{
		if (GetPawn())
			return GetPawn()->GetActorLocation();
		else
			return FVector::ZeroVector;
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ticker")
	float DetectionRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ticker")
	float RadiusMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ticker")
	float RadiusMax;

	UPROPERTY(transient)
	UBehaviorTreeComponent* BehaviorTreeTicker;

	UPROPERTY(transient)
	UBlackboardComponent* BlackboardTicker;
	
	//

	AMaxCharacter* Player;

	FVector PlayerLocation;

	FVector TickerLocation;

	float DistanceDifference;

	bool Sleeping;

	UCrowdFollowingComponent* CrowdComp;


public:
	/*    Returns BlackboardComp Subobject   */
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardTicker; }
	/** Returns BehaviorComp subobject **/
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp() const { return BehaviorTreeTicker; }
};
