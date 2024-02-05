// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/VM/TVMProgressBarBase.h"

void UTVMProgressBarBase::SetValue(float InValue)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(Value, InValue))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetPercent);
	}
}

float UTVMProgressBarBase::GetValue() const
{
	return Value;
}

void UTVMProgressBarBase::SetMaxValue(float InMaxValue)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(MaxValue, InMaxValue))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetPercent);
	}
}

float UTVMProgressBarBase::GetMaxValue() const
{
	return MaxValue;
}

float UTVMProgressBarBase::GetPercent() const
{
	return MaxValue == 0 ? 0.0f : Value / MaxValue;
}
