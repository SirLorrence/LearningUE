// Fill out your copyright notice in the Description page of Project Settings.


#include "MoverComponent.h"
#include "Math/UnrealMathUtility.h"


// Sets default values for this component's properties
UMoverComponent::UMoverComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UMoverComponent::BeginPlay() {
	Super::BeginPlay();

	origin_location = GetOwner()->GetActorLocation();
}


// Called every frame
void UMoverComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                    FActorComponentTickFunction* ThisTickFunction) {
	// UE_LOG(LogTemp, Display, TEXT("Is Moving"));
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// AActor* Owner = GetOwner(); // the address of the actor that the component is on
	// FVector owners_locations = Owner->GetActorLocation();
	// FString location_data = owners_locations.ToCompactString();
	// UE_LOG(LogTemp,Display,TEXT("Current Location: %s"), *location_data);
	// UE_LOG(LogTemp,Display, TEXT("%u"), Owner);

	if (should_move) {
		FVector current_location = GetOwner()->GetActorLocation();
		FVector target_location = origin_location + move_offset;
		float speed = FVector::Distance(origin_location, target_location) / move_seconds; // interesting

		FVector new_location = FMath::VInterpConstantTo(current_location, target_location, DeltaTime, speed);
		GetOwner()->SetActorLocation(new_location);
	}
}

void UMoverComponent::SetShouldMove(bool value) {
	should_move = value;
}
