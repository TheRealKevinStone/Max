// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
#include "AI/BanditCharacter.h"
#include "AI/AI_Weapons/BaseTicker.h"
#include "MaxCharacter.h"


// Sets default values
AMaxCharacter::AMaxCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = true;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.8f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create SpellOffsetComponent
	SpellOffsetComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SpellOffset"));
	SpellOffsetComponent->AttachTo(RootComponent);

	//Setting Collision on
	SetActorEnableCollision(true);

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

// Called when the game starts or when spawned
void AMaxCharacter::BeginPlay()
{
	Super::BeginPlay();
	MaxStamina = StaminaPoints;
	MoveSpeed = CurWalkSpeed;
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	//FiredartMana = MySpellBook->FireDartMana;
	RockPunchTimer = 0.f;
	BoltTimer = 0.f;
	FireBallTimer = 0.f;
	IceBlockTimer = 0.f;
}

// Called every frame
void AMaxCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	
	bIsGrounded = &UCharacterMovementComponent::IsMovingOnGround;
	if (isDashing && Controller != NULL && bIsGrounded)
	{
		//if player ran out of stamina and isnt exhausted
		if (StaminaPoints == 0 && !isExhausted)
		{
			//Turn off dash function and reduce to walking speed
			isDashing = false;
			isExhausted = true;
			MoveSpeed = CurWalkSpeed;

		}
		//if theres still stamina then decrease stamina points and set to run
		else
		{
			StaminaPoints -= DeltaTime*DecrementRate;
			StaminaPoints = FMath::Clamp<float>(StaminaPoints, 0, MaxStamina);
			MoveSpeed = CurRunSpeed;
		}
	}
	else
	{
		MoveSpeed = CurWalkSpeed;
		//Recover stamina if not running
		if (StaminaPoints < MaxStamina)
		{
			StaminaPoints += DeltaTime*RecoveryRate;
			StaminaPoints = FMath::Clamp<float>(StaminaPoints, 0, MaxStamina);
		}
		//if player has enough stamina to use dash
		if (StaminaPoints >= MaxStamina / 2.f)
		{
			isExhausted = false;
		}
	}
	//Setting movement speed to character movement walk speed.
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;

	if (ManaPoints < MaxMana && !isCasting)
	{
		ManaPoints += DeltaTime*ManaRecoverRate;
	}

	// Check to see if we want to cast spells this frame
	if (bIsCastingFireBall)
	{
		CastFireBall();
	}
	else if (bIsCastingIceBlock)
	{
		CastIceBlock();
	}
	else if (bIsCastingRockPunch)
	{
		CastRockPunch();
	}
	else if (bIsCastingLightningBolt)
	{
		CastLightningBolt();
	}

	if (isLightningCoolDown)
	{
		if (UGameplayStatics::GetRealTimeSeconds(GetWorld()) >= BoltTimer)
		{
			isLightningCoolDown = false;
		}
	}
	if (isRockCooldown)
	{
		if (UGameplayStatics::GetRealTimeSeconds(GetWorld()) >= RockPunchTimer)
		{
			isRockCooldown = false;
		}
	}
	if (isIceCooldown)
	{
		if (UGameplayStatics::GetRealTimeSeconds(GetWorld()) >= IceBlockTimer)
		{
			isIceCooldown = false;
		}
	}

}

// Called to bind functionality to input
void AMaxCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	// Set up gameplay key bindings
	check(InputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAction("Dash", IE_Pressed, this, &AMaxCharacter::Dash);
	InputComponent->BindAction("Dash", IE_Released, this, &AMaxCharacter::StopDashing);

	InputComponent->BindAxis("MoveForward", this, &AMaxCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMaxCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &AMaxCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &AMaxCharacter::LookUpAtRate);

	// Spell Casting Inputs
	InputComponent->BindAction("CastSpellOne", IE_Pressed, this, &AMaxCharacter::OnFire1);
	InputComponent->BindAction("CastSpellOne", IE_Released, this, &AMaxCharacter::OnRelease1);

	InputComponent->BindAction("CastSpellTwo", IE_Pressed, this, &AMaxCharacter::OnFire2);
	InputComponent->BindAction("CastSpellTwo", IE_Released, this, &AMaxCharacter::OnRelease2);

	InputComponent->BindAction("CastSpellThree", IE_Pressed, this, &AMaxCharacter::OnFire3);
	InputComponent->BindAction("CastSpellThree", IE_Released, this, &AMaxCharacter::OnRelease3);

	//InputComponent->BindAction("CastSpellFour", IE_Pressed, this, &AMaxCharacter::OnFire4);
	//InputComponent->BindAction("CastSpellFour", IE_Released, this, &AMaxCharacter::OnRelease4);


}

float AMaxCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	//Take away from health
	HealthPoints -= DamageAmount;
	//Check if player is alive
	if (HealthPoints <= 0.f)
	{
		//Do Death Animation
		//Play Audio
		//Set collision off
		GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Blue, TEXT("Player Dead"));
		FName ConvertedName = FName(*GetWorld()->GetName());
		UGameplayStatics::OpenLevel(this, ConvertedName, false);
		SetActorEnableCollision(false);
	}
	else
	{
		//Do Damage Animation
		//Play Damage Audio
		//Apply Knockback
		LaunchCharacter(GetActorForwardVector()*KnockbackForce, true, true);
		GEngine->AddOnScreenDebugMessage(1, 50.f, FColor::Blue, TEXT("Player Damaged"));
	}
	return HealthPoints;
}

void AMaxCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMaxCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMaxCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AMaxCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AMaxCharacter::OnFire1()
{
	bIsCastingLightningBolt = true;
	RotateCharacterTowardsTarget(GetTargetedObject());
}

void AMaxCharacter::OnFire2()
{
	bIsCastingRockPunch = true;
	RotateCharacterForward();
}

void AMaxCharacter::OnFire3()
{
	bIsCastingIceBlock = true;
}

void AMaxCharacter::OnFire4()
{
	bIsCastingFireBall = true;
}

void AMaxCharacter::OnRelease1()
{
	isCasting = false;
	bIsCastingLightningBolt = false;
}

void AMaxCharacter::OnRelease2()
{
	isCasting = false;
	bIsCastingRockPunch = false;
}

void AMaxCharacter::OnRelease3()
{
	isCasting = false;
	bIsCastingIceBlock = false;
}

void AMaxCharacter::OnRelease4()
{
	isCasting = false;
	bIsCastingFireBall = false;
}

void AMaxCharacter::CastFireBall()
{
	//// try and fire a projectile
	//if (Fireball != NULL)
	//{
	//	const FRotator SpawnRotation = GetControlRotation();
	//	// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
	//	const FVector SpawnLocation = SpellOffsetComponent->GetComponentLocation();

	//	UWorld* const World = GetWorld();
	//	if (World != NULL && ManaPoints > FireballMana && !isCasting && UGameplayStatics::GetRealTimeSeconds(GetWorld()) >= FireBallTimer)
	//	{
	//		// spawn the projectile at the muzzle
	//		World->SpawnActor<AActor>(Fireball, SpawnLocation, SpawnRotation);
	//		ManaPoints -= FireballMana;

	//		// Update FireBallTimer
	//		FireBallTimer = UGameplayStatics::GetRealTimeSeconds(GetWorld()) + FireBallCoolDown;
	//	}
	//}

	// try and play the sound if specified
	//if (FireSound != NULL)
	//{
	//	UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	//}

	//// try and play a firing animation if specified
	//if (FireAnimation != NULL)
	//{
	//	// Get the animation object for the arms mesh
	//	UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
	//	if (AnimInstance != NULL)
	//	{
	//		AnimInstance->Montage_Play(FireAnimation, 1.f);
	//	}
	//}

}

