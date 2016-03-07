// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Mana.generated.h"

UCLASS()
class MAX_API AMana : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMana();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ManaValue = 15.f;

protected:

	//Mana pickup SFX
	UPROPERTY(EditANywhere, Category = Sound)
		USoundCue* ManaSFX;

	//collider for currency pick up
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* ManaCollider;

	//mesh for currency pick up
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* ManaMesh;

protected:
	
	//when an actor overlaps with this one (will be player)
	//UFUNCTION()
	//virtual void OnOverLap(class AActor* OtherActor);

	//UFUNCTION(BlueprintImplementableEvent, Category = Drop, meta = (DisplayName = "Apply to Player")) 
	//void Event_ApplyToPlayer(AMax* Max);
	
};
