// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "EnemyUITest.h"


// Sets default values
AEnemyUITest::AEnemyUITest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Enemy Collider"));
	RootComponent = EnemyCollider;

	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy Mesh"));
	EnemyMesh->AttachTo(RootComponent);

}

// Called when the game starts or when spawned
void AEnemyUITest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyUITest::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}