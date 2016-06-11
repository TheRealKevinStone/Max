// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Stamina.generated.h"

UCLASS()
class MAX_API AStamina : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStamina();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//value for the pickup. default for now at 100
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 StaminaVal = 100;

	//axis rotations (for effect)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float XAxisRotate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float YAxisRotate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ZAxisRotate;
	

protected:

	//money pickup sfx
	UPROPERTY(EditAnywhere, Category = Sound)
		USoundCue* StaminaSFX;

	//collider for currency pick up
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* StaminaCollider;

	//mesh for currency pick up
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaminaMesh;

protected:

	//when an actor overlaps with this one (will be player)
	//UFUNCTION()
	//virtual void OnOverLap(class AActor* OtherActor);
	
	//UFUNCTION(BlueprintImplementableEvent, Category = Drop, meta = (DisplayName = "Apply to Player")) 
	//void Event_ApplyToPlayer(AMax* Max);

};
