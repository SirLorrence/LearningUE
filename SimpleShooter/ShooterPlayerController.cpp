// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"

#include "Blueprint/UserWidget.h"


void AShooterPlayerController::BeginPlay() {
	Super::BeginPlay();
	HUD = CreateWidget(this,HUDScreenClass);
	if(HUD != nullptr) HUD->AddToViewport();
}

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner) {
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	UE_LOG(LogTemp, Display, TEXT("Game Over"));
	HUD->RemoveFromViewport();
	if (bIsWinner) {
		UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
		if (WinScreen != nullptr) {
			WinScreen->AddToViewport();
		}
	}
	else {
		UUserWidget* LoseScreen = CreateWidget(this, LooseScreenClass);
		if (LoseScreen != nullptr) {
			LoseScreen->AddToViewport();
		}
	}

	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}
