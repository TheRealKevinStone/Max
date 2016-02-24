// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "BanditController.h"
#include "BanditCharacter.h"


// Sets default values
ABanditCharacter::ABanditCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = ABanditController::StaticClass();
}

// Called when the game starts or when spawned
void ABanditCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABanditCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


