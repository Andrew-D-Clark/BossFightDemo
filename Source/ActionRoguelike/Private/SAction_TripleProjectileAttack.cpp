// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction_TripleProjectileAttack.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "GameFramework/Character.h"





USAction_TripleProjectileAttack::USAction_TripleProjectileAttack()
{
	HandSocketName = "Muzzle_01";
	AttackAnimDelay = 0.2f;

	SweepRadius = 20.0f;
	SweepDistanceFallback = 5000;
}


void USAction_TripleProjectileAttack::StartAction_Implementation(AActor* Instigator)
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


void USAction_TripleProjectileAttack::AttackDelay_Elapsed(ACharacter* InstigatorCharacter)
{
	if (ensureAlways(ProjectileClass))
	{
		FVector HandLocation = InstigatorCharacter->GetMesh()->GetSocketLocation(HandSocketName);

		HandLocation.Z += 100.0f;

		// We trace against the environment first to find whats under the player crosshair.
		// We use the hit location to adjust the projectile launch direction so it will hit what is under the crosshair rather than shoot straight forward from the player hands.

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = InstigatorCharacter;

		FCollisionShape Shape;
		Shape.SetSphere(SweepRadius);

		// Ignore Player
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(InstigatorCharacter);

		FVector TraceDirection = InstigatorCharacter->GetControlRotation().Vector();

		// Add sweep radius onto start to avoid the sphere clipping into floor/walls the camera is directly against.
		FVector TraceStart = InstigatorCharacter->GetPawnViewLocation() + (TraceDirection * SweepRadius);
		// endpoint far into the look-at distance (not too far, still adjust somewhat towards crosshair on a miss)
		FVector TraceEnd = TraceStart + (TraceDirection * SweepDistanceFallback);

		FHitResult Hit;
		// returns true if we got to a blocking hit (Channel1="Projectile" defined in DefaultGame.ini)
		if (GetWorld()->SweepSingleByChannel(Hit, TraceStart, TraceEnd, FQuat::Identity, ECC_GameTraceChannel1, Shape, Params))
		{
			// Overwrite trace end with impact point in world
			TraceEnd = Hit.ImpactPoint;
		}

		// find new direction/rotation from Hand pointing to impact point in world.
		FRotator ProjRotation = (TraceEnd - HandLocation).Rotation();
		const FRotator BaseRotation = (TraceEnd - HandLocation).Rotation();

		// Generate random values for ProjectileCount and OffsetModifier
		int ProjectileCount = FMath::RandRange(ProjectileCountMin, ProjectileCountMax);
		int OffsetIncrement = FMath::RandRange(OffsetIncrementMin, OffsetIncrementMax);
		int OffsetModifier = FMath::RandRange(OffsetModifierMin, OffsetModifierMax);

		for (int ProjectileCountIndex = 0; ProjectileCountIndex <= ProjectileCount; ProjectileCountIndex++)
		{
			int Offset = 0;
			if (ProjectileCountIndex % 2 == 0) {
				Offset = ProjectileCountIndex / 2 * OffsetModifier * OffsetIncrement;
			}
			else {
				Offset = -1 * (ProjectileCountIndex / 2 * OffsetModifier * OffsetIncrement);
			}

			ProjRotation = FRotator(0, BaseRotation.Yaw + Offset, 0);
			FTransform SpawnTM = FTransform(ProjRotation, HandLocation);
			GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
		}
	}

	StopAction(InstigatorCharacter);
}

//void USAction_TripleProjectileAttack::AttackDelay_Elapsed(ACharacter* InstigatorCharacter)
//{
//	if (ensureAlways(ProjectileClass))
//	{
//		FVector HandLocation = InstigatorCharacter->GetMesh()->GetSocketLocation(HandSocketName);
//
//		HandLocation.Z += 100.0f;
//
//		// We trace against the environment first to find whats under the player crosshair.
//		// We use the hit location to adjust the projectile launch direction so it will hit what is under the crosshair rather than shoot straight forward from the player hands.
//
//		FActorSpawnParameters SpawnParams;
//		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//		SpawnParams.Instigator = InstigatorCharacter;
//
//		FCollisionShape Shape;
//		Shape.SetSphere(SweepRadius);
//
//		// Ignore Player
//		FCollisionQueryParams Params;
//		Params.AddIgnoredActor(InstigatorCharacter);
//
//		FVector TraceDirection = InstigatorCharacter->GetControlRotation().Vector();
//
//		// Add sweep radius onto start to avoid the sphere clipping into floor/walls the camera is directly against.
//		FVector TraceStart = InstigatorCharacter->GetPawnViewLocation() + (TraceDirection * SweepRadius);
//		// endpoint far into the look-at distance (not too far, still adjust somewhat towards crosshair on a miss)
//		FVector TraceEnd = TraceStart + (TraceDirection * SweepDistanceFallback);
//
//		FHitResult Hit;
//		// returns true if we got to a blocking hit (Channel1="Projectile" defined in DefaultGame.ini)
//		if (GetWorld()->SweepSingleByChannel(Hit, TraceStart, TraceEnd, FQuat::Identity, ECC_GameTraceChannel1, Shape, Params))
//		{
//			// Overwrite trace end with impact point in world
//			TraceEnd = Hit.ImpactPoint;
//		}
//
		
//		}
//
//		StopAction(InstigatorCharacter);
//	}