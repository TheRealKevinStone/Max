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

void ABaseTicker::ExplosionGib()
{
	if (Explosion)
	{
		if (!Exploded)
		{
			FVector TickerLocation = GetActorLocation();
			AGib* Corpse= GetWorld()->SpawnActor<AGib>(Explosion, TickerLocation, FRotator::ZeroRotator);
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
