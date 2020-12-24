// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

#include "PuzzlePlatformsGameInstance.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);
    UE_LOG(LogTemp, Warning, TEXT("ALobbyGameMode::PostLogin()"));

    JoinedPlayersCount++;
    UE_LOG(LogTemp, Warning, TEXT("Joinedplayers= %d, total players=%d"), JoinedPlayersCount, GetNumPlayers());

    if (JoinedPlayersCount == 2)
    {
        GetWorldTimerManager().SetTimer(InOutHandle, this, &ALobbyGameMode::StartGame, 5.0f, false, -1.0f);
    }
}

void ALobbyGameMode::StartGame()
{
    UE_LOG(LogTemp, Warning, TEXT("ALobbyGameMode::StartSession()"));

    auto GameInstance = Cast<UPuzzlePlatformsGameInstance>(GetGameInstance());
    if (!ensure(GameInstance!=nullptr)) return;

    UWorld* World = GetWorld();
    if (!ensure(World!=nullptr)) return;

    GameInstance->StartSession();
    bUseSeamlessTravel = true;
    World->ServerTravel("/Game/PuzzlePlatform/Maps/MAP_Game");
}

void ALobbyGameMode::Logout(AController* Exiting)
{
    Super::Logout(Exiting);
    UE_LOG(LogTemp, Warning, TEXT("ALobbyGameMode::Logout()"));

    JoinedPlayersCount--;
    UE_LOG(LogTemp, Warning, TEXT("Joinedplayers= %d, total players=%d"), JoinedPlayersCount, GetNumPlayers());
}
