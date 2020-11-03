// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "Components/Button.h"

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
    UE_LOG(LogTemp, Warning, TEXT("Constructor of main menu"));
}

bool UMainMenu::Initialize()
{
    bool init = Super::Initialize();
    if (!init) return false;
    UE_LOG(LogTemp, Warning, TEXT("Initialize main menu"));

    if (!ensure(Host!=nullptr)) return false;
    if (!ensure(JoinMenu!=nullptr)) return false;
    if (!ensure(CancelJoinMenu!=nullptr)) return false;
    if (!ensure(Join!=nullptr)) return false;
    if (!ensure(QuitGame!=nullptr)) return false;
    
    UE_LOG(LogTemp, Warning, TEXT("Lets bind buttons"));

    // Main Menu
    Host->OnClicked.AddDynamic(this, &UMainMenu::OnclickHost);
    JoinMenu->OnClicked.AddDynamic(this, &UMainMenu::OnClickJoinMenu);

    // Join a Game
    CancelJoinMenu->OnClicked.AddDynamic(this, &UMainMenu::OnClickBackToMainMenu);
    Join->OnClicked.AddDynamic(this, &UMainMenu::OnClickJoin);

    //Quit game
    QuitGame->OnClicked.AddDynamic(this, &UMainMenu::OnClickQuitGame);

    UE_LOG(LogTemp, Warning, TEXT("Buttons Host and Join are binded"));

    return true;
}

void UMainMenu::OnclickHost()
{
    UE_LOG(LogTemp, Warning, TEXT("Lets' host game"));

    if (MenuInterface != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Call interface Host"));
        MenuInterface->Host();
    }
}

void UMainMenu::SwitchMenu(UWidget* widget)
{
    UE_LOG(LogTemp, Warning, TEXT("UMainMenu::SwitchMenu()"));

    if (!ensure(widget != nullptr)) return;
    if (!ensure(MenusSwitcher != nullptr)) return;

    MenusSwitcher->SetActiveWidget(widget);
}

void UMainMenu::OnClickBackToMainMenu()
{
    UE_LOG(LogTemp, Warning, TEXT("UMainMenu::OnclickBackToMainMenu()"));
    SwitchMenu(MainMenu);
}

void UMainMenu::OnClickJoinMenu()
{
    UE_LOG(LogTemp, Warning, TEXT("UMainMenu::OnclickJoinMenu()"));
    SwitchMenu(JoinGameMenu);
}

void UMainMenu::OnClickJoin()
{
    UE_LOG(LogTemp, Warning, TEXT("UMainMenu::OnclickJoin()"));

    if (MenuInterface != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Call interface Join"));

        MenuInterface->Join(IPAddress->GetText().ToString());
    }
}

void UMainMenu::OnClickQuitGame()
{
    if (MenuInterface != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Call interface Join"));

        MenuInterface->QuitGame();
    }
}
