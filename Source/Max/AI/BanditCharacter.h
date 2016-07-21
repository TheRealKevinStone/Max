// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BanditController.h"
#include "AI/TestTargetPoint.h"
#include "AI_Weapons/BaseProjectile.h"
#include "BanditCharacter.generated.h"

UCLASS()
class MAX_API ABanditCharacter : public ACharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	ABanditCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//// Called every frame
	//virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable,Category="BaseBandit")
	void FireProjectile();

	//Taking Damage from player
	//UFUNCTION()
	//virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable, Category = "Bandit")
	void ResetShot() { Shot = false; }

	UFUNCTION(BlueprintCallable, Category = "Bandit")
	void StopBehaviorTree();

	UFUNCTION(BlueprintCallable, Category = "Bandit")
	void StartBehaviorTree();

	UFUNCTION(BlueprintCallable, Category = "Bandit")
	void FrozenFeetHit();

	virtual void RockPunchLaunch();

	//UFUNCTION(BlueprintCallable, Category = "EnemyManager")
	//void OnEnemyDead();

public:
	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* ProjectilePoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseProjectile> ProjectileClass;
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TArray<ATestTargetPoint*> WaypointList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BanditHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;

	ABanditController* BanditController;

	//UPROPERTY(BlueprintReadWrite)
	bool Shot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RockPunch_KB;

	uint32 ArrayReserveNumber=10;
};
