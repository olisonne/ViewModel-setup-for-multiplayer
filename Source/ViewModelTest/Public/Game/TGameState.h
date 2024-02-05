// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TGameState.generated.h"

/**
 * 
 */
UCLASS()
class VIEWMODELTEST_API ATGameState : public AGameState
{
	GENERATED_BODY()
public:
	virtual void PostInitializeComponents() override;

private:
	virtual void RegisterInViewModel();
};
