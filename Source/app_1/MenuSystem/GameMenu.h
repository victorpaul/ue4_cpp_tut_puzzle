// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MenuHelper.h"
#include "Components/Button.h"

#include "GameMenu.generated.h"

/**
 * 
 */
UCLASS()
class APP_1_API UGameMenu : public UMenuHelper
{
    GENERATED_BODY()

protected:

    virtual bool Initialize() override;


private:

    UPROPERTY(meta=(BindWidget))
    UButton* Cancel;

    UPROPERTY(meta=(BindWidget))
    UButton* Quit;

public:

    UFUNCTION()
    void HideMenu();

    UFUNCTION()
    void QuitGame();
};
