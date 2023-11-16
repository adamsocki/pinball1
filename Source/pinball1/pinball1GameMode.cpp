// Copyright Epic Games, Inc. All Rights Reserved.

#include "pinball1GameMode.h"
#include "pinball1Character.h"
#include "UObject/ConstructorHelpers.h"

Apinball1GameMode::Apinball1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
