// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "ShooterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


void AShooterAIController::BeginPlay() {
	Super::BeginPlay();

	if (AIBehavior != nullptr) {
		RunBehaviorTree(AIBehavior);
		// PlayerPawn = Cast<APawn>(UGameplayStatics::GetPlayerPawn(this, 0));
		// GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}	
	// PlayerPawn = Cast<APawn>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// void AShooterAIController::Tick(float DeltaSeconds) {
// 	Super::Tick(DeltaSeconds);
//
// 	// if(LineOfSightTo(PlayerPawn)) {
// 	// 	GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
// 	// 	GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownLocation"), PlayerPawn->GetActorLocation());
// 	// }
// 	// else {
// 	// 	GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
// 	// }
//
//
// 	// Manual AI movement
// 	// if (LineOfSightTo(PlayerPawn)) {
// 	// 	SetFocus(PlayerPawn);
// 	// 	MoveToActor(PlayerPawn, 200);
// 	// }
// 	// else {
// 	// 	ClearFocus(EAIFocusPriority::Gameplay);
// 	// 	StopMovement();
// 	// }
// }

bool AShooterAIController::IsAlive() const {
	const AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
	if(ControlledCharacter != nullptr) {
		return ControlledCharacter->IsAlive();
	}
	return false;
}
