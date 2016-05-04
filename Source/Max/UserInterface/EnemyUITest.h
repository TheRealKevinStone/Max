// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include  "CharacterControls/MaxCharacter.h"
#include "EnemyUITest.generated.h"

UCLASS()
class MAX_API AEnemyUITest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyUITest();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:

	//collider for enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* EnemyCollider;

	//mesh for enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* EnemyMesh;

	//UPROPERTY(EditAnywhere, Category = Arts)

protected:

	UFUNCTION()
	virtual void OnEnemyOverlap(class AActor* OtherActor);

	UFUNCTION(BlueprintImplementableEvent, Category = Damage, meta = (DisplayName = "Apply to Enemy"))
	void Event_ApplyToEnemy(AMaxCharacter* MaxCharacter);

};
