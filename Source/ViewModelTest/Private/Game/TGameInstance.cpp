// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/TGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogCGGameInstance, All, All);

UTGameInstance* UTGameInstance::Self = nullptr;

UTGameInstance::UTGameInstance()
{
	Self = this;
}

UTGameInstance* UTGameInstance::GetGameInstance()
{
#if WITH_EDITOR

	if (IsValid(GEngine) && IsValid(GEngine->GameViewport))
	{
		UTGameInstance* GameInstance = Cast<UTGameInstance>(GEngine->GameViewport->GetGameInstance());

		if (IsValid(GameInstance))
		{
			return Cast<UTGameInstance>(GEngine->GameViewport->GetGameInstance());
		}
	}

#endif

	return Self;
}
