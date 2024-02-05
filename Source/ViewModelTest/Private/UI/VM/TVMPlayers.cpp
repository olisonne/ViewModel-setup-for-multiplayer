// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/VM/TVMPlayers.h"

#include "TPlayerStateBase.h"
#include "Subsystem/TViewModelSubsystem.h"
#include "Types/MVVMViewModelCollection.h"
#include "UI/VM/TVMLocalPlayer.h"

DEFINE_LOG_CATEGORY_STATIC(LogCGVMPlayers, All, All);


UTVMLocalPlayer* UTVMPlayers::GetVMLocalPlayer() const
{
	return VMLocalPlayer;
}

void UTVMPlayers::RegisterPlayerState(ATPlayerStateBase* InPlayerState)
{
	AController* Controller = InPlayerState->GetOwningController();

	if (!IsValid(Controller) || !Controller->IsLocalPlayerController())
	{
		return;
	}

	RegisterLocalPlayerState(InPlayerState);
}

void UTVMPlayers::UnregisterPlayerState(ATPlayerStateBase* InPlayerState)
{
	UnregisterLocalPlayerState(InPlayerState);
}

void UTVMPlayers::Initialize(UTViewModelSubsystem* InVMSubsystem)
{
	if (bInitialized)
	{
		return;
	}

	bInitialized = true;

	VMSubsystem = IsValid(InVMSubsystem) ? InVMSubsystem : UTViewModelSubsystem::GetViewModelSubsystem();

	CreateViewModels();
	RegisterViewModels();
}


void UTVMPlayers::BeginDestroy()
{
	UnregisterViewModels();
	DestroyViewModels();
	Super::BeginDestroy();
}

void UTVMPlayers::CreateViewModels()
{
	VMLocalPlayer = NewObject<UTVMLocalPlayer>(this);

	if (ensure(IsValid(VMLocalPlayer)))
	{
		VMLocalPlayer->Initialize(VMSubsystem);
	}
}

void UTVMPlayers::DestroyViewModels()
{
	// Maybe we need destroy VMs manually?
}

void UTVMPlayers::RegisterViewModels()
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

	// Register this
	{
		FMVVMViewModelContext Context;
		Context.ContextClass = GetClass();
		Context.ContextName = FName("VMPlayers");
		VMCollection->AddViewModelInstance(Context, this);
	}

	if (IsValid(VMLocalPlayer))
	{
		VMLocalPlayer->SetContextName(FName("VMLocalPlayer"));
	}
}

void UTVMPlayers::UnregisterViewModels()
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
		Context.ContextName = FName("VMPlayers");
		VMCollection->RemoveViewModel(Context);
	}

	if (IsValid(VMLocalPlayer))
	{
		VMLocalPlayer->SetContextName(FName(NAME_None));
	}
}

void UTVMPlayers::RegisterLocalPlayerState(ATPlayerStateBase* InPlayerState)
{
	if (!IsValid(VMLocalPlayer))
	{
		return;
	}

	VMLocalPlayer->SetPlayerState(InPlayerState);
}

void UTVMPlayers::UnregisterLocalPlayerState(ATPlayerStateBase* InPlayerState)
{
	if (!IsValid(VMLocalPlayer))
	{
		return;
	}

	if (VMLocalPlayer->GetPlayerState() != InPlayerState)
	{
		return;
	}

	VMLocalPlayer->SetPlayerState(nullptr);
}

