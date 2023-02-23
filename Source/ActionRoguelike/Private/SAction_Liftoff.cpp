// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction_Liftoff.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "GameFramework/Character.h"
#include "SActionComponent.h"
#include "SActionEffect.h"

USAction_Liftoff::USAction_Liftoff()
{
	WingSocketName1 = "wing_main_r";
	WingSocketName2 = "wing_main_l";
	AttackAnimDelay = 0.2f;
}

void USAction_Liftoff::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	
	USActionComponent* ActionComponent = Cast<USActionComponent>(Instigator->GetComponentByClass(USActionComponent::StaticClass()));
	if (ActionComp && CoolDownActionClass)
	{
		ActionComponent->AddAction(Instigator, CoolDownActionClass);
	}

	ACharacter* Character = Cast<ACharacter>(Instigator);
	if (Character)
	{
		Character->PlayAnimMontage(AttackAnim);

		UGameplayStatics::SpawnEmitterAttached(CastingEffect, Character->GetMesh(), WingSocketName1, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget);
		UGameplayStatics::SpawnEmitterAttached(CastingEffect, Character->GetMesh(), WingSocketName2, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget);

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

	void USAction_Liftoff::AttackDelay_Elapsed(ACharacter * InstigatorCharacter)
{
		
	StopAction(InstigatorCharacter);
}




