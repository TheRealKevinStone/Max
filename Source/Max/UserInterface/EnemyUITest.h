// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GameFramework/HUD.h"
#include "CharacterControls/MaxCharacter.h"
#include "EnemyUITest.generated.h"

UCLASS()
class MAX_API AEnemyUITest : public AActor
{
	GENERATED_UCLASS_BODY()

public:	
	// Sets default values for this actor's properties
	AEnemyUITest();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//where we call the function that draws the texture
	//virtual void DrawHUD();

	//where we draw the texture
	//void DrawDamageCounter();

protected:

	//collider for enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* EnemyCollider;

	//mesh for enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* EnemyMesh;

protected:

	UFUNCTION()
	virtual void OnOverlap(class AActor* OtherActor);

	UFUNCTION(BlueprintImplementableEvent, Category = Damage, meta = (DisplayName = "Apply to Enemy"))
	 void Event_ApplyToEnemy(AMaxCharacter* MaxCharacter);

};
