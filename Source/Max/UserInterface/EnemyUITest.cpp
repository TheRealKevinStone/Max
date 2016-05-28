// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "EnemyUITest.h"
#include "Engine/Canvas.h"

// Sets default values
AEnemyUITest::AEnemyUITest(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Enemy Collider"));
	RootComponent = EnemyCollider;

	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy Mesh"));
	EnemyMesh->AttachTo(RootComponent);

	OnActorBeginOverlap.AddDynamic(this, &AEnemyUITest::OnOverlap);
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

//void AEnemyUITest::DrawHUD()
//{
	//Super::DrawHUD();

	//DrawDamageCounter();
//}

//void AEnemyUITest::DrawDamageCounter()
//{
	//float ScaleEnemyUI = Canvas->ClipY / Canvas->ClipX;

	//FCanvasIcon DamageCounterIcon = UCanvas::MakeIcon(StaminaBarTexture, 0, 0, TestStamina, 20);

	//Canvas->DrawIcon(StaminaBarIcon, (Canvas->SizeX) / 7.5, 20, ScaleManaUI);
//}

void AEnemyUITest::OnOverlap(class AActor* OtherActor)
{
	AMaxCharacter* MaxCharacter = Cast<AMaxCharacter>(OtherActor);

	if (MaxCharacter)
	{
		//DrawHUD();
		GEngine->AddOnScreenDebugMessage(2, 2.f, FColor::Red, FString::Printf(TEXT("damage counter shows")));
		Event_ApplyToEnemy(MaxCharacter);
		//Destroy();
	}
}