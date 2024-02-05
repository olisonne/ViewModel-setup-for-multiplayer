// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TPlayerStateBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedDelegate, float, InValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedDelegate, float, InValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndPlayDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIsLocallyControlledDelegate, bool, InValue);

UCLASS()
class VIEWMODELTEST_API ATPlayerStateBase : public APlayerState
{
	GENERATED_BODY()

public:
	/* Common Characteristics Delegates*/
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Delegates | Common Characteristics")
	FOnHealthChangedDelegate OnHealthChangedDelegate;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Delegates | Common Characteristics")
	FOnMaxHealthChangedDelegate OnMaxHealthChangedDelegate;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Delegates | Common Specifications")
	FOnEndPlayDelegate OnEndPlayDelegate;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Delegates | Common Specifications")
	FOnIsLocallyControlledDelegate OnIsLocallyControlledDelegate;

	/* Common Characteristics */
	UFUNCTION(BlueprintPure, Category = "Common Characteristics")
	virtual float GetHealth() const;

	UFUNCTION(BlueprintPure, Category = "Common Characteristics")
	virtual float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable)
	void SetHealth(float InHealth);
	void SetMaxHealth(float InMaxHealth);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	virtual void RegisterInViewModel();
	virtual void UnregisterInViewModel();

private:
	UPROPERTY(Replicated)
	float Health = 75.f;

	UPROPERTY(Replicated)
	float MaxHealth = 100.f;
};
