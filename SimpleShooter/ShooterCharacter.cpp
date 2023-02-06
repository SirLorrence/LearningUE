// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"

#include "SimpleShooterGameModeBase.h"
#include "WeaponActor.h"
#include "Components/CapsuleComponent.h"


// Sets default values
AShooterCharacter::AShooterCharacter() {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

bool AShooterCharacter::IsAlive() const {
	return Health > 0.f;
}

float AShooterCharacter::GetHealthPercent() const {
	return Health / MaxHealth;
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay() {
	Super::BeginPlay();

	Health = MaxHealth;

	Weapon = GetWorld()->SpawnActor<AWeaponActor>(WeaponClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Weapon->SetOwner(this);
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Axis Inputs

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);

	// Mouse input can be called directly from Pawn class
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	// For controller input
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate);

	// Action Inputs

	PlayerInputComponent->BindAction(TEXT("JumpAction"), IE_Pressed, this, &AShooterCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("ShootAction"),IE_Pressed,this, &AShooterCharacter::Shoot);
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser) {
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser); // keeps base method info
	DamageToApply = FMath::Min(Health,DamageToApply);
	Health -= DamageToApply;
	UE_LOG(LogTemp, Display, TEXT("%s Health: %f"), *GetName(), Health);

	if(!IsAlive()) {
		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if(GameMode != nullptr) GameMode->PawnKilled(this);
		
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	
	// GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red,TEXT("%s Health: %f"), *EventInstigator->GetName(), Health);
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AShooterCharacter::MoveForward(float Value) {
	AddMovementInput(GetActorForwardVector() * Value);
}

void AShooterCharacter::MoveRight(float Value) {
	AddMovementInput(GetActorRightVector() * Value);
}

void AShooterCharacter::LookUpRate(float Value) {
	AddControllerPitchInput(Value * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRightRate(float Value) {
	AddControllerYawInput(Value * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::Shoot() {
	if(Weapon == nullptr) return;

	Weapon->PullTrigger();
}

