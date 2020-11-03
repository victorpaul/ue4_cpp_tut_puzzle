// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
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
    void ToggleGameMEnu();
    UFUNCTION(Exec)
    void Host() override;
    UFUNCTION(Exec)
    void Join(const FString& Address) override;
    UFUNCTION(Exec)
    void LoadMainMenu() override;
    UFUNCTION(Exec)
    void QuitGame() override;

private:

    UPROPERTY()
    TSubclassOf<class UMainMenu> MenuClass;
    TSubclassOf<class UGameMenu> GameMenuClass;
    class UMainMenu* Menu;
};
