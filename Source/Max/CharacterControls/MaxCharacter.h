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

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BackHopForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DashForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* SpellOffsetComponent;

	/***** HEALTH *****/
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HealthPoints = 100.0f;

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
	float MaxStamina = 100.0f;

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
	



protected:
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AActor> Firedart;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AActor> Fireball;

protected:
	bool bIsDashing;

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
	void Dash();
	void StopDashing();

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
