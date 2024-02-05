// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/VM/TVMPlayerBase.h"
#include "TVMLocalPlayer.generated.h"

/**
 * 
 */
UCLASS()
class VIEWMODELTEST_API UTVMLocalPlayer : public UTVMPlayerBase
{
	GENERATED_BODY()

protected:
	virtual void SubscribeToPlayerState() override;
	virtual void UnsubscribeFromPlayerState() override;

	virtual void CreateViewModels() override;

	virtual void RegisterViewModels() override;
	virtual void UnregisterViewModels() override;

protected:
	virtual void OnPlayerStateLocallyControlled(bool bInLocallyControlled) override;
	
};
