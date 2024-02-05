// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/VM/TVMLocalPlayer.h"

#include "Subsystem/TViewModelSubsystem.h"

void UTVMLocalPlayer::SubscribeToPlayerState()
{
	Super::SubscribeToPlayerState();
}

void UTVMLocalPlayer::UnsubscribeFromPlayerState()
{
	Super::UnsubscribeFromPlayerState();
}

void UTVMLocalPlayer::CreateViewModels()
{
	Super::CreateViewModels();
}

void UTVMLocalPlayer::RegisterViewModels()
{
	Super::RegisterViewModels();
}

void UTVMLocalPlayer::UnregisterViewModels()
{
	Super::UnregisterViewModels();
}

void UTVMLocalPlayer::OnPlayerStateLocallyControlled(bool bInLocallyControlled)
{
	// We dont need call Super here

	if (bInLocallyControlled)
	{
		return;
	}

	if (!IsValid(VMSubsystem))
	{
		return;
	}

	SetPlayerState(nullptr);
}
