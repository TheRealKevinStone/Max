// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
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
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable,Category="BaseBandit")
	void FireProjectile();

public:
	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* ProjectilePoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseProjectile> ProjectileClass;
	
};