void AMaxCharacter::CastLightningBolt()
{
	// try and fire a projectile
	if (Firedart != NULL && UGameplayStatics::GetRealTimeSeconds(GetWorld()) >= BoltTimer)
	{
		const FRotator SpawnRotation = GetControlRotation();
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		const FVector SpawnLocation = SpellOffsetComponent->GetComponentLocation();

		UWorld* const World = GetWorld();
		if (World != NULL && ManaPoints > FiredartMana && !isCasting)
		{
			// spawn the projectile at the muzzle
			World->SpawnActor<AActor>(Firedart, SpawnLocation, SpawnRotation);
			ManaPoints -= FiredartMana;
		}
		isLightningCoolDown = true;
		// Update BoltTimer to the next time we can cast
		BoltTimer = UGameplayStatics::GetRealTimeSeconds(GetWorld()) + BoltCoolDown;
	}


	// try and play the sound if specified
	//if (FireSound != NULL)
	//{
	//	UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	//}

	//// try and play a firing animation if specified
	//if (FireAnimation != NULL)
	//{
	//	// Get the animation object for the arms mesh
	//	UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
	//	if (AnimInstance != NULL)
	//	{
	//		AnimInstance->Montage_Play(FireAnimation, 1.f);
	//	}
	//}
}

void AMaxCharacter::CastRockPunch()
{
	if (RockPunch != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL && ManaPoints > RockPunchMana && !isCasting &&  UGameplayStatics::GetRealTimeSeconds(GetWorld()) >= RockPunchTimer)
		{
			// spawn the projectile at the muzzle
			//World->SpawnActor<AActor>(RockPunch, SpawnLocation, SpawnRotation);
			ManaPoints -= RockPunchMana;
			/*MySpellBook->RockPunch(SpawnLocation, SpawnRotation);*/
			isRockCooldown = true;
			//check if enemy got attacked already
			bool EnemyHit = false;

			// For each rock in NumberOfRocks do a line trace
			for (uint8 i = 0; i < NumberOfRocks; i++)
			{
				float PitchOffSet = FMath::FRandRange(-MaxDegreesOfSpread, MaxDegreesOfSpread);
				float YawOffSet = FMath::FRandRange(-MaxDegreesOfSpread, MaxDegreesOfSpread);
				//float RandomRollRotation = FMath::FRandRange(0.f, 360.f);
				const FRotator SpawnRotation = GetControlRotation() + FRotator(PitchOffSet, YawOffSet, 0.f);

				// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
				const FVector SpawnLocation = SpellOffsetComponent->GetComponentLocation();

				// Collect infor for the trace
				const FVector StartTrace = SpawnLocation; // trace start is the camera location
				const FVector Direction = SpawnRotation.Vector(); // Get a unit vector pointing forward from our start location
				const FVector EndTrace = StartTrace + Direction * RockPunchRange; // Define the distance of the Trace

																				  // Perform trace to retrieve hit info
				FCollisionQueryParams TraceParams(FName(TEXT("RockPunchTrace")), true, this);
				TraceParams.bTraceAsyncScene = true;
				TraceParams.bReturnPhysicalMaterial = true;

				// Simple trace function
				FHitResult ObjectHit(ForceInit);
				GetWorld()->LineTraceSingleByChannel(ObjectHit, StartTrace, EndTrace, COLLISION_DAMAGEABLE, TraceParams);
				
				//check if it hit something
				if (ObjectHit.bBlockingHit)
				{
					//check if its an enemy
					if (ObjectHit.GetActor()->IsA(ABanditCharacter::StaticClass()))
					{
						ABanditCharacter* Bandit = Cast<ABanditCharacter>(ObjectHit.GetActor());
						if (Bandit)
						{
							if (!EnemyHit)
							{
								UGameplayStatics::ApplyDamage(Bandit, RockPunchDamage, GetInstigatorController(), this, UDamageType::StaticClass());
								EnemyHit = true;
							}
						} 
						else
						{
							return;
						}
					}
					else if (ObjectHit.GetActor()->IsA(ABaseTicker::StaticClass()))
					{
						ABaseTicker* Ticker = Cast<ABaseTicker>(ObjectHit.GetActor());
						if (Ticker)
						{
							if (!EnemyHit)
							{
								UGameplayStatics::ApplyDamage(Ticker, RockPunchDamage, GetInstigatorController(), this, UDamageType::StaticClass());
								EnemyHit = true;
							}
						}
						else
						{
							return;
						}
					}
				}


				// Debug line for the trace
				if (bIsDebugging)
				{
					DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(255, 0, 0, 255), true, 1.5f);
				}
			}

			// Update RockPunchTimer
			RockPunchTimer = UGameplayStatics::GetRealTimeSeconds(GetWorld()) + RockPunchCoolDown;
		}
	}
}

