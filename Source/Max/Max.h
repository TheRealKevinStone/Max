// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#ifndef __MAX_H__
#define __Max_H__

#include "Engine.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMax, Log, All);

#define COLLISION_DAMAGEABLE        ECC_GameTraceChannel2
#define COLLISION_TARGETABLE		ECC_GameTraceChannel3

#endif

//USTRUCT(BlueprintType)
//struct FDebugVariable
//{
//	GENERATED_USTRUCT_BODY()
//
//		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug Variable")
//		FName Name;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug Variable")
//		FString Value;
//
//	void SetName(const FName NewValue)
//	{
//		Name = NewValue;
//	}
//
//	void SetValue(const FString NewValue)
//	{
//		Value = NewValue;
//	}
//
//	FDebugVariable()
//	{
//		Name = "None";
//		Value = "None";
//	}
//};