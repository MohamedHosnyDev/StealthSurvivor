// Copyright Epic Games, Inc. All Rights Reserved.

#include "StealthSurvivorGameMode.h"
#include "StealthSurvivorCharacter.h"
#include "UObject/ConstructorHelpers.h"

AStealthSurvivorGameMode::AStealthSurvivorGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
