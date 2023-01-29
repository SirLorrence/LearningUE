// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabberComponent.h"

#include "AssetSelection.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabberComponent::UGrabberComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UGrabberComponent::BeginPlay() {
	Super::BeginPlay();
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	FVector TargetLocation = GetComponentLocation() + GetForwardVector() * holdDistance;
	PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
}

// Called every frame
void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	if (PhysicsHandle->GetGrabbedComponent() != nullptr) {
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * holdDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
	// FRotator componentRotation = GetComponentRotation();
	// FString rotationString = componentRotation.ToCompactString();
	// // UE_LOG(LogTemp, Display,TEXT("Rotation: %s"),*rotationString);
	//
	// UWorld* World = GetWorld();	
	// float time = World->GetTimeSeconds();
	// UE_LOG(LogTemp,Display,TEXT("Time: %f"), time);
}

void UGrabberComponent::Grab() {
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	FHitResult HitResult;
	
	if (GetGrabberInReach(HitResult)) {
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->WakeAllRigidBodies();
		HitResult.GetActor()->Tags.Add("Grabbed");
		PhysicsHandle->GrabComponentAtLocationWithRotation(HitComponent,
		                                                   NAME_None,
		                                                   HitResult.ImpactPoint,
		                                                   GetComponentRotation());
		// AActor* Actor = HitResult.GetActor();
		// // DrawDebugSphere(GetWorld(), HitResult.Location, 10,10,FColor::Red, false, 5);
		// DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10,10,FColor::Green,  false, 5);
		// UE_LOG(LogTemp, Display, TEXT("Actor Hit: %s"), *Actor->GetActorNameOrLabel());
	}
}

void UGrabberComponent::Release() {
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle->GetGrabbedComponent() != nullptr) {
		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		PhysicsHandle->GetGrabbedComponent()->GetOwner()->Tags.Remove("Grabbed");
		PhysicsHandle->ReleaseComponent();
	}

	UE_LOG(LogTemp, Display, TEXT("Released"))
}

UPhysicsHandleComponent* UGrabberComponent::GetPhysicsHandle() const {
	UPhysicsHandleComponent* result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (result == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("PhysicsHandle is NULL"));
	}
	return result;
}

bool UGrabberComponent::GetGrabberInReach(FHitResult& OutHitResult) const {
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * grabDistance;
	DrawDebugLine(GetWorld(), Start, End, FColor::Red);
	DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue, false, 5);

	const FCollisionShape cSphere = FCollisionShape::MakeSphere(grabRadius);

	//can get the trace collision channel from Config/DefaultEngine.ini
	return GetWorld()->SweepSingleByChannel(OutHitResult,
	                                        Start,
	                                        End,
	                                        FQuat::Identity,
	                                        ECC_GameTraceChannel2,
	                                        cSphere);
}
