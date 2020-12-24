// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "app_1GameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class APP_1_API ALobbyGameMode : public Aapp_1GameMode
{
    GENERATED_BODY()

public:

    // virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage);

    virtual void PostLogin(APlayerController* NewPlayer) override;
    virtual void Logout(AController* Exiting) override;
    virtual void StartGame();

private:

    uint16 JoinedPlayersCount;
    FTimerHandle InOutHandle;
};
