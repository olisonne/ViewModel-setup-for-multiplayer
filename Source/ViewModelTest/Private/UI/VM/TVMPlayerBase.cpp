// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/VM/TVMPlayerBase.h"

#include "TPlayerStateBase.h"
#include "Subsystem/TViewModelSubsystem.h"
#include "Types/MVVMViewModelCollection.h"
#include "UI/VM/TVMProgressBarBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogCGVMPlayerBase, All, All);

void UTVMPlayerBase::SetPlayerStateIsActive(bool bInActive)
{
	UE_MVVM_SET_PROPERTY_VALUE(bPlayerStateIsActive, bInActive);
}

bool UTVMPlayerBase::IsPlayerStateActive() const
{
	return bPlayerStateIsActive;
}

void UTVMPlayerBase::SetContextName(const FName& InContextName)
{
	UnregisterViewModels();

	ContextName = InContextName;

	RegisterViewModels();
}

FName UTVMPlayerBase::GetContextName() const
{
	return ContextName;
}

void UTVMPlayerBase::SetPlayerState(ATPlayerStateBase* InPlayerState)
{
	if (InPlayerState == PlayerState)
	{
		return;
	}

	UnsubscribeFromPlayerState();

	PlayerState = InPlayerState;

	SubscribeToPlayerState();
}

ATPlayerStateBase* UTVMPlayerBase::GetPlayerState() const
{
	return PlayerState;
}

UTVMProgressBarBase* UTVMPlayerBase::GetVMHealth() const
{
	return VMHealth;
}

void UTVMPlayerBase::Initialize(UTViewModelSubsystem* InVMSubsystem)
{
	VMSubsystem = IsValid(InVMSubsystem) ? InVMSubsystem : UTViewModelSubsystem::GetViewModelSubsystem();

	CreateViewModels();
}

void UTVMPlayerBase::BeginDestroy()
{
	UnsubscribeFromPlayerState();
	UnregisterViewModels();
	DestroyViewModels();
	Super::BeginDestroy();
}

void UTVMPlayerBase::SubscribeToPlayerState()
{
	if (!IsValid(PlayerState))
	{
		return;
	}

	OnHealthChange(PlayerState->GetHealth());
	PlayerState->OnHealthChangedDelegate.AddDynamic(this, &ThisClass::OnHealthChange);

	OnMaxHealthChange(PlayerState->GetMaxHealth());
	PlayerState->OnMaxHealthChangedDelegate.AddDynamic(this, &ThisClass::OnMaxHealthChange);
	PlayerState->OnEndPlayDelegate.AddDynamic(this, &ThisClass::OnPlayerStateEndPlay);
	PlayerState->OnIsLocallyControlledDelegate.AddDynamic(this, &ThisClass::OnPlayerStateLocallyControlled);

	SetPlayerStateIsActive(IsPlayerStateReady());
}

void UTVMPlayerBase::UnsubscribeFromPlayerState()
{
	if (!IsValid(PlayerState))
	{
		return;
	}

	PlayerState->OnHealthChangedDelegate.RemoveAll(this);
	PlayerState->OnMaxHealthChangedDelegate.RemoveAll(this);
	PlayerState->OnEndPlayDelegate.RemoveAll(this);
	PlayerState->OnIsLocallyControlledDelegate.RemoveAll(this);

	PlayerState = nullptr;
	SetPlayerStateIsActive(IsPlayerStateReady());
}

void UTVMPlayerBase::CreateViewModels()
{
	VMHealth = NewObject<UTVMProgressBarBase>(this);
}

void UTVMPlayerBase::DestroyViewModels()
{
	// Maybe we need destroy VMs manually?
}

void UTVMPlayerBase::RegisterViewModels()
{
	if (ContextName.IsNone())
	{
		return;
	}

	if (!IsValid(VMSubsystem))
	{
		return;
	}

	UMVVMViewModelCollectionObject* VMCollection = VMSubsystem->GetViewModelCollection();

	if (!IsValid(VMCollection))
	{
		return;
	}

	// Register this
	{
		FMVVMViewModelContext Context;
		Context.ContextClass = GetClass();
		Context.ContextName = ContextName;
		VMCollection->AddViewModelInstance(Context, this);
	}

	if (IsValid(VMHealth))
	{
		FMVVMViewModelContext Context;
		Context.ContextClass = VMHealth->GetClass();
		Context.ContextName = FName(ContextName.ToString() + FName("Health").ToString());
		VMCollection->AddViewModelInstance(Context, VMHealth);
	}
}

void UTVMPlayerBase::UnregisterViewModels()
{
	if (!IsValid(VMSubsystem))
	{
		return;
	}

	UMVVMViewModelCollectionObject* VMCollection = VMSubsystem->GetViewModelCollection();

	if (!IsValid(VMCollection))
	{
		return;
	}

	// Remove this
	{
		FMVVMViewModelContext Context;
		Context.ContextClass = GetClass();
		Context.ContextName = ContextName;
		VMCollection->RemoveViewModel(Context);
	}

	// Remove VMHealth
	{
		FMVVMViewModelContext Context;
		Context.ContextClass = VMHealth->GetClass();
		Context.ContextName = FName(ContextName.ToString() + FName("Health").ToString());
		VMCollection->RemoveViewModel(Context);
	}
}

void UTVMPlayerBase::OnPlayerStateLocallyControlled(bool bInLocallyControlled)
{
	// In general, there is no action required. Override as needed
}

bool UTVMPlayerBase::IsPlayerStateReady() const
{
	return IsValid(PlayerState);
}

void UTVMPlayerBase::OnHealthChange(float InHealth)
{
	if (!IsValid(VMHealth))
	{
		return;
	}

	VMHealth->SetValue(InHealth);
}

void UTVMPlayerBase::OnMaxHealthChange(float InMaxHealth)
{
	if (!IsValid(VMHealth))
	{
		return;
	}

	VMHealth->SetMaxValue(InMaxHealth);
}

void UTVMPlayerBase::OnPlayerStateEndPlay()
{
	SetPlayerState(nullptr);
}


