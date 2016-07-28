// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "IceBlock.h"


// Sets default values
AIceBlock::AIceBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->BodyInstance.SetCollisionProfileName(TEXT("BlockAll"));
	Collider->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	SpawnParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SpawnParticle"));
	SpawnParticle->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AIceBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

//// Called every frame
//void AIceBlock::Tick( float DeltaTime )
//{
//	Super::Tick( DeltaTime );
//
//}

