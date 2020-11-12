// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "MenuSystem/MenuInterface.h"
#include "MenuSystem/MainMenu.h"
#include "PuzzlePlatformsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class APP_1_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
    GENERATED_BODY()

public:

    UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectIn);

    virtual void Init() override;
    UFUNCTION(Exec, BlueprintCallable)
    void LoadMenu();
    UFUNCTION(Exec, BlueprintCallable)
    void LoadGameMenu();
    UFUNCTION(Exec)
    void Host(const FString& ServerName) override;
    UFUNCTION(Exec)
    void JoinByGameAddress(const FString& Address) override;
    UFUNCTION(Exec)
    void Join(uint32 SessionIndex) override;
    UFUNCTION(Exec)
    void LoadMainMenu() override;
    UFUNCTION(Exec)
    void QuitGame() override;

    void RefreshSessions() override;

private:

    UPROPERTY()
    TSubclassOf<class UMainMenu> MenuClass;
    UPROPERTY()
    TSubclassOf<class UGameMenu> GameMenuClass;
    class UMainMenu* Menu;

    IOnlineSessionPtr Session;
    TSharedPtr<FOnlineSessionSearch> SessionSearch;
    
    void OnHostSessionDestroyed(FName SessionName, bool Success);
    void OnHostSessionCreated(FName SessionName, bool success);
    void OnFindSessionsCompleteDelegates(bool Found);
    void OnJoinSessionCompleteDelegates(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
    void CreateSession(const FString& ServerName);

};
