// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TViewModelSubsystem.generated.h"

class ATGameState;
class ATPlayerStateBase;
class UMVVMViewModelCollectionObject;
class UMVVMGameSubsystem;

UCLASS()
class VIEWMODELTEST_API UTViewModelSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UTViewModelSubsystem();
	static UTViewModelSubsystem* GetViewModelSubsystem();

public:
	UFUNCTION(BlueprintCallable, Category = "Viewmodel")
	void RegisterGameState(ATGameState* InGameState);

	UFUNCTION(BlueprintCallable, Category = "Viewmodel")
	void RegisterPlayerState(ATPlayerStateBase* InPlayerState);

	UFUNCTION(BlueprintCallable, Category = "Viewmodel")
	void UnregisterPlayerState(ATPlayerStateBase* InPlayerState);

public:
	UFUNCTION(BlueprintPure, Category = "Viewmodel")
	UTVMPlayers* GetVMPlayers() const;

	UFUNCTION(BlueprintPure, Category = "Viewmodel")
	UMVVMViewModelCollectionObject* GetViewModelCollection() const;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
	void CreateViewModels();
	void ClearViewModels();
	void SubscribeToGameStateDelegates();
	void UnsubscribeFromGameStateDelegates();

private:
	static UTViewModelSubsystem* Self;

	UPROPERTY();
	UMVVMGameSubsystem* MVVMSubsystem = nullptr;

	UPROPERTY()
	ATGameState* GameState = nullptr;

private:
	UPROPERTY()
	UTVMPlayers* VMPlayers = nullptr;
	
};
