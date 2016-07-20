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
	//WaypointList.Reserve(ArrayReserveNumber);
}

// Called when the game starts or when spawned
void ABanditCharacter::BeginPlay()
{
	Super::BeginPlay();
	BanditController = Cast<ABanditController>(GetController());
	BanditHealth = MaxHealth;
	//To look for waypoints in the world.
	//for (ATestTargetPoint* Waypoint : WaypointList)
	//{
	//	if (Waypoint)
	//	{
	//		if (BanditController)
	//		{
	//			BanditController->SetWaypoint(Waypoint);
	//		}
	//	}

	//}
}

// Called every frame
//void ABanditCharacter::Tick( float DeltaTime )
//{
//	Super::Tick( DeltaTime );
//
//}

void ABanditCharacter::FireProjectile()
{
	if (ProjectileClass != NULL)
	{
		if (!Shot)
		{
			GetWorld()->SpawnActor<ABaseProjectile>(ProjectileClass, ProjectilePoint->GetComponentLocation(), ProjectilePoint->GetComponentRotation());
			Shot = true;
		}
	}
}

//float ABanditCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
//{
//	Health -= DamageAmount;
//	if (Health <= 0.f)
//	{
//		//Do Death Animation
//		//Play Death Audio
//		
//		this->SetActorEnableCollision(false);
//
//	}
//	else
//	{
//		//Do Damage Animation
//		//Play Damage Audio
//		//Apply Knockback
//		
//	}
//
//
//	return Health;
//}

void ABanditCharacter::StopBehaviorTree()
{
	if (BanditController)
	{
		BanditController->GetBehaviorComp()->StopTree();

	}
}

void ABanditCharacter::StartBehaviorTree()
{
	if (BanditController)
	{
		BanditController->GetBehaviorComp()->StartTree(*BehaviorTree);

	}
}

void ABanditCharacter::FrozenFeetHit()
{
	if (BanditController)
	{
		BanditController->BanditFrozen();
	}
}

//void ABanditCharacter::OnEnemyDead()
//{
//
//}

