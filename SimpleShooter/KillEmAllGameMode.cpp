// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "ShooterAIController.h"


void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner) {
	for (AController* Controller : TActorRange<AController>(GetWorld())) {
		// bool bIsPlayerController = Controller->IsPlayerController();
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);

		// if(bIsPlayerController && bIsPlayerWinner || !bIsPlayerController && !bIsPlayerWinner)
		// 	Controller->GameHasEnded(nullptr,true);
		//
		// if(bIsPlayerController && !bIsPlayerWinner || !bIsPlayerController && bIsPlayerWinner)
		// 	Controller->GameHasEnded(nullptr,false);
	}
}

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled) {
	Super::PawnKilled(PawnKilled);


	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr) {
		EndGame(false);
	}
	// loop over the ShooterAI in the world
	for (AShooterAIController* AIController : TActorRange<AShooterAIController>(GetWorld())) {
		if (AIController->IsAlive()) return;
	}
	EndGame(true);
}
