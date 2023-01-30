// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank() {
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));

	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed,this,&ATank::Fire);
}

void ATank::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	FHitResult HitResult;
	if (TankPlayerController) {
		TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint,
		                50.f,
		                12,
		                FColor::Blue,
		                false);
		RotateTurret(HitResult.ImpactPoint);
	}
}



// Called when the game starts or when spawned
void ATank::BeginPlay() {
	Super::BeginPlay();

	// PlayerControllerRef = static_cast<APlayerController*>(GetController());
	TankPlayerController = Cast<APlayerController>(GetController()); 
}

void ATank::HandleDestruction() {
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	bAlive=false;
}

//=========== Callback Methods

void ATank::Move(float Value) {
	FVector DeltaLocation = FVector::Zero();
	DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation, true);
	// UE_LOG(LogTemp,Display,TEXT("Move Value: %f"),Value);
}

void ATank::Turn(float Value) {
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation, true);
}
