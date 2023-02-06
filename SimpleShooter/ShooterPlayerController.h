// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterPlayerController : public APlayerController {
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<class UUserWidget> LooseScreenClass;
	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<class UUserWidget> WinScreenClass;
	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<class UUserWidget> HUDScreenClass;
	UPROPERTY()
	class UUserWidget* HUD;
	
	FTimerHandle RestartTimer;


	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.f;

protected:
	virtual void BeginPlay() override;

public:
	virtual void GameHasEnded(AActor* EndGameFocus, bool bIsWinner) override;
};
