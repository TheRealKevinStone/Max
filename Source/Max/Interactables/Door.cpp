// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "Door.h"


// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//creating the collider/object for a door
	DoorCollider = CreateAbstractDefaultSubobject<UBoxComponent>(TEXT("DoorCollider"));
	RootComponent = DoorCollider;

	//creating a mesh component for the door (model)
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->AttachTo(RootComponent);

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

