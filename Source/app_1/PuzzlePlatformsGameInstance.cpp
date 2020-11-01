// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MainMenu.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectIn)
{
    static ConstructorHelpers::FClassFinder<UUserWidget> MainManuBPWClass(
        TEXT("/Game/MenuSystem/WBP_MainMenu"));
    if (!ensure(MainManuBPWClass.Class!=nullptr)) return;
    MenuClass = MainManuBPWClass.Class;

    UE_LOG(LogTemp, Warning, TEXT("Found class %s in constructor"), *MenuClass->GetName());
}

void UPuzzlePlatformsGameInstance::Init()
{
    UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName());
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
    if (ensure(MenuClass==nullptr)) return;
    Menu = CreateWidget<UMainMenu>(this, MenuClass);
    if (!ensure(Menu!=nullptr)) return;

    Menu->SetMenuInterface(this);
    Menu->Setup();
}

void UPuzzlePlatformsGameInstance::Host()
{
    if (Menu != nullptr)
    {
        Menu->TearDown();
    }

    UEngine* Engine = GetEngine();
    UWorld* World = GetWorld();
    if (!ensure(Engine!=nullptr) || !ensure(World!=nullptr)) return;

    Engine->AddOnScreenDebugMessage(0, 2, FColor::Green,TEXT("Hosting"));
    World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
    UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance::Join(%s)"), *Address);

    if (Menu != nullptr)
    {
        Menu->TearDown();
    }

    UEngine* Engine = GetEngine();
    APlayerController* PlayerController = GetFirstLocalPlayerController();

    if (!ensure(Engine!=nullptr) || !ensure(PlayerController!=nullptr)) return;

    Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining: %s"), *Address));
    PlayerController->ClientTravel(Address, TRAVEL_Absolute);
}
