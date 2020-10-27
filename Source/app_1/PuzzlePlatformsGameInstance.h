// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PuzzlePlatformsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class APP_1_API UPuzzlePlatformsGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:

    UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectIn);

    virtual void Init() override;

    UFUNCTION(Exec)
    void Host();
    UFUNCTION(Exec)
    void Join(const FString& Address);
};
