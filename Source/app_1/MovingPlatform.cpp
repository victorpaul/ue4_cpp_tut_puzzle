// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
    PrimaryActorTick.bCanEverTick = true;
    SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {
        SetReplicates(true);
        SetReplicateMovement(true);
    }

    GlobalStartLocation = GetActorLocation();
    GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (HasAuthority())
    {
        FVector Location = GetActorLocation();
        float JorneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
        float JorneyTraveled = (Location - GlobalStartLocation).Size();

        if (JorneyTraveled >= JorneyLength)
        {
            FVector swap = GlobalStartLocation;
            GlobalStartLocation = GlobalTargetLocation;
            GlobalTargetLocation = swap;
        }

        FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
        Location += Speed * DeltaTime * Direction;
        SetActorLocation(Location);
    }
}
