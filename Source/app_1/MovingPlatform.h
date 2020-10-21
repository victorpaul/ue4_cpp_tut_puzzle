// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 *
 */
UCLASS()
class APP_1_API AMovingPlatform : public AStaticMeshActor
{
    GENERATED_BODY()

public:
    AMovingPlatform();

    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnyWhere)
    float Speed = 20;

    UPROPERTY(EditAnyWhere, Meta = (MakeEditWidget=true))
    FVector TargetLocation;

    void AddActiveTrigger();
    void RemoveActiveTrigger();

private:

    FVector GlobalTargetLocation;
    FVector GlobalStartLocation;

    UPROPERTY(EditAnywhere)
    int ActiveTriggers = 1;
};
