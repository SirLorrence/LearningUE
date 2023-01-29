// Copyright Epic Games, Inc. All Rights Reserved.

#include "CRaiderGameMode.h"
#include "CRaiderCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACRaiderGameMode::ACRaiderGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
