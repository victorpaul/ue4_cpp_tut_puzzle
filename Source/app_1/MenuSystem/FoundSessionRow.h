// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MainMenu.h"
#include "Components/Button.h"

#include "FoundSessionRow.generated.h"

/**
 * 
 */
UCLASS()
class APP_1_API UFoundSessionRow : public UUserWidget
{
    GENERATED_BODY()

protected:

    virtual bool Initialize() override;

public:

    UPROPERTY(meta=(BindWidget))
    UButton* RowButton;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* ServerName;

    void Setup(class UMainMenu* menu, uint32 index);

private:
    UFUNCTION()
    void OnClicked();

    UPROPERTY()
    class UMainMenu* Menu;
    uint32 Index;
};
