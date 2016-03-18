// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "BaseTicker.h"


// Sets default values
ABaseTicker::ABaseTicker()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}



// Called every frame
void ABaseTicker::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


float ABaseTicker::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	//Explode
	return DamageAmount;
}
