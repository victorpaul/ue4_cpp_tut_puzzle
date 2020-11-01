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

    if (!ensure(Host!=nullptr) || !ensure(Join!=nullptr)) return false;

    UE_LOG(LogTemp, Warning, TEXT("Lets bind buttons"));
    
    Host->OnClicked.AddDynamic(this, &UMainMenu::OnclickHost);
    Join->OnClicked.AddDynamic(this, &UMainMenu::OnclickJoin);

    UE_LOG(LogTemp, Warning, TEXT("Buttons Host and Join are binded"));

    return true;
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

void UMainMenu::OnclickJoin()
{
    UE_LOG(LogTemp, Warning, TEXT("Lets' host game"));

    if (MenuInterface != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Call interface Join"));
        MenuInterface->Join("192.168.50.235");
    }
}
