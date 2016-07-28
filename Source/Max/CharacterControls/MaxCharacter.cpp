// Fill out your copyright notice in the Description page of Project Settings.

#include "Max.h"
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
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create SpellOffsetComponent
	SpellOffsetComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SpellOffset"));
	SpellOffsetComponent->SetupAttachment(RootComponent);

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
}

// Called every frame
void AMaxCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Yellow, FString::Printf(TEXT("Dashing: %s"), isDashing ? TEXT("true") : TEXT("false")));
	if (isDashing && Controller != NULL)
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
	InputComponent->BindAction("CastSpellOne", IE_Released, this, &AMaxCharacter::OnRelease);

	InputComponent->BindAction("CastSpellTwo", IE_Pressed, this, &AMaxCharacter::OnFire2);
	InputComponent->BindAction("CastSpellTwo", IE_Released, this, &AMaxCharacter::OnRelease);

	InputComponent->BindAction("CastSpellThree", IE_Pressed, this, &AMaxCharacter::OnFire3);
	InputComponent->BindAction("CastSpellThree", IE_Released, this, &AMaxCharacter::OnRelease);

	InputComponent->BindAction("CastSpellFour", IE_Pressed, this, &AMaxCharacter::OnFire4);
	InputComponent->BindAction("CastSpellFour", IE_Released, this, &AMaxCharacter::OnRelease);


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
	// try and fire a projectile
	if (Firedart != NULL)
	{
		const FRotator SpawnRotation = GetControlRotation();
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		const FVector SpawnLocation = SpellOffsetComponent->GetComponentLocation();

		UWorld* const World = GetWorld();
		if (World != NULL && ManaPoints>FiredartMana && !isCasting)
		{
			// spawn the projectile at the muzzle
			World->SpawnActor<AActor>(Firedart, SpawnLocation, SpawnRotation);
			ManaPoints -= FiredartMana;
		}
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

void AMaxCharacter::OnFire2()
{
	// try and fire a projectile
	if (Fireball != NULL)
	{
		const FRotator SpawnRotation = GetControlRotation();
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		const FVector SpawnLocation = SpellOffsetComponent->GetComponentLocation();

		UWorld* const World = GetWorld();
		if (World != NULL&&ManaPoints>FireballMana && !isCasting)
		{
			// spawn the projectile at the muzzle
			World->SpawnActor<AActor>(Fireball, SpawnLocation, SpawnRotation);
			ManaPoints -= FireballMana;
		}
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

void AMaxCharacter::OnFire3()
{
	if (IceBlock != NULL)
	{
		const FRotator SpawnRotation = GetControlRotation();
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		const FVector SpawnLocation = SpellOffsetComponent->GetComponentLocation();

		UWorld* const World = GetWorld();
		if (World != NULL&&ManaPoints>IceBlockMana && !isCasting)
		{
			// spawn the projectile at the muzzle
			World->SpawnActor<AActor>(IceBlock, SpawnLocation, SpawnRotation);
			ManaPoints -= IceBlockMana;
		}
	}
}

void AMaxCharacter::OnFire4()
{
	if (RockPunch != NULL)
	{
		const FRotator SpawnRotation = GetControlRotation();
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		const FVector SpawnLocation = SpellOffsetComponent->GetComponentLocation();

		UWorld* const World = GetWorld();
		if (World != NULL&&ManaPoints>RockPunchMana && !isCasting)
		{
			// spawn the projectile at the muzzle
			World->SpawnActor<AActor>(RockPunch, SpawnLocation, SpawnRotation);
			ManaPoints -= RockPunchMana;
		}
	}
}

void AMaxCharacter::OnRelease()
{
	isCasting = false;
}

void AMaxCharacter::Dash()
{
	//Check if player isnt sprinting,exhausted and has enough stamina to dash
	if (!isDashing&&!isExhausted&&StaminaPoints > 0)
	{
		//enable dash
		isDashing = true;
		//adjust move speed for character movement
		MoveSpeed = CurRunSpeed;
	}







	//bIsDashing = true;
	//if (GetVelocity().Z == 0.f)
	//{
	//	// find out which way is forward
	//	const FRotator Rotation = Controller->GetControlRotation();
	//	const FRotator YawRotation(0, Rotation.Yaw, 0);

		//FVector LaunchVelocity = GetVelocity().GetSafeNormal() * DashForce;
		//LaunchVelocity.Z = 0.f;

		//LaunchCharacter(LaunchVelocity, true, false);
	//}
	//// get forward vector
	//const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	//// get right vector 
	//const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	//FVector LaunchVelocity = GetVelocity().SafeNormal() * 1200.f;
	//DashVelocity.Z = 0.f;
	//LaunchCharacter(DashVelocity, true, false);

	//FVector MovementDirection = GetVelocity().SafeNormal();
	//AddMovementInput(MovementDirection, 1.0f);
}

void AMaxCharacter::StopDashing()
{
	isDashing = false;
}