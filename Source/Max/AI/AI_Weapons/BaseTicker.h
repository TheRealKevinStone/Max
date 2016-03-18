// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "CharacterControls/MaxCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BaseTicker.generated.h"

UCLASS()
class MAX_API ABaseTicker : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseTicker();

	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;

public:
	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* BehaviorTreeBaseTick;

protected:
	
	AMaxCharacter* Player;


};
