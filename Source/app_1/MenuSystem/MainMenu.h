// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class APP_1_API UMainMenu : public UUserWidget
{
    GENERATED_BODY()

public:
    UMainMenu(const FObjectInitializer& ObjectInitializer);

    void SetMenuInterface(IMenuInterface* Interface);
    
protected:
    virtual bool Initialize();

private:

    UPROPERTY(meta=(BindWidget))
    class UButton* Host;
    UPROPERTY(meta=(BindWidget))
    class UButton* Join;

    UFUNCTION()
    void OnclickHost();
    UFUNCTION()
    void OnclickJoin();

    IMenuInterface* MenuInterface;
};
