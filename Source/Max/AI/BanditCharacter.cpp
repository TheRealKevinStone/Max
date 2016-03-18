// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "BanditCharacter.h"


// Sets default values
ABanditCharacter::ABanditCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = ABanditController::StaticClass();
	ProjectilePoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectilePoint->AttachTo(RootComponent);
	WaypointList.Reserve(ArrayReserveNumber);
}

// Called when the game starts or when spawned
void ABanditCharacter::BeginPlay()
{
	Super::BeginPlay();
	BanditController = Cast<ABanditController>(GetController());
	
	for (ATestTargetPoint* Waypoint : WaypointList)
	{
		if (Waypoint)
		{
			if (BanditController)
			{
				BanditController->SetWaypoint(Waypoint);
			}
		}

	}
}

// Called every frame
void ABanditCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ABanditCharacter::FireProjectile()
{


	if (ProjectileClass != NULL)
	{
		GetWorld()->SpawnActor<ABaseProjectile>(ProjectileClass, ProjectilePoint->GetComponentLocation(), ProjectilePoint->GetComponentRotation());

	}
}

