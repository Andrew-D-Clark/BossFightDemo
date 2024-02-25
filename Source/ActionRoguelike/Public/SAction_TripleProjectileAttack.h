// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAction.h"
#include "SAction_TripleProjectileAttack.generated.h"

class UAnimMontage;
class UParticleSystem;
class USoundBase;

/**
 *
 */
UCLASS()
class ACTIONROGUELIKE_API USAction_TripleProjectileAttack : public USAction
{
	GENERATED_BODY()

protected:

	/* Sphere radius of the sweep to find desired target under crosshair. Adjusts final projectile direction */
	UPROPERTY(EditAnywhere, Category = "Targeting")
		float SweepRadius;

	/* Fallback distance when sweep finds no collision under crosshair. Adjusts final projectile direction */
	UPROPERTY(EditAnywhere, Category = "Targeting")
		float SweepDistanceFallback;

	UPROPERTY(EditAnywhere, Category = "Attack")
		TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
		FName HandSocketName;

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

	UPROPERTY(EditAnywhere, Category = "Attack")
		int ProjectileCountMax;
	UPROPERTY(EditAnywhere, Category = "Attack")
		int ProjectileCountMin;
	UPROPERTY(EditAnywhere, Category = "Attack")
		int OffsetModifierMax;
	UPROPERTY(EditAnywhere, Category = "Attack")
		int OffsetIncrementMax;
	UPROPERTY(EditAnywhere, Category = "Attack")
		int OffsetModifierMin;
	UPROPERTY(EditAnywhere, Category = "Attack")
		int OffsetIncrementMin;
		


public:

	virtual void StartAction_Implementation(AActor* Instigator) override;

	USAction_TripleProjectileAttack();
};

