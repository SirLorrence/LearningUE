// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

	UFUNCTION(BlueprintPure)
	bool IsAlive() const;
	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;
	void Shoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Creating Custom 'TakeDamage' Method
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	UPROPERTY(EditAnywhere)
	float RotationRate = 50.f;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.f;
	UPROPERTY(VisibleInstanceOnly)
	float Health;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUpRate(float Value);
	void LookRightRate(float Value);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AWeaponActor> WeaponClass;

	UPROPERTY()
	class AWeaponActor* Weapon; 
	
};
