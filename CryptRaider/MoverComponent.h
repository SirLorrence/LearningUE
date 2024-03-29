// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoverComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRAIDER_API UMoverComponent : public UActorComponent {
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMoverComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void SetShouldMove(bool value);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	FVector move_offset{};
	UPROPERTY(EditAnywhere)
	float move_seconds{5};
	UPROPERTY(EditAnywhere)
	bool should_move{false};

	FVector origin_location{};
};
