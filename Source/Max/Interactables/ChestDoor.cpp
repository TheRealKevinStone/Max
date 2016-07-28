// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "ChestDoor.h"


// Sets default values
AChestDoor::AChestDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ChestDoorCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Chest Door Collider"));
	RootComponent = ChestDoorCollider;

	ChestDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Chest Door Mesh"));
	ChestDoorMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AChestDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChestDoor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

