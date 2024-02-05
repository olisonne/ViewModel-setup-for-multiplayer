// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "TVMPlayers.generated.h"

class ATPlayerStateBase;
class UTViewModelSubsystem;
UCLASS()
class VIEWMODELTEST_API UTVMPlayers : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	UTVMLocalPlayer* GetVMLocalPlayer() const;

public:
	void RegisterPlayerState(ATPlayerStateBase* InPlayerState);
	void UnregisterPlayerState(ATPlayerStateBase* InPlayerState);

public:
	virtual void Initialize(UTViewModelSubsystem* InVMSubsystem = nullptr);
	virtual void BeginDestroy() override;

private:
	void CreateViewModels();
	void DestroyViewModels();

	void RegisterViewModels();
	void UnregisterViewModels();

	void RegisterLocalPlayerState(ATPlayerStateBase* InPlayerState);

	void UnregisterLocalPlayerState(ATPlayerStateBase* InPlayerState);

private:
	UPROPERTY()
	UTViewModelSubsystem* VMSubsystem = nullptr;

	UPROPERTY()
	UTVMLocalPlayer* VMLocalPlayer = nullptr;

	bool bInitialized = false;
};
