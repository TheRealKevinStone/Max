// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

UCLASS()
class MAX_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();


	UPROPERTY(EditDefaultsOnly)
	UProjectileMovementComponent* ProjectileComp;

	UFUNCTION()
	virtual void OnActorOverlap(AActor* OtherActor);


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	float Damage;

	FVector forward;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile)
	USphereComponent* ColliderSphere;

	AActor* EnemyThatShot;

private:
	float Speed;



	

	
	
};
