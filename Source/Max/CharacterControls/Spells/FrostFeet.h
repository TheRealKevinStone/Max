// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FrostFeet.generated.h"

UCLASS()
class MAX_API AFrostFeet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFrostFeet();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//// Called every frame
	//virtual void Tick( float DeltaSeconds ) override;

	/** Returns CollisionComp subobject **/
	FORCEINLINE class USphereComponent* GetCollisionComp() const { return Collider; }
	
public:
	UFUNCTION(BlueprintNativeEvent, Category = Projectile)
	void OnHit(AActor* OtherActor);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* Collider;

	

};
