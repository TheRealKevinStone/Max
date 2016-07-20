// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RockPunch.generated.h"

UCLASS()
class MAX_API ARockPunch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARockPunch();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

//public:
//	UFUNCTION(BlueprintNativeEvent, Category = Melee)
//		void OnHit(AActor* OtherActor);
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* Collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* RootPunch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PunchDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float KnockbackForce;

	bool TimesUp;

	bool isAttacked;

	float CurrentTimer;
	
};
