// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "AI/BanditCharacter.h"
#include "AI/BanditClasses/TickerBandit.h"
#include "AI/AI_Weapons/BaseTicker.h"
#include "RockPunch.h"


// Sets default values
ARockPunch::ARockPunch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootPunch = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = RootPunch;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->BodyInstance.SetCollisionProfileName("Projectile");
	Collider->SetupAttachment(RootComponent);
	SetActorEnableCollision(true);
}

// Called when the game starts or when spawned
void ARockPunch::BeginPlay()
{
	Super::BeginPlay();
	
	//SetActorRotation(FRotator::ZeroRotator);
}

// Called every frame
void ARockPunch::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
	if (!TimesUp)
	{
		CurrentTimer += DeltaTime;
		if (CurrentTimer <= PunchDuration)
		{
			TArray<AActor*>OverlappingActors;
			Collider->GetOverlappingActors(OverlappingActors);
			for (AActor* CollidedActor : OverlappingActors)
			{
				ABanditCharacter* Bandit = Cast<ABanditCharacter>(CollidedActor);
				ABaseTicker* Ticker = Cast<ABaseTicker>(CollidedActor);
				if (Bandit)
				{
					if (!isAttacked)
					{
						UGameplayStatics::ApplyDamage(Bandit, Damage, this->GetInstigatorController(), this, UDamageType::StaticClass());
						isAttacked = true;
					}
				}
				else if (Ticker)
				{
					UGameplayStatics::ApplyDamage(Ticker, Damage, this->GetInstigatorController(), this, UDamageType::StaticClass());
					isAttacked = true;
				}
			}
		}
	}
	else
	{
		TimesUp = true;
	}
}



