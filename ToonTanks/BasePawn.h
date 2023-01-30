// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	void HandleDestruction() const;

protected:
	void RotateTurret(FVector LookAtTarget);
	void Fire();

private:
	UPROPERTY(VisibleAnywhere, Category="Pawn Meshes")
	class UCapsuleComponent* CapsuleComp; //forward def (incomplete type)

	UPROPERTY(EditAnywhere)
	class UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere)
	class USoundBase* DeathSound;

	UPROPERTY(VisibleAnywhere, Category="Pawn Meshes")
	UStaticMeshComponent* BaseMesh; // static mesh component is already apart of this class, no need to forward def

	UPROPERTY(VisibleAnywhere, Category="Pawn Meshes")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TSubclassOf<class AProjectile> ProjectileClass; //stores a UClass

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShakeBase> DeathCameraShake;

	
};
