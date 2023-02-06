// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "ShooterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


void UBTService_PlayerLocationIfSeen::
TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	
	APawn* PlayerPawn = Cast<APawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if(PlayerPawn == nullptr) return;
	if(OwnerComp.GetAIOwner() == nullptr) return;
	if(OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn))
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
	else
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
}

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen() {
	NodeName = TEXT("Update Player Location if Seen");
}
