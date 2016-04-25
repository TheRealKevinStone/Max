// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "TickerController.h"
#include "BaseTicker.h"


// Sets default values
ABaseTicker::ABaseTicker()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = ATickerController::StaticClass();

	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseTicker::OnOverlap);
}

void ABaseTicker::BeginPlay()
{
	Super::BeginPlay();

	ATickerController* TickController = Cast<ATickerController>(GetController());

	if (TickController)
	{
		AMaxCharacter* Player = Cast<AMaxCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (Player)
		{
			//BlackboardComp->SetValueAsObject(TEXT("CurrentTarget"), Player);
			TickController->GetBlackboardComp()->SetValueAsObject(TEXT("Player"), Player);
		}
	}

}

void ABaseTicker::OnOverlap(AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ABaseTicker* OtherTicker = Cast<ABaseTicker>(OtherActor);
	if (OtherTicker)
	{
		//Launch Ticker to opposite direction.
		FVector curForwardVector = OtherTicker->GetActorLocation() - this->GetActorLocation();
		curForwardVector.ProjectOnTo(FVector(1, 1, 0));
		//curForwardVector.Normalize();
		LaunchCharacter(curForwardVector*KnockbackMin, true, true);

	}
}

void ABaseTicker::ExplosionGib()
{
	if (Explosion)
	{
		Player = Cast<AMaxCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (Player)
		{
			FVector PlayerLocation = Player->GetActorLocation();
			FVector TickerLocation = this->GetActorLocation();
			float Distance = FVector::Dist(TickerLocation, PlayerLocation);
			if (Distance >= ExplodeDistance)
			{
				if (!Exploded)
				{
					FVector TickerLocation = GetActorLocation();
					AGib* Corpse = GetWorld()->SpawnActor<AGib>(Explosion, TickerLocation, FRotator::ZeroRotator);
					Exploded = true;

					if (Corpse)
					{
						ATickerController* TickerController = Cast<ATickerController>(GetController());
						TickerController->BehaviorTreeTicker->StopTree();
						Destroy();

					}
				}
			}
		}
		

		
	}
}

//// Called every frame
//void ABaseTicker::Tick( float DeltaTime )
//{
//	Super::Tick( DeltaTime );
//
//}


//float ABaseTicker::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
//{
//	//Explode
//	return DamageAmount;
//}
