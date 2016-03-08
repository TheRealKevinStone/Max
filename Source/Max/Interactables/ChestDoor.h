// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ChestDoor.generated.h"

UCLASS()
class MAX_API AChestDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChestDoor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:

	UPROPERTY(EditAnywhere, Category = Sound)
		USoundCue* ChestDoorOpenSFX;

	UPROPERTY(EditAnywhere, Category = Sound)
		USoundCue* ChestDoorClosedSFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* ChestDoorCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* ChestDoorMesh;

protected:

	//when an actor overlaps with this one (will be player)
	//UFUNCTION()
	//virtual void OnOverLap(class AActor* OtherActor);

	//UFUNCTION(BlueprintImplementableEvent, Category = Drop, meta = (DisplayName = "Apply to Player")) 
	//void Event_ApplyToPlayer(AMax* Max);
	
};
