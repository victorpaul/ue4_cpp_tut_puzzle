// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
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
    void Setup();
    void TearDown();

protected:
    virtual bool Initialize();

private:

    UPROPERTY(meta=(BindWidget))
    class UButton* Host;
    UPROPERTY(meta=(BindWidget))
    class UButton* Join;
    UPROPERTY(meta=(BindWidget))
    class UButton* JoinMenu;
    UPROPERTY(meta=(BindWidget))
    class UButton* CancelJoinMenu;
    UPROPERTY(meta=(BindWidget))
    class UWidgetSwitcher* MenusSwitcher;
    UPROPERTY(meta=(BindWidget))
    class UEditableTextBox* IPAddress;

    UPROPERTY(meta=(BindWidget))
    class UWidget* MainMenu;
    UPROPERTY(meta=(BindWidget))
    class UWidget* JoinGameMenu;
    
    UFUNCTION()
    void OnclickHost();
    UFUNCTION()
    void OnclickJoin();
    UFUNCTION()
    void OnclickJoinMenu();
    UFUNCTION()
    void OnclickBackToMainMenu();
    UFUNCTION()
    void SwitchMenu(UWidget* widget);
    
    IMenuInterface* MenuInterface;
};
