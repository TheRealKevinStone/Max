// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "Mana.h"


// Sets default values
AMana::AMana()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ManaCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Mana Collider"));
	RootComponent = ManaCollider;

	ManaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mana Mesh"));
	ManaMesh->SetupAttachment(RootComponent);

	//OnActorBeginOverlap.AddDynamic(this, &::OnOverlap);

}

// Called when the game starts or when spawned
void AMana::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMana::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

//void AMana::OnOverLap(class AActor* OtherActor)
//{
	//if (ManaSFX)
	//{
		//UGameplayStatics::PlaySoundAtLocation(this, ManaSFX, GetActorLocation(), 1, 1);
	//}
//}

