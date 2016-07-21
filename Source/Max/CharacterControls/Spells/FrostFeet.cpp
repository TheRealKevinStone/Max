// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "AI/BanditCharacter.h"
#include "AI/AI_Weapons/BaseTicker.h"
#include "CharacterControls/MaxCharacter.h"
#include "FrostFeet.h"


// Sets default values
AFrostFeet::AFrostFeet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	Collider->BodyInstance.SetCollisionProfileName("Projectile");
	RootComponent = Collider;
	OnActorBeginOverlap.AddDynamic(this, &AFrostFeet::OnHit);

	SetActorEnableCollision(true);
}

// Called when the game starts or when spawned
void AFrostFeet::BeginPlay()
{
	Super::BeginPlay();
	AMaxCharacter* Player = Cast<AMaxCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player)
	{
		FVector SpawnPoint = Player->GetActorLocation();
		SetActorRotation(FRotator::ZeroRotator);
		this->SetActorLocation(SpawnPoint);
	}

}
//
//// Called every frame
//void AFrostFeet::Tick( float DeltaTime )
//{
//	Super::Tick( DeltaTime );
//
//}

void AFrostFeet::OnHit_Implementation(AActor * OtherActor)
{
	if (OtherActor != GetOwner())
	{
		ABanditCharacter* Bandit = Cast<ABanditCharacter>(OtherActor);
		ABaseTicker* Ticker = Cast<ABaseTicker>(OtherActor);
		if (Bandit)
		{
			Bandit->FrozenFeetHit();
		}
		else if (Ticker)
		{
			Ticker->FrozenSpellHit();
		}
	}
}