void AMaxCharacter::CastIceBlock()
{
	if (IceBlock != NULL)
	{
		const FRotator SpawnRotation = FRotator::ZeroRotator;
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		FVector SpawnLocation = SpellOffsetComponent->GetComponentLocation();
		SpawnLocation.X -= 200.f;
		UWorld* const World = GetWorld();
		if (World != NULL && ManaPoints > IceBlockMana && !isCasting && UGameplayStatics::GetRealTimeSeconds(GetWorld()) >= IceBlockTimer)
		{
			bCanCastIceBlock = true;
			// spawn the projectile at the muzzle
			World->SpawnActor<AActor>(IceBlock, SpawnLocation, SpawnRotation);
			ManaPoints -= IceBlockMana;

			isIceCooldown = true;
			// Update IceBlockTimer
			IceBlockTimer = UGameplayStatics::GetRealTimeSeconds(GetWorld()) + IceBlockCoolDown;
		}
		else
		{
			bCanCastIceBlock = false;
		}
	}
}

void AMaxCharacter::Dash()
{
	//Check if player isnt sprinting,exhausted and has enough stamina to dash
	if (!isDashing && !isExhausted && StaminaPoints > 0 )
	{
		
		//enable dash
		isDashing = true;
		//adjust move speed for character movement
		MoveSpeed = CurRunSpeed;
	}
}

void AMaxCharacter::StopDashing()
{
	isDashing = false;
}

FVector AMaxCharacter::GetTargetedObject()
{
	// Shoot a ray stright out from the camera
	FVector CamLocation;
	FRotator CamRotation;

	Controller->GetPlayerViewPoint(CamLocation, CamRotation);

	// Collect infor for the trace
	const FVector StartTrace = CamLocation; // trace start is the camera location
	const FVector Direction = CamRotation.Vector(); // Get a unit vector pointing forward from our start location
	const FVector EndTrace = StartTrace + Direction * TargetingRange; // Define the distance of the Trace

																	  // Perform trace to retrieve hit info
	FCollisionQueryParams TraceParams(FName(TEXT("TargetingTrace")), true, this);
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = true;

	// Simple trace function
	FHitResult ObjectHit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(ObjectHit, StartTrace, EndTrace, COLLISION_TARGETABLE, TraceParams);

	// Get the vector of the hit
	FVector HitVector = ObjectHit.Location;

	// Debug line for the trace
	if (bIsDebugging)
	{
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(0, 255, 0, 255), true, 1.5f);
		//GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Yellow, FString::Printf(TEXT("Hit Vector: %s"), HitVector));
	}

	// Return the vector of the hit target in world coordinates
	return HitVector;
}

void AMaxCharacter::RotateCharacterTowardsTarget(FVector Target)
{
	// Find the vector between the player and the target
	FVector LookAtVector = Target - GetActorLocation();

	// Caculate Yaw rotation to face the target
	FRotator LookRotation = FRotator(0.f, LookAtVector.Rotation().Yaw, 0.f);

	// Make player face the target
	this->SetActorRotation(LookRotation);
}

void AMaxCharacter::RotateCharacterForward()
{
	// Get Camera's Rotation
	FVector CamLocation;
	FRotator CamRotation;

	Controller->GetPlayerViewPoint(CamLocation, CamRotation);

	// Rotate Player so they are in line with the camera rotation
	// AKA facing forward.
	FRotator LookRotation = FRotator(0.f, CamRotation.Yaw, 0.f);
	this->SetActorRotation(LookRotation);
}