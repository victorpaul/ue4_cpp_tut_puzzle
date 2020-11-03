// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MenuInterface.h"
#include "Blueprint/UserWidget.h"
#include "MenuHelper.generated.h"

/**
 * 
 */
UCLASS()
class APP_1_API UMenuHelper : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetMenuInterface(IMenuInterface* Interface);
    void Setup();
    void TearDown();

protected:

    void SetInputUI();
    void SetInputGame();

    IMenuInterface* MenuInterface;
};
