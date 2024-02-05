// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/TGameState.h"

#include "Subsystem/TViewModelSubsystem.h"

void ATGameState::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	RegisterInViewModel();
}

void ATGameState::RegisterInViewModel()
{
	UTViewModelSubsystem* ViewModelSubsystem = UTViewModelSubsystem::GetViewModelSubsystem();

	if (!IsValid(ViewModelSubsystem))
	{
		return;
	}

	ViewModelSubsystem->RegisterGameState(this);
}
