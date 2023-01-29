// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}


void UTriggerComponent::BeginPlay() {
	Super::BeginPlay();

	UE_LOG(LogTemp, Display, TEXT("Hello World"));
};

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Actor = GetAcceptableActor();
	if(Actor != nullptr) {
		// check if its a uprimitivecomponent then output the pointer to that type
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		if(Component != nullptr) {
			Component->SetSimulatePhysics(false);
		}
		Component->AttachToComponent(this,FAttachmentTransformRules::KeepWorldTransform);
		Mover->SetShouldMove(true);
		// UE_LOG(LogTemp,Display,TEXT("Unlocking"));
	}
	else {
		Mover->SetShouldMove(false);
		// UE_LOG(LogTemp,Display,TEXT("Relocking"));
	}
}

void UTriggerComponent::SetMover(UMoverComponent* MoverComponent) {
	Mover = MoverComponent;
}


AActor* UTriggerComponent::GetAcceptableActor() const {
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	// Like a foreach loop
	for (AActor* Actor : Actors) {
		// FString ActorName = Actor->GetActorNameOrLabel();
		if (Actor->ActorHasTag(UnlockTag) && !Actor->ActorHasTag("Grabbed")) {
			return Actor;
			// UE_LOG(LogTemp, Display, TEXT("Unlocking"));
		}
	}
	return nullptr;
}


