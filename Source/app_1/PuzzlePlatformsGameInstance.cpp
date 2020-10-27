// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectIn)
{
    UE_LOG(LogTemp, Warning, TEXT("Puzzle game instance constructor"));
}

void UPuzzlePlatformsGameInstance::Init()
{
    UE_LOG(LogTemp, Warning, TEXT("Puzzle game instance initialization"));
}

void UPuzzlePlatformsGameInstance::Host()
{
    UEngine* Engine = GetEngine();
    UWorld* World = GetWorld();
    if (ensure(Engine==nullptr)) return;
    if (ensure(World==nullptr)) return;

    Engine->AddOnScreenDebugMessage(0, 2, FColor::Green,TEXT("Hosting"));
    World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
    UEngine* Engine = GetEngine();
    APlayerController* PlayerController = GetFirstLocalPlayerController();

    if (ensure(Engine==nullptr)) return;
    if (ensure(PlayerController==nullptr)) return;
    
    Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining: %s"), *Address));
    PlayerController->ClientTravel(Address,TRAVEL_Absolute);
}
