// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SActionEffect.h"
#include "SActionEffect_Slow.generated.h"

/**
 *
 */
UCLASS()
class ACTIONROGUELIKE_API USActionEffect_Slow : public USActionEffect
{
	GENERATED_BODY()

protected:

	
public:

	void StartAction_Implementation(AActor* Instigator) override;

	void StopAction_Implementation(AActor* Instigator) override;

	USActionEffect_Slow();
};
