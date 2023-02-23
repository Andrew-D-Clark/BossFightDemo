// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAction.h"
#include "SAction_Liftoff.generated.h"

class UAnimMontage;
class UParticleSystem;
class USoundBase;
class USActionEffect;

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API USAction_Liftoff : public USAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<USActionEffect> CoolDownActionClass;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
		FName WingSocketName1;
	UPROPERTY(VisibleAnywhere, Category = "Effects")
		FName WingSocketName2;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
		float AttackAnimDelay;

	UPROPERTY(EditAnywhere, Category = "Attack")
		UAnimMontage* AttackAnim;

	/* Particle System played during attack animation */
	UPROPERTY(EditAnywhere, Category = "Attack")
		UParticleSystem* CastingEffect;

	/* Sound Effect to play (Can be Wave or Cue) */
	UPROPERTY(EditAnywhere, Category = "Attack")
		USoundBase* CastingSound;

	UFUNCTION()
		void AttackDelay_Elapsed(ACharacter* InstigatorCharacter);

public:

	virtual void StartAction_Implementation(AActor* Instigator) override;

	USAction_Liftoff();
};
	