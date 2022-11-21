// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabberSceneComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UGrabberSceneComponent::UGrabberSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabberSceneComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabberSceneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// FRotator rotation = GetComponentRotation();
	// FString s_rotation = rotation.ToCompactString();
	// UE_LOG(LogTemp,Display, TEXT("Rotation: %s"), *s_rotation);
	// float time = GetWorld()->TimeSeconds; 
	// UE_LOG(LogTemp, Display, TEXT("Time: %f"),time);

	FVector start = GetComponentLocation();
	FVector end = start + GetForwardVector() * max_grab_dist;
	DrawDebugLine(GetWorld(),start,end,FColor::Red);

	float damage = 0;
	float& damage_ref = damage;
	damage_ref = 5; // lol i predicted him
	UE_LOG(LogTemp,Display, TEXT("Original Damage: %f"), damage);
	UE_LOG(LogTemp,Display, TEXT("Reference Damage: %f"), damage_ref);
	
	
}

