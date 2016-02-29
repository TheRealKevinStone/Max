// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "BaseProjectile.h"


// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ColliderSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ColliderSphere"));
	RootComponent = ColliderSphere;
	ColliderSphere->OnComponentHit.AddDynamic(this, &ABaseProjectile::Collision);
	Damage = 1;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(RootComponent);


}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ABaseProjectile::Collision(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector
	NormalImpulse, const FHitResult& Hit)
{
	Destroy();
}

