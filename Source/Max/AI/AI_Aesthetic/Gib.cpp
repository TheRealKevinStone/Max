// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "Gib.h"


// Sets default values
AGib::AGib()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	//Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	////Collider->BodyInstance.SetCollisionProfileName("Projectile");
	////OnActorBeginOverlap.AddDynamic(this, &ABaseProjectile::OnActorOverlap);
	////Collider->OnComponentBeginOverlap.AddDynamic(this, &AGib::OnExplosion);
	//Collider->AttachTo(RootComponent);

	GibMesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gib1"));
	GibMesh1->AttachTo(RootComponent);

	GibMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gib2"));
	GibMesh2->AttachTo(RootComponent);
	
	GibMesh3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gib3"));
	GibMesh3->AttachTo(RootComponent);
	
	GibMesh4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gib4"));
	GibMesh4->AttachTo(RootComponent);
	
	GibMesh5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gib5"));
	GibMesh5->AttachTo(RootComponent);
	
	GibMesh6 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gib6"));
	GibMesh6->AttachTo(RootComponent);
	
	Particles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particles"));
	Particles->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AGib::BeginPlay()
{
	Super::BeginPlay();
	FVector Origin = this->GetActorLocation();
	//SetActorLocation(FVector(Origin.X, Origin.Y, FloorOffset));
	//IsAttacked = false;

	//Applying Impulse force and setting physics on
	GibMesh1->SetSimulatePhysics(true);
	GibMesh1->AddRadialImpulse(Origin, ForceRadius, ImpulseForce, ERadialImpulseFalloff::RIF_Linear, true);

	GibMesh2->SetSimulatePhysics(true);
	GibMesh2->AddRadialImpulse(Origin, ForceRadius, ImpulseForce, ERadialImpulseFalloff::RIF_Linear, true);

	GibMesh3->SetSimulatePhysics(true);
	GibMesh3->AddRadialImpulse(Origin, ForceRadius, ImpulseForce, ERadialImpulseFalloff::RIF_Linear, true);
	
	GibMesh4->SetSimulatePhysics(true);
	GibMesh4->AddRadialImpulse(Origin, ForceRadius, ImpulseForce, ERadialImpulseFalloff::RIF_Linear, true);
	
	GibMesh5->SetSimulatePhysics(true);
	GibMesh5->AddRadialImpulse(Origin, ForceRadius, ImpulseForce, ERadialImpulseFalloff::RIF_Linear, true);
	
	GibMesh6->SetSimulatePhysics(true);
	GibMesh6->AddRadialImpulse(Origin, ForceRadius, ImpulseForce, ERadialImpulseFalloff::RIF_Linear, true);
	

	if (GibSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, GibSound, GetActorLocation(), 1, 1);
	}
	//if (Particles != NULL)
	//{
	//}
}

//void AGib::Tick(float DeltaSeconds)
//{
//	Super::Tick(DeltaSeconds);
//
//	//more experimenting with collision with explosion
//	//if (!TimesUp)
//	//{
//	//	if (CurrentTimer <= ExplosionDuration)
//	//	{
//	//		TArray<AActor*> OverlappingActors;
//	//		Collider->GetOverlappingActors(OverlappingActors);
//	//		for (AActor* CollidedActor : OverlappingActors)
//	//		{
//	//			AMaxCharacter* Player = Cast<AMaxCharacter>(CollidedActor);
//	//			if (Player)
//	//			{
//	//				if (!IsAttacked)
//	//				{
//	//					//Apply Damage
//	//					//UGameplayStatics::ApplyDamage(Player,Damage, this->GetInstigatorController(), this, UDamageType::StaticClass());
//	//					IsAttacked = true;
//	//					
//	//					//Deactivate Impact particle effect and explosion
//	//					
//	//				}
//	//			}
//	//		}
//	//		
//	//	}
//	//	else
//	//	{
//	//		TimesUp = true;
//	//	}
//	//	CurrentTimer += DeltaSeconds;
//	//}
//
//}

//Attempt to do On Trigger Enter into a function
//void AGib::OnExplosion(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	if (OtherActor != GetOwner())
//	{
//		AMaxCharacter* Player = Cast<AMaxCharacter>(OtherActor);
//		if (Player)
//		{
//			if (!IsAttacked)
//			{
//				//Apply Damage
//				UGameplayStatics::ApplyDamage(Player, Damage, this->GetInstigatorController(), this, UDamageType::StaticClass());
//				IsAttacked = true;
//				Collider->BodyInstance.SetCollisionProfileName("IgnoreCollision");
//			}
//		}
//	}
//}

