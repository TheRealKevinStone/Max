// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MaxSpellbook.h"
#include "MaxCharacter.generated.h"

UCLASS()
class MAX_API AMaxCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	// Sets default values for this character's properties
	AMaxCharacter();

	/*** DEBUG STUFF ***/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDebugging = true;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BackHopForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* SpellOffsetComponent;

	/******* TARGETING PARAMS *******/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	float TargetingRange = 15000.f;

	/****** LIGHTING BOLT *****/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightning Bolt")
	float BoltCoolDown = 0.125f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightning Bolt")
	float BoltRange = 2000.f;

	float BoltTimer;

	/****** ROCK PUNCH *****/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rock Punch")
	uint8 NumberOfRocks = 7;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rock Punch")
	float MaxDegreesOfSpread = 7.5f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rock Punch")
	float RockPunchRange = 2000.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rock Punch")
	float RockPunchCoolDown = 0.25f;

	float RockPunchTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rock Punch")
	float RockPunchDamage;

	/****** FIREBALL *****/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Ball")
	float FireBallCoolDown = 5.f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Fire Ball")
	float FireBallTimer;

	/***** ICE BLOCK *****/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ice Block")
	float IceBlockCoolDown = 10.f;

	float IceBlockTimer;

	/***** HEALTH *****/
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HealthPoints = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float KnockbackForce;

	UFUNCTION(BlueprintCallable, Category = "Health")
	float getHealthtPoints() { return HealthPoints; }
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	void setHP(float setHealthPoints)
		{
			//if your current health becomes greater than the max health
			if (setHealthPoints > MaxHealth)
			{
				HealthPoints = MaxHealth; //set it to the max health limit
			}
			else
			{
				HealthPoints = setHealthPoints; //if not, set your health to whatever your current health is
			}
		}

	/***** MANA *****/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxMana = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ManaPoints = 100.0f;

	UFUNCTION(BlueprintCallable, Category = "Mana")
		float getManaPoints() { return ManaPoints; }

	UFUNCTION(BlueprintCallable, Category = "Mana")
		void setMP(float setManaPoints)
	{
		
		if (setManaPoints > MaxMana)
		{
			ManaPoints = MaxMana; 
		}
		else
		{
			ManaPoints = setManaPoints; 
		}
	}

	/***** STAMINA *****/
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float StaminaPoints = 100.0f;

	UFUNCTION(BlueprintCallable, Category = "Stamina")
		float getStaminaPoints() { return StaminaPoints; }

	UFUNCTION(BlueprintCallable, Category = "Stamina")
		void setSP(float setStaminaPoints)
	{

		if (setStaminaPoints > MaxStamina)
		{
			StaminaPoints = MaxStamina;
		}
		else
		{
			StaminaPoints = setStaminaPoints;
		}
	}
	//*****DASH******//
	//Stamina decrement rate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxMovement")
	float DecrementRate;
	
	//Stamina recovery rate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxMovement")
	float RecoveryRate;

	//This is the current speed we would run at if we wanted to dash
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxMovement")
	float CurRunSpeed;

	//Default walk speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxMovement")
	float CurWalkSpeed;
	
	float MoveSpeed;
	
	bool bIsGrounded;

	//indicate if dashing
	bool isDashing = false;

	//if stamina ran out
	bool isExhausted = false;

	bool isCasting;

	bool bIsCastingLightningBolt;
	bool bIsCastingFireBall;
	bool bIsCastingRockPunch;
	bool bIsCastingIceBlock;

	//For animInstance
	bool bCanCastIceBlock;

	void Dash();
	void StopDashing();

protected:
	//*********Spells***********//
	UPROPERTY(EditDefaultsOnly, Category = Spells)
	TSubclassOf<class AActor> Firedart;

	UPROPERTY(EditDefaultsOnly, Category = Spells)
	TSubclassOf<class AActor> Fireball;

	UPROPERTY(EditDefaultsOnly, Category = Spells)
	TSubclassOf<class AActor> IceBlock;

	UPROPERTY(EditDefaultsOnly, Category = Spells)
	TSubclassOf<class AActor> RockPunch;

	MaxSpellbook* MySpellBook;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category= Spells)
	float FiredartMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spells)
	float FireballMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spells)
	float IceBlockMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spells)
	float RockPunchMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spells)
	float ManaRecoverRate;


protected:
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	* Called via input to turn at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	/**
	* Called via input to turn look up/down at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void LookUpAtRate(float Rate);

	void OnFire1();
	void OnFire2();
	void OnFire3();
	void OnFire4();
	void OnRelease1();
	void OnRelease2();
	void OnRelease3();
	void OnRelease4();

	void CastFireBall();
	void CastLightningBolt();
	void CastRockPunch();
	void CastIceBlock();

	FVector GetTargetedObject();
	void RotateCharacterTowardsTarget(FVector Target);
	void RotateCharacterForward();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

public:

	//Taking Damage from enemies
	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;


	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	
	
};
