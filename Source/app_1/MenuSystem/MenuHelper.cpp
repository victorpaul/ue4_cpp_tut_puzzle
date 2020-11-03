// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuHelper.h"

void UMenuHelper::SetMenuInterface(IMenuInterface* Interface)
{
    MenuInterface = Interface;
}

void UMenuHelper::Setup()
{
    UE_LOG(LogTemp, Warning, TEXT("UMenuHelper::Setup()"));

    AddToViewport();
    SetInputUI();
}

void UMenuHelper::TearDown()
{
    UE_LOG(LogTemp, Warning, TEXT("UMenuHelper::TearDown()"));

    SetInputGame();
    RemoveFromViewport();
}

void UMenuHelper::SetInputUI()
{
    UE_LOG(LogTemp, Warning, TEXT("UMenuHelper::Setup()"));
    UWorld* world = GetWorld();
    if (!ensure(world!=nullptr)) return;
    
    APlayerController* PlayerController = world->GetFirstPlayerController();
    if (!ensure(PlayerController!=nullptr)) return;

    FInputModeUIOnly InputMode;
    InputMode.SetWidgetToFocus(this->TakeWidget());
    InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    PlayerController->SetInputMode(InputMode);
    PlayerController->bShowMouseCursor = true;
}

void UMenuHelper::SetInputGame()
{
    UWorld* world = GetWorld();
    if (!ensure(world!=nullptr)) return;

    APlayerController* PlayerController = world->GetFirstPlayerController();
    if (!ensure(PlayerController!=nullptr)) return;

    FInputModeGameOnly InputMode;
    PlayerController->SetInputMode(InputMode);
    PlayerController->bShowMouseCursor = false;
}
