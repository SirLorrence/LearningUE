// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class OBSTACLEASSAULT_API AMovingPlatform : public AActor {
	GENERATED_BODY()
	// UPROPERTY() <-- makes it visible in the editor

	FVector start_location; //FVector <--- Unreal uses the 'F' prefix for naming structs
	FString actors_name;

	UPROPERTY(VisibleAnywhere) // (VisibleAnywhere) dope. wished unity had this built in
	float current_distance;

	UPROPERTY(EditAnywhere)
	float move_distance {100};
	UPROPERTY(EditAnywhere)
	FRotator rotation_velocity;
	UPROPERTY(EditAnywhere)
	FVector platform_velocity{FVector(100, 0, 0)};

	void MovePlat(float tick);
	void RotatePlat(float tick);

	// const methods insure that it can't modify the class within it
	bool ReversePlatDir() const;
	float GetDistMoved() const; 


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Sets default values for this actor's properties
	AMovingPlatform();




};
