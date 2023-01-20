// Fill out your copyright notice in the Description page of Project Settings.


#include "SActionEffect_Slow.h"
#include "SAttributeComponent.h"
#include "SActionComponent.h"
#include "SGameplayFunctionLibrary.h"
#include <GameFramework\CharacterMovementComponent.h>



USActionEffect_Slow::USActionEffect_Slow()
{
	Duration = 0.0f;
	Period = 0.0f;
}



void USActionEffect_Slow::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	
}


void USActionEffect_Slow::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);

	
}

