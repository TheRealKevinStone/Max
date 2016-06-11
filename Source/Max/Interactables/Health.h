// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Max/CharacterControls/MaxCharacter.h"
#include "Health.generated.h"

UCLASS()
class MAX_API AHealth : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealth();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	////to use max as reference when needed
	//AMaxCharacter* Max = Cast<AMaxCharacter>(*TActorIterator<AMaxCharacter>(GetWorld()));

	//how much health you'll get
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HealthValue = 15.f;

	//axis rotations (for effect)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float XAxisRotate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float YAxisRotate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ZAxisRotate;

protected:

	//used to play the pickup sound when collected
	UPROPERTY(EditAnywhere, Category = Sound)
		USoundCue* HealthSFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* HealthCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* HealthMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AHealth> HealthDrop;

protected:

	//when an actor overlaps with this one (will be player)
	UFUNCTION()
	virtual void OnOverLap(class AActor* OtherActor);

	UFUNCTION(BlueprintImplementableEvent, Category = Drop, meta = (DisplayName = "Apply to Player")) 
	void Event_ApplyToPlayer(AMaxCharacter* Max);

	
};
