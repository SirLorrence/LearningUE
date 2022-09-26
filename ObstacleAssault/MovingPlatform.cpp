// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"


// Sets default values
AMovingPlatform::AMovingPlatform() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay() {
	Super::BeginPlay();

	actors_name = GetName();
	start_location = GetActorLocation();
	SetActorLocation(start_location);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	MovePlat(DeltaTime);
	RotatePlat(DeltaTime);
}

void AMovingPlatform::MovePlat(float tick) {
	if (ReversePlatDir()) {
		const float over_shoot = current_distance - move_distance;
		UE_LOG(LogTemp, Display, TEXT("%s over shoot: %f"), *actors_name, over_shoot);
		// '*' before the string converse FString to string....kinda weird
		const FVector move_direction = platform_velocity.GetSafeNormal();
		start_location += move_direction * move_distance;
		SetActorLocation(start_location);
		platform_velocity *= -1;
	}
	else {
		// movement logic
		FVector current_location{GetActorLocation()};
		current_location += platform_velocity * tick;
		SetActorLocation(current_location);
	}
}

void AMovingPlatform::RotatePlat(float tick) {
	// UE_LOG(LogTemp, Display, TEXT("Is Rotating"));
	AddActorLocalRotation(rotation_velocity * tick); // add the current rotation, no need to deal with negative rotation
}

bool AMovingPlatform::ReversePlatDir() const {
	return GetDistMoved() > move_distance;
}

float AMovingPlatform::GetDistMoved() const {
	return FVector::Dist(start_location, GetActorLocation());
}
