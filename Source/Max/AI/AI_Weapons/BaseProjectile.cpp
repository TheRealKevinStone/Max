// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "BaseProjectile.h"


// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ColliderSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ColliderSphere"));
	ColliderSphere->BodyInstance.SetCollisionProfileName("Projectile");
	ColliderSphere->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	ColliderSphere->CanCharacterStepUpOn = ECB_No;

	RootComponent = ColliderSphere;
	Damage = 1;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(RootComponent);

	ProjectileComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileComp->UpdatedComponent = ColliderSphere;
	ProjectileComp->InitialSpeed = 1200.f;
	ProjectileComp->MaxSpeed = 1200.f;
	ProjectileComp->bRotationFollowsVelocity = true;
	ProjectileComp->bShouldBounce = false;

	OnActorBeginOverlap.AddDynamic(this, &ABaseProjectile::OnActorOverlap);

	InitialLifeSpan = 10.f;

}

void ABaseProjectile::OnActorOverlap(AActor * OtherActor)
{
	if (OtherActor != GetOwner())
	{
		//Appply Damage
		//Cast to player
		//Add knockback
		//Add sounds
		this->Destroy();
		GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Black, FString(TEXT("Collision")));
	}
}

