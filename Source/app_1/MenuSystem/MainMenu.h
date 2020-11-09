// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MenuHelper.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"

#include "MainMenu.generated.h"

USTRUCT()
struct FServerData
{
    GENERATED_BODY()

    FString ServerName;
    FString HostUsername;
    uint16 PlayersCount;
    uint16 MaxPlayers;
    uint32 Ping;
};
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

    // UPROPERTY(meta=(BindWidget))
    // class UButton* JoinByIp;

    UPROPERTY(meta=(BindWidget))
    class UButton* Join;

    UPROPERTY(meta=(BindWidget))
    class UButton* JoinMenu;

    UPROPERTY(meta=(BindWidget))
    class UButton* CancelJoinMenu;

    UPROPERTY(meta=(BindWidget))
    class UWidgetSwitcher* MenusSwitcher;

    // UPROPERTY(meta=(BindWidget))
    // class UEditableTextBox* IPAddress;

    UPROPERTY(meta=(BindWidget))
    class UWidget* MainMenu;

    UPROPERTY(meta=(BindWidget))
    class UWidget* JoinGameMenu;

    UPROPERTY(meta=(BindWidget))
    class UButton* QuitGame;

    UPROPERTY(meta=(BindWidget))
    class UScrollBox* ScrollBoxSessions;

    UPROPERTY(meta=(BindWidget))
    class UButton* Refresh;

    UPROPERTY()
    TSubclassOf<class UFoundSessionRow> FoundSessionRowClass;

    UFUNCTION()
    void OnclickHost();

    // UFUNCTION()
    // void OnClickJoinByIp();

    UFUNCTION()
    void OnClickJoinBySession();

    UFUNCTION()
    void OnClickRefreshSessions();
    
    UFUNCTION()
    void OnClickJoinMenu();

    UFUNCTION()
    void OnClickBackToMainMenu();

    UFUNCTION()
    void SwitchMenu(UWidget* widget);

    UFUNCTION()
    void OnClickQuitGame();

    TOptional<uint32> SelectedSessionRowIndex;

    UPROPERTY(meta=(BindWidget))
    class UWidget* HostGameMenu;
    UPROPERTY(meta=(BindWidget))
    class UButton* CancelHost;
    UPROPERTY(meta=(BindWidget))
    class UButton* CreateHost;
    UPROPERTY(meta=(BindWidget))
    class UEditableTextBox* GameName;
    UFUNCTION()
    void OnClickCancelHost();
    UFUNCTION()
    void OnClickCreateHost();
    
public:
    void SetServersList(TArray<FServerData> ServerNames);
    void SelectIndex(uint32 SessionIndex);
};
