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

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintNativeEvent,Category=Projectile)
	void Collision(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector
			NormalImpulse, const FHitResult& Hit);

	void SetEnemyThatShot(AActor* EnemyThatShot);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
		float Damage;

	FVector forward;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile)
	USphereComponent* ColliderSphere;

	AActor* EnemyThatShot;



	

	
	
};
