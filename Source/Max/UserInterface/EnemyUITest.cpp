// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "EnemyUITest.h"


// Sets default values
AEnemyUITest::AEnemyUITest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Enemy Collider"));
	RootComponent = EnemyCollider;

	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy Mesh"));
	EnemyMesh->AttachTo(RootComponent);

}

// Called when the game starts or when spawned
void AEnemyUITest::BeginPlay()
{
	Super::BeginPlay();

	AMaxCharacter* MaxCharacter = Cast<AMaxCharacter>(*TActorIterator<AMaxCharacter>(GetWorld()));
	
}

// Called every frame
void AEnemyUITest::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AEnemyUITest::OnOverlap(class AActor* OtherActor)
{
	//UI stuff here I guess
	//first will debug message to make sure working
	//then start adding a UI image of w.e pop u[
	// from there align position of UI (above object)
	//then change image to numbers
	AMaxCharacter* MaxCharacter = Cast<AMaxCharacter>(OtherActor);

	GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Red, FString::Printf(TEXT("damage counter shows")));

	if (MaxCharacter)
	{
		GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Red, FString::Printf(TEXT("damage counter shows")));
		Event_ApplyToEnemy(MaxCharacter);

		//Destroy();
	}
}