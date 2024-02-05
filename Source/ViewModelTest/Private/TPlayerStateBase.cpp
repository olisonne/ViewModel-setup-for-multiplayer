// Fill out your copyright notice in the Description page of Project Settings.


#include "TPlayerStateBase.h"

#include "Subsystem/TViewModelSubsystem.h"

void ATPlayerStateBase::GetLifetimeReplicatedProps(class TArray<class FLifetimeProperty, class TSizedDefaultAllocator<32> >&) const
{
	
}

float ATPlayerStateBase::GetHealth() const
{
	return Health;
}

float ATPlayerStateBase::GetMaxHealth() const
{
	return MaxHealth;
}

void ATPlayerStateBase::SetHealth(float InHealth)
{
	OnHealthChangedDelegate.Broadcast(InHealth); // ToDo CG-1614: old mechanics

	OnHealthChangedDelegate.Broadcast(InHealth);

	Health = InHealth;
}

void ATPlayerStateBase::SetMaxHealth(float InMaxHealth)
{
	OnHealthChangedDelegate.Broadcast(InMaxHealth); // ToDo CG-1614: old mechanics

	OnMaxHealthChangedDelegate.Broadcast(InMaxHealth);

	MaxHealth = InMaxHealth;
}

void ATPlayerStateBase::BeginPlay()
{
	Super::BeginPlay();

	RegisterInViewModel(); // ToDo CG-1614: Maybe we should call it in other stage
}

void ATPlayerStateBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	UnregisterInViewModel(); // ToDo CG-1614: Maybe we should call it in other stage
}

void ATPlayerStateBase::RegisterInViewModel()
{
	UTViewModelSubsystem* ViewModelSubsystem = UTViewModelSubsystem::GetViewModelSubsystem();

	if (!IsValid(ViewModelSubsystem))
	{
		return;
	}

	ViewModelSubsystem->RegisterPlayerState(this);
}

void ATPlayerStateBase::UnregisterInViewModel()
{
	UTViewModelSubsystem* ViewModelSubsystem = UTViewModelSubsystem::GetViewModelSubsystem();

	if (!IsValid(ViewModelSubsystem))
	{
		return;
	}

	ViewModelSubsystem->UnregisterPlayerState(this);
}
