// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "FireDart.h"
#include "AI/BanditCharacter.h"
#include "AI/DamageTypes/Burning_DT.h"
#include "AI/AI_Weapons/BaseTicker.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AFireDart::AFireDart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	//CollisionComp->OnComponentHit.AddDynamic(this, &AFireDart::OnHit);		// set up a notification for when this component hits something blocking
	OnActorBeginOverlap.AddDynamic(this, &AFireDart::OnHit);
	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
	SetActorEnableCollision(true);
}

// Called when the game starts or when spawned
void AFireDart::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFireDart::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AFireDart::OnHit_Implementation(AActor * OtherActor) 
{
	if (OtherActor != GetOwner())
	{
		ABanditCharacter* Bandit = Cast<ABanditCharacter>(OtherActor);
		ABaseTicker* Ticker = Cast<ABaseTicker>(OtherActor);
		if (Bandit)
		{
			if (Explosion)
			{
				UWorld* const World = GetWorld();
				const FVector SpawnLocation = GetActorLocation();
				const FRotator SpawnRotation = GetActorRotation();
				World->SpawnActor<AActor>(Explosion, SpawnLocation,SpawnRotation);
				UGameplayStatics::ApplyDamage(Bandit, Damage, this->GetInstigatorController(), this, UDamageType::StaticClass());
				this->Destroy();
			}
			
		}
		else if (Ticker)
		{
			if (Explosion)
			{
				UWorld* const World = GetWorld();
				const FVector SpawnLocation = GetActorLocation();
				const FRotator SpawnRotation = GetActorRotation();
				World->SpawnActor<AActor>(Explosion, SpawnLocation, SpawnRotation);
				UGameplayStatics::ApplyDamage(Ticker, Damage, this->GetInstigatorController(), this, UDamageType::StaticClass());
				this->Destroy();
			}

		}
	}
	
}



