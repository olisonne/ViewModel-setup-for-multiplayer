// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class VIEWMODELTEST_API UTGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UTGameInstance();
	static UTGameInstance* GetGameInstance();

private:
	static UTGameInstance* Self;
};
