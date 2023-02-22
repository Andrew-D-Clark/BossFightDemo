// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectileBase.h"
#include "GameplayTagContainer.h"
#include "SGroupHealAOE.generated.h"

class USActionEffect;
/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASGroupHealAOE : public ASProjectileBase
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		TMap<AActor*, int> HitCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay")
		int MaxHits;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float numBlackholeTicks = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		float DamageAmount;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		FGameplayTag ParryTag;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		TSubclassOf<USActionEffect> BurningActionClass;

	FTimerHandle BlackholeTimerHandle;

	UFUNCTION()
		void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void PostInitializeComponents() override;

public:


	ASGroupHealAOE();
};
