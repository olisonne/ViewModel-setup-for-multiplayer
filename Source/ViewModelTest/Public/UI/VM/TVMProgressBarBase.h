// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "TVMProgressBarBase.generated.h"

/**
 * 
 */
UCLASS()
class VIEWMODELTEST_API UTVMProgressBarBase : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	void SetValue(float InValue);
	float GetValue() const;

	void SetMaxValue(float InMaxValue);
	float GetMaxValue() const;

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetPercent() const;

protected:
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float Value = 75.0f;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float MaxValue = 100.f;
};
