// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

UCLASS()
class SIMPLESHOOTER_API AWeaponActor : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponActor();
	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* MuzzleFlashSystem;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* ImpactParticleSystem;

	UPROPERTY(EditAnywhere, Category="Sound")
	USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere, Category="Sound")
	USoundBase* ImpactSound; 

	AController* GetOwnerController() const;

	bool WeaponTrace(FHitResult& HitOut);

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000.f;

	float Damage = 10.f;
};
