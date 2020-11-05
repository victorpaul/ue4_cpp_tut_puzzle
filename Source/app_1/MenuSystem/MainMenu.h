// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MenuHelper.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "FoundSessionRow.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class APP_1_API UMainMenu : public UMenuHelper
{
    GENERATED_BODY()

public:
    UMainMenu(const FObjectInitializer& ObjectInitializer);

protected:
    virtual bool Initialize();

private:

    UPROPERTY(meta=(BindWidget))
    class UButton* Host;

    UPROPERTY(meta=(BindWidget))
    class UButton* JoinByIp;

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

    UPROPERTY(meta=(BindWidget))
    class UButton* QuitGame;

    UPROPERTY(meta=(BindWidget))
    class UScrollBox* ScrollBoxSessions;

    UPROPERTY()
    TSubclassOf<class UFoundSessionRow> FoundSessionRowClass;

    UFUNCTION()
    void OnclickHost();

    UFUNCTION()
    void OnClickJoinByIp();

    UFUNCTION()
    void OnClickJoinBySession();

    UFUNCTION()
    void OnClickJoinMenu();

    UFUNCTION()
    void OnClickBackToMainMenu();

    UFUNCTION()
    void SwitchMenu(UWidget* widget);

    UFUNCTION()
    void OnClickQuitGame();

    TOptional<uint32> SelectedSessionRowIndex;

public:
    void SetServersList(TArray<FString> ServerNames);
    void SelectIndex(uint32 SessionIndex);
};
