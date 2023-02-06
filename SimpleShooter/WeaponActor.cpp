// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponActor.h"

#include "CollisionDebugDrawingPublic.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AWeaponActor::AWeaponActor() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));

	SetRootComponent(Root);
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWeaponActor::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void AWeaponActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

AController* AWeaponActor::GetOwnerController() const {
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return nullptr;
	AController* OwnerController = OwnerPawn->GetController();
	return OwnerController;
}

bool AWeaponActor::WeaponTrace(FHitResult& HitOut) {
	FVector Location;
	FRotator Rotation;

	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr) return false;
	
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	FVector End = Location + Rotation.Vector() * MaxRange;

	// You the AI and player can't shot themselves
	FCollisionQueryParams Parms;
	Parms.AddIgnoredActor(this); // the weapon
	Parms.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(HitOut, Location, End, ECC_GameTraceChannel1, Parms);
}

void AWeaponActor::PullTrigger() {
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlashSystem, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound,Mesh,TEXT("MuzzleFlashSocket"));

	
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr) return;

	FHitResult HitResult;

	if (WeaponTrace(HitResult)) {
		FVector ShotDir = HitResult.ImpactNormal;
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticleSystem, HitResult.Location,
		                                         ShotDir.Rotation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(),ImpactSound,HitResult.Location,ShotDir.Rotation());
		AActor* Actor = HitResult.GetActor();
		if (Actor != nullptr) {
			FPointDamageEvent DamageEvent(Damage, HitResult, ShotDir, nullptr);
			Actor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}

		// DrawDebugPoint(GetWorld(), HitResult.Location, 12, FColor::Red, true);
	}

	// DrawDebugPoint(GetWorld(), Location, 20, FColor::Red, true);
	// DrawLineTraces(GetWorld(),Location, End, )
	// DrawDebugCamera(GetWorld(), Location, Rotation, 90, 2, FColor::Red, true);
	// GEngine->AddOnScreenDebugMessage(-1,2.5f,FColor::Blue, TEXT("Shot"));
}
