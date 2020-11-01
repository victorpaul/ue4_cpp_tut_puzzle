// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "app_1/PuzzlePlatformsGameInstance.h"
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

    UE_LOG(LogTemp, Warning, TEXT("Lets bind buttons"));

    // Main Menu
    Host->OnClicked.AddDynamic(this, &UMainMenu::OnclickHost);
    JoinMenu->OnClicked.AddDynamic(this, &UMainMenu::OnclickJoinMenu);

    // Join a Game
    CancelJoinMenu->OnClicked.AddDynamic(this, &UMainMenu::OnclickBackToMainMenu);
    Join->OnClicked.AddDynamic(this, &UMainMenu::OnclickJoin);

    UE_LOG(LogTemp, Warning, TEXT("Buttons Host and Join are binded"));

    return true;
}

void UMainMenu::Setup()
{
    UE_LOG(LogTemp, Warning, TEXT("UMainMenu::Setup()"));
    UWorld* world = GetWorld();
    if (!ensure(world!=nullptr)) return;

    APlayerController* PlayerController = world->GetFirstPlayerController();
    if (!ensure(PlayerController!=nullptr)) return;

    this->AddToViewport();
    FInputModeUIOnly InputMode;
    InputMode.SetWidgetToFocus(this->TakeWidget());
    InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    PlayerController->SetInputMode(InputMode);
    PlayerController->bShowMouseCursor = true;
}

void UMainMenu::TearDown()
{
    UE_LOG(LogTemp, Warning, TEXT("UMainMenu::TearDown()"));

    UWorld* world = GetWorld();
    if (!ensure(world!=nullptr)) return;

    APlayerController* PlayerController = world->GetFirstPlayerController();
    if (!ensure(PlayerController!=nullptr)) return;

    FInputModeGameOnly InputMode;
    PlayerController->SetInputMode(InputMode);
    PlayerController->bShowMouseCursor = false;

    this->RemoveFromViewport();
}

void UMainMenu::SetMenuInterface(IMenuInterface* Interface)
{
    this->MenuInterface = Interface;
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

void UMainMenu::OnclickBackToMainMenu()
{
    UE_LOG(LogTemp, Warning, TEXT("UMainMenu::OnclickBackToMainMenu()"));
    SwitchMenu(MainMenu);
}

void UMainMenu::OnclickJoinMenu()
{
    UE_LOG(LogTemp, Warning, TEXT("UMainMenu::OnclickJoinMenu()"));
    SwitchMenu(JoinGameMenu);
}

void UMainMenu::OnclickJoin()
{
    UE_LOG(LogTemp, Warning, TEXT("UMainMenu::OnclickJoin()"));

    if (MenuInterface != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Call interface Join"));

        MenuInterface->Join(IPAddress->GetText().ToString());
    }
}
