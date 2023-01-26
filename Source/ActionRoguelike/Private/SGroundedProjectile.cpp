// Fill out your copyright notice in the Description page of Project Settings.


#include "SGroundedProjectile.h"
#include "Engine.h"
#include "DrawDebugHelpers.h"

//void ASProjectileBase::Tick(float DeltaTime)
//{
//    Super::Tick(DeltaTime);
//
//    FHitResult Hit;
//    FVector StartTrace = GetActorLocation();
//    FVector EndTrace = GetActorLocation() - FVector(0, 0, 100); // slightly below the current location
//    FCollisionQueryParams CollisionParams;
//    CollisionParams.AddIgnoredActor(this);
//
//    // Draw a debug line to visualize the line trace
//    DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red, false, 0.0f, 0, 2.0f);
//
//
//    // Check if a hit occurred
//    if (GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, ECC_Visibility, CollisionParams))
//    {
//        // Update the projectile's location to be at the same height as the hit point
//        FVector NewLocation = FVector(GetActorLocation().X, GetActorLocation().Y, Hit.ImpactPoint.Z);
//        SetActorLocation(NewLocation);
//    }
//}