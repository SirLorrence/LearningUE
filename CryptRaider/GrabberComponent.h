// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/SceneComponent.h"
#include "GrabberComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRAIDER_API UGrabberComponent : public USceneComponent {
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabberComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Release();
	UFUNCTION(BlueprintCallable)
	void Grab();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float grabDistance{400.0f};
	UPROPERTY(EditAnywhere)
	float grabRadius{100.0f};
	UPROPERTY(EditAnywhere)
	float holdDistance{200.0f};

	// UPhysicsHandleComponent Utility object for moving physics objects around.
	UPhysicsHandleComponent* GetPhysicsHandle() const;
	bool GetGrabberInReach(FHitResult& OutHitResult) const;
};
