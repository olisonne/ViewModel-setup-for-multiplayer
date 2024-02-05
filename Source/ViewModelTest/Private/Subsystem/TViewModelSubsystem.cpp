

// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/TViewModelSubsystem.h"

#include "Game/TGameInstance.h"
#include "MVVMGameSubsystem.h"
#include "UI/VM/TVMPlayers.h"

//DEFINE_LOG_CATEGORY_STATIC(LogCGViewModelSubsystem, All, All);

UTViewModelSubsystem* UTViewModelSubsystem::Self = nullptr;

UTViewModelSubsystem::UTViewModelSubsystem()
{
	Self = this;
}

UTViewModelSubsystem* UTViewModelSubsystem::GetViewModelSubsystem()
{
//#if WITH_EDITOR
//	UTGameInstance* GameInstance = UTGameInstance::GetGameInstance();
//
//	if (IsValid(GameInstance))
//	{
//		return UTGameInstance::GetGameInstance()->GetSubsystem<UTViewModelSubsystem>();
//	}
//#endif

	return Self;
}

void UTViewModelSubsystem::RegisterGameState(ATGameState* InGameState)
{
	if (InGameState == GameState)
	{
		return;
	}

	UnsubscribeFromGameStateDelegates();

	GameState = InGameState;

	SubscribeToGameStateDelegates();

	// ToDo: Register GameState for ViewModels if needed
}

void UTViewModelSubsystem::RegisterPlayerState(ATPlayerStateBase* InPlayerState)
{
	if (!IsValid(VMPlayers))
	{
		return;
	}

	VMPlayers->RegisterPlayerState(InPlayerState);
}

void UTViewModelSubsystem::UnregisterPlayerState(ATPlayerStateBase* InPlayerState)
{
	if(!IsValid(VMPlayers))
	{
		return;
	}

	VMPlayers->UnregisterPlayerState(InPlayerState);
}

UTVMPlayers* UTViewModelSubsystem::GetVMPlayers() const
{
	return VMPlayers;
}

UMVVMViewModelCollectionObject* UTViewModelSubsystem::GetViewModelCollection() const
{
	if (!IsValid(MVVMSubsystem))
	{
		return nullptr;
	}

	return MVVMSubsystem->GetViewModelCollection();
}

void UTViewModelSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UTGameInstance* GameInstance = UTGameInstance::GetGameInstance();

	if (!IsValid(GameInstance))
	{
		return;
	}

	MVVMSubsystem = GameInstance->GetSubsystem<UMVVMGameSubsystem>();

	CreateViewModels();
}

void UTViewModelSubsystem::Deinitialize()
{
	ClearViewModels();

	Self = nullptr;

	Super::Deinitialize();
}

void UTViewModelSubsystem::CreateViewModels()
{
	VMPlayers = NewObject<UTVMPlayers>(this);

	if (IsValid(VMPlayers))
	{
		VMPlayers->Initialize(this);
	}
}

void UTViewModelSubsystem::ClearViewModels()
{

}

void UTViewModelSubsystem::SubscribeToGameStateDelegates()
{
	// ToDo: Subscribe to GameState delegates
}

void UTViewModelSubsystem::UnsubscribeFromGameStateDelegates()
{
	// ToDo: Unsubscribe from GameState delegates
}






