// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "TestTargetPoint.h"
#include "Perception/PawnSensingComponent.h"
#include "BanditController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;

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

	/** Update direction AI is looking based on FocalPoint */
	virtual void UpdateControlRotation(float DeltaTime, bool bUpdatePawn = true) override;

	//Getter for current target location for function UpdateControlRotation
	FVector GetCurrentTarget();

	//Setting waypoint to Array
	void SetWaypoint(ATestTargetPoint* Waypoint);

	//Getting waypoint from Array
	ATestTargetPoint* CurrentWaypoint();
	
	virtual void BanditFrozen();

	//for timer function
	void ResetSight();

protected:
	UPROPERTY(VisibleAnywhere)
	UBehaviorTreeComponent* BehaviorTreeComp;

	UPROPERTY(VisibleAnywhere)
	UBlackboardComponent* BlackboardComp;

	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensing;

	UPROPERTY(VisibleAnywhere)
	UAIPerceptionComponent* AIPerception;

	UFUNCTION()
	void OnSeenPlayer(APawn* Player);
	
	TArray<ATestTargetPoint*> WaypointArray;

	uint16 WaypointIndex;

	uint32 ArrayMax=10;

	//Timer to handle to keep track of our timer
	FTimerHandle TimerHandle;

	//if player is found
	bool PlayerSpotted;

	//determine if player is still near
	bool PlayerSightedNear;

	bool TurnOffRotation;

	//Players last location seen
	FVector LastKnownLocation;

	FName PlayerSpottedKeyName = TEXT("PlayerSpotted");

	FName PlayerSightedNearKeyName = TEXT("PlayerNearby");

	FName LastKnownLocationKeyName = TEXT("PlayersLastknownLocation");

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SightRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName PlayerKeyName;

	
private:
	FVector CurrentTarget;
	bool isItPlayer;

public:
	/*    Returns BlackboardComp Subobject   */
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	/** Returns BehaviorComp subobject **/
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp() const { return BehaviorTreeComp; }
};
