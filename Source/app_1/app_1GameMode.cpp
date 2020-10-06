// Copyright Epic Games, Inc. All Rights Reserved.

#include "app_1GameMode.h"
#include "app_1Character.h"
#include "UObject/ConstructorHelpers.h"

Aapp_1GameMode::Aapp_1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
