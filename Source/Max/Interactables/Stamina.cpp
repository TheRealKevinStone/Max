// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "Stamina.h"


// Sets default values
AStamina::AStamina()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaminaCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Stamina Collider"));
	RootComponent = StaminaCollider;

	StaminaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Currency Mesh"));
	StaminaMesh->AttachTo(RootComponent);

	//OnActorBeginOverlap.AddDynamic(this, &::OnOverlap);
}

// Called when the game starts or when spawned
void AStamina::BeginPlay()
{
	Super::BeginPlay();

	//for when we have max
	//Max = Cast<AMax>(*TActorIterator<AMax>(GetWorld()));


	/*
	ITEMS WILL REPEL FROM MAX DISTANCE, SO NOT COLLECTED RIGHT AWAY

		FVector Max Location GetActoLocaton

		if Max
		if repel dist > max dist to max

		set actor location lerp actor location, max location, repel from plaer

	*/
	
}

// Called every frame
void AStamina::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	/*
	WHEN MAX GETS CLOSE ENOUGH, ATTRACT PICKUPS (temp effect if we want it
												 maybe only for currency?)

	
		if max
			fvector max location = get his location
			float distance to him = fvector dist(get his location)

			if dist to max is less than max dist to him
			set pickup location, lerp, get actor location, max location, speed to max(for pickup)

			else if distance to repel > max dist to him
			set actor location lerp, get actorlocation - max location, repel from player
	*/

	StaminaCollider->AddRelativeRotation(FRotator(XAxisRotate, YAxisRotate, ZAxisRotate), true, false);

}

//void AHealth::OnOverLap(class AActor* OtherActor)
//{
	//if (CurrencySFX)
	//{
		//UGameplayStatics::PlaySoundAtLocation(this, CurrencySFX, GetActorLocation(), 1, 1);
	//}
//}
