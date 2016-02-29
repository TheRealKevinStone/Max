// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Currency.generated.h"

UCLASS()
class MAX_API ACurrency : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACurrency();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//value for the pickup. default for now at 100
	uint8 CurrencyVal = 100;

	//axis rotations (for effect)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		uint8 XAxisRotate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		uint8 YAxisRotate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		uint8 ZAxisRotate;
	

protected:

	//collider for currency pick up
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* CurrencyCollider;

	//mesh for currency pick up
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* CurrencyMesh;

protected:

	//when an actor overlaps with this one (will be player)
	//UFUNCTION()
	//virtual void OnOverLap(class AActor* OtherActor);
	
	//UFUNCTION(BlueprintImplementableEvent, Category = Drop, meta = (DisplayName = "Apply to Player")) 
	//void Event_ApplyToPlayer(AMax* Max);

};
