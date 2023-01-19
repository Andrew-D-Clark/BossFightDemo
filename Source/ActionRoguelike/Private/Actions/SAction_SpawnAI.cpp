// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/SAction_SpawnAI.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "GameFramework/Character.h"




USAction_SpawnAI::USAction_SpawnAI()
{
	HandSocketName = "Muzzle_01";
	AttackAnimDelay = 0.2f;

	//SweepRadius = 20.0f;
	//SweepDistanceFallback = 5000;
}


void USAction_SpawnAI::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	ACharacter* Character = Cast<ACharacter>(Instigator);
	if (Character)
	{
		Character->PlayAnimMontage(AttackAnim);

		UGameplayStatics::SpawnEmitterAttached(CastingEffect, Character->GetMesh(), HandSocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget);

		UGameplayStatics::SpawnSoundAttached(CastingSound, Character->GetMesh());

		if (Character->HasAuthority())
		{
			FTimerHandle TimerHandle_AttackDelay;
			FTimerDelegate Delegate;
			Delegate.BindUFunction(this, "AttackDelay_Elapsed", Character);

			GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay, Delegate, AttackAnimDelay, false);
		}
	}
}


void USAction_SpawnAI::AttackDelay_Elapsed(ACharacter* InstigatorCharacter)
{
	StopAction(InstigatorCharacter);
}

