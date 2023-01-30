// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AProjectile::AProjectile() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Move Component"));
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Particles"));

	RootComponent = StaticMeshComponent;
	ParticleSystemComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay() {
	Super::BeginPlay();

	//Look into this more "OnComponentHit" Delegate
	StaticMeshComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	if(LaunchSound)
		UGameplayStatics::PlaySoundAtLocation(this,LaunchSound,GetActorLocation(),GetActorRotation());
}

// Called every frame
void AProjectile::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                        FVector NormalImpulse, const FHitResult& Hit) {
	// UE_LOG(LogTemp,Display,TEXT("Hit. HitComp: %s, Other Actor: %s, Other Comp: %s"),*HitComp->GetName(),*OtherActor->GetName(), *OtherComp->GetName());
	AActor* MyOwner = GetOwner();
	if (MyOwner == nullptr) {
		Destroy();
		return;
	}

	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();
	UClass* DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner) {
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);

		//emit particles
		if(HitParticles)
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
		if(HitSound)
			UGameplayStatics::PlaySoundAtLocation(this,HitSound,GetActorLocation(),GetActorRotation());
		if(HitCameraShake)
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShake);
	}
	Destroy();
}
