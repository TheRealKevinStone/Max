// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class MAX_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:

	UPROPERTY(EditAnywhere, Category = Sound)
		USoundCue* DoorOpenSFX;

	UPROPERTY(EditAnywhere, Category = Sound)
		USoundCue* DoorClosedSFX;
	
	//collider
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* DoorCollider;

	//mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* DoorMesh;

protected:
	//when an actor overlaps with this one (will be player)
	//UFUNCTION()
	//virtual void OnOverLap(class AActor* OtherActor);

	//UFUNCTION(BlueprintImplementableEvent, Category = Drop, meta = (DisplayName = "Apply to Player")) 
	//void Event_ApplyToPlayer(AMax* Max);
	
};
