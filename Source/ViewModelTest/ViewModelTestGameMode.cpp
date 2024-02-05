// Copyright Epic Games, Inc. All Rights Reserved.

#include "ViewModelTestGameMode.h"
#include "ViewModelTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AViewModelTestGameMode::AViewModelTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
