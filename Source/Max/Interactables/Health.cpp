// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "Health.h"


// Sets default values
AHealth::AHealth()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Max = Cast<AMaxCharacter>(*TActorIterator<AMaxCharacter>(GetWorld()));

	HealthCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Health Collider"));
	RootComponent = HealthCollider;

	HealthMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Health Mesh"));
	HealthMesh->AttachTo(RootComponent);

	OnActorBeginOverlap.AddDynamic(this, &AHealth::OnOverLap);
}

// Called when the game starts or when spawned
void AHealth::BeginPlay()
{
	Super::BeginPlay();

	//to use max as reference when needed
	AMaxCharacter* Max = Cast<AMaxCharacter>(*TActorIterator<AMaxCharacter>(GetWorld()));

	HealthCollider->SetSimulatePhysics(false);
	
}

// Called every frame
void AHealth::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AHealth::OnOverLap(class AActor* OtherActor)
{
	//AMaxCharacter* Max = Cast<AMaxCharacter>(OtherActor);

	//if (Max)
	//{
	//	float CurrentHealth = Max->Health;
	//	CurrentHealth += HealthValue;
	//	//Max->Health(CurrentHealth);
	//	Event_ApplyToPlayer(Max);
	//}

	
}

