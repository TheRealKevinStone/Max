// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "CharacterControls/MaxCharacter.h"
#include "TickerController.h"
#include "AI/AI_Aesthetic/Gib.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BaseTicker.generated.h"


UCLASS()
class MAX_API ABaseTicker : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseTicker();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//// Called every frame
	//virtual void Tick( float DeltaSeconds ) override;
	//Check for collisions
	UFUNCTION()
		virtual void OnOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);	//Taking Damage from player
	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	//Explosion function to spawn gibs
	UFUNCTION(BlueprintCallable,Category= "Ticker")
	void ExplosionGib();

	virtual void FrozenSpellHit();
	
public:
	//Property for behavior tree
	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* BehaviorTreeBaseTick;
	//selection of gibs
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Ticker")
	TSubclassOf<AGib> Explosion;

	//Explosion Detect Radius
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ticker")
	float ExplodeDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ticker")
	float KnockbackMin;
	//ATickerController* TickerController;

protected:
	//Cache for player
	AMaxCharacter* Player;

	//ATickerController* TickerController;
	//check if you exploded
	bool Exploded;
	//Check if player is near
	bool PlayerNear;
};
