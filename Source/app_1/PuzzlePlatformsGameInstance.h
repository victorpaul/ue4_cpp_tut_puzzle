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
    UFUNCTION(Exec)
    void Host();
    UFUNCTION(Exec)
    void Join(const FString& Address);

private:

    UPROPERTY()
    TSubclassOf<class UMainMenu> MenuClass;
    class UMainMenu* Menu;
};
