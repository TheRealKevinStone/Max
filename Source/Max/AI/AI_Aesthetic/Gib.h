// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CharacterControls/MaxCharacter.h"
#include "Gib.generated.h"

UCLASS()
class MAX_API AGib : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGib();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float FloorOffset = 44.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* Collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* GibMesh1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* GibMesh2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* GibMesh3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* GibMesh4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* GibMesh5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* GibMesh6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystemComponent* Particles;

	UPROPERTY(EditAnywhere, Category = Sound)
	USoundCue* GibSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ForceRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ImpulseForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExplosionDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

	bool TimesUp;

	bool IsAttacked;

	float CurrentTimer;
	
};
