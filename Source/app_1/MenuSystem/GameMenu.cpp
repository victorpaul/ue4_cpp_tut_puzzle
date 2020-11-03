// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMenu.h"
#include "Components/Button.h"

bool UGameMenu::Initialize()
{
    if (!Super::Initialize()) return false;

    if (!ensure(Cancel!=nullptr)) return false;
    if (!ensure(Quit!=nullptr)) return false;

    Cancel->OnClicked.AddDynamic(this, &UGameMenu::HideMenu);
    Quit->OnClicked.AddDynamic(this, &UGameMenu::QuitGame);

    return true;
}

void UGameMenu::HideMenu()
{
    UE_LOG(LogTemp, Warning, TEXT("UGameMenu::HideMenu"));
    TearDown();
}

void UGameMenu::QuitGame()
{
    TearDown();
    UE_LOG(LogTemp, Warning, TEXT("UGameMenu::QuitGame"));
    if (MenuInterface != nullptr)
    {
        MenuInterface->LoadMainMenu();
    }
}
