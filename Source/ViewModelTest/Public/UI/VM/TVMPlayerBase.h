// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "TVMPlayerBase.generated.h"

class ATPlayerStateBase;
class UTVMProgressBarBase;
class UTViewModelSubsystem;

UCLASS()
class VIEWMODELTEST_API UTVMPlayerBase : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	void SetPlayerStateIsActive(bool bInActive);
	bool IsPlayerStateActive() const;

public:
	UFUNCTION(BlueprintCallable)
	void SetContextName(const FName& InContextName);

	UFUNCTION(BlueprintPure)
	FName GetContextName() const;

	UFUNCTION(BlueprintCallable)
	void SetPlayerState(ATPlayerStateBase* InPlayerState);

	UFUNCTION(BlueprintPure, FieldNotify)
	ATPlayerStateBase* GetPlayerState() const;

	UFUNCTION(BlueprintPure)
	UTVMProgressBarBase* GetVMHealth() const;

public:
	virtual void Initialize(UTViewModelSubsystem* InVMSubsystem = nullptr);
	virtual void BeginDestroy() override;

protected:
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter = "SetPlayerStateIsActive", Getter = "IsPlayerStateActive")
	bool bPlayerStateIsActive = false;

protected:
	virtual void SubscribeToPlayerState();
	virtual void UnsubscribeFromPlayerState();

	virtual void CreateViewModels();
	virtual void DestroyViewModels();

	virtual void RegisterViewModels();
	virtual void UnregisterViewModels();

protected:

	UFUNCTION()
	virtual void OnPlayerStateLocallyControlled(bool bInLocallyControlled);

	virtual bool IsPlayerStateReady() const;

private:
	UFUNCTION()
	void OnHealthChange(float InHealth);

	UFUNCTION()
	void OnMaxHealthChange(float InMaxHealth);

	UFUNCTION()
	void OnPlayerStateEndPlay();

protected:
	FName ContextName = "CGVMPlayerBase";

	UPROPERTY()
	UTViewModelSubsystem* VMSubsystem = nullptr;

	UPROPERTY()
	ATPlayerStateBase* PlayerState = nullptr;

	UPROPERTY()
	UTVMProgressBarBase* VMHealth = nullptr;
};
