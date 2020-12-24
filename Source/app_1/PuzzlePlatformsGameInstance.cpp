// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "MenuSystem/MainMenu.h"
#include "MenuSystem/GameMenu.h"

const static FName SESSION_NAME = NAME_GameSession;
const static FName SERVER_NAME_KEY = TEXT("ServerName");
const static uint16 MAX_PLAYERS = 4;

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectIn)
{
    static ConstructorHelpers::FClassFinder<UUserWidget> MainManuBPWClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
    if (!ensure(MainManuBPWClass.Succeeded())) return;
    MenuClass = MainManuBPWClass.Class;
    UE_LOG(LogTemp, Warning, TEXT("Found class %s in constructor"), *MenuClass->GetName());

    static ConstructorHelpers::FClassFinder<UUserWidget> GameManuBPWClass(TEXT("/Game/MenuSystem/WBP_InGameMenu"));
    if (!ensure(GameManuBPWClass.Succeeded())) return;
    GameMenuClass = GameManuBPWClass.Class;
    UE_LOG(LogTemp, Warning, TEXT("Found class %s in constructor"), *GameMenuClass->GetName());
}

void UPuzzlePlatformsGameInstance::Init()
{
    UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance::Init"));

    IOnlineSubsystem* SubSystem = IOnlineSubsystem::Get();
    if (SubSystem != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Got online subsystem: %s"), *SubSystem->GetSubsystemName().ToString());
        Session = SubSystem->GetSessionInterface();
        Session->OnDestroySessionCompleteDelegates.AddUObject(
            this, &UPuzzlePlatformsGameInstance::OnHostSessionDestroyed);
        Session->OnCreateSessionCompleteDelegates.AddUObject(
            this, &UPuzzlePlatformsGameInstance::OnHostSessionCreated);
        Session->OnFindSessionsCompleteDelegates.AddUObject(
            this, &UPuzzlePlatformsGameInstance::OnFindSessionsCompleteDelegates);
        Session->OnJoinSessionCompleteDelegates.AddUObject(
            this, &UPuzzlePlatformsGameInstance::OnJoinSessionCompleteDelegates);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Got no subsystem"));
    }
}

void UPuzzlePlatformsGameInstance::RefreshSessions()
{
    UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance::RefreshSessions()"));

    SessionSearch = MakeShareable(new FOnlineSessionSearch());
    if (SessionSearch.IsValid())
    {
        SessionSearch->MaxSearchResults = 100;
        SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
        UE_LOG(LogTemp, Warning, TEXT("Let's search some sessions"));
        Session->FindSessions(0, SessionSearch.ToSharedRef());
    }
}

void UPuzzlePlatformsGameInstance::OnFindSessionsCompleteDelegates(bool Found)
{
    UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance::OnFindSessionsCompleteDelegates(%d)"), Found);

    if (Found && SessionSearch.IsValid())
    {
        TArray<FServerData> serverNames;
        for (auto& FoundSession : SessionSearch->SearchResults)
        {
            if (FoundSession.IsValid())
            {
                UE_LOG(LogTemp, Warning, TEXT("Found session: %s"), *FoundSession.GetSessionIdStr());
                FServerData Data;
                Data.ServerName = FoundSession.GetSessionIdStr();
                Data.HostUsername = FoundSession.Session.OwningUserName;
                Data.MaxPlayers = FoundSession.Session.SessionSettings.NumPublicConnections;
                Data.PlayersCount = Data.MaxPlayers - FoundSession.Session.NumOpenPublicConnections;
                Data.Ping = FoundSession.PingInMs;

                FString ServerName;
                if (FoundSession.Session.SessionSettings.Get(SERVER_NAME_KEY, ServerName))
                {
                    Data.ServerName = ServerName;
                }

                serverNames.Add(Data);
            }
        }
        Menu->SetServersList(serverNames);
    }
}

void UPuzzlePlatformsGameInstance::OnJoinSessionCompleteDelegates(FName SessionName,
                                                                  EOnJoinSessionCompleteResult::Type Result)
{
    UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance::OnJoinSessionCompleteDelegates(%s)"),
           *SessionName.ToString());
    if (!ensure(Session.IsValid()))return;
    if (!ensure(Result == EOnJoinSessionCompleteResult::Success))return;

    FString ConnectInfo;
    if (!Session->GetResolvedConnectString(SESSION_NAME, ConnectInfo))
    {
        UE_LOG(LogTemp, Warning, TEXT("Connect info can not be recieved"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Join by IP: %s"), *ConnectInfo);
    JoinByGameAddress(ConnectInfo);
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
    if (!ensure(MenuClass!=nullptr)) return;
    Menu = CreateWidget<UMainMenu>(this, MenuClass);
    if (!ensure(Menu!=nullptr)) return;

    Menu->SetMenuInterface(this);
    Menu->Setup();
}

void UPuzzlePlatformsGameInstance::LoadGameMenu()
{
    UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance::ToggleGameMenu()"));

    if (!ensure(GameMenuClass!=nullptr)) return;
    class UGameMenu* GameMenu = CreateWidget<UGameMenu>(this, GameMenuClass);

    GameMenu->SetMenuInterface(this);
    GameMenu->Setup();
}

void UPuzzlePlatformsGameInstance::OnHostSessionDestroyed(FName SessionName, bool Success)
{
    UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance::OnHostSessionDestroyed(%s,%d)"),
           *SessionName.ToString(), Success);
    if (Success)
    {
        CreateSession(Menu->GetServerName());
    }
}

void UPuzzlePlatformsGameInstance::Host(const FString& ServerName)
{
    UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance::Host(%s)"), *ServerName);
    if (!Session.IsValid()) return;

    auto ExistingSession = Session->GetNamedSession(SESSION_NAME);
    if (ExistingSession != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Found existing session %s"), *ExistingSession->SessionName.ToString());
        SessionSearch->bIsLanQuery = true;
        Session->DestroySession(ExistingSession->SessionName);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No existing session, let's create new one"));
        CreateSession(ServerName);
    }
}

void UPuzzlePlatformsGameInstance::CreateSession(const FString& ServerName)
{
    bool IsLan = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";
    UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance::CreateSession(), LAN=%d, Subsystem=%s"), IsLan,
           *IOnlineSubsystem::Get()->GetSubsystemName().ToString());

    if (Session.IsValid())
    {
        FOnlineSessionSettings settings;
        settings.bIsLANMatch = IsLan;
        settings.NumPublicConnections = MAX_PLAYERS;
        settings.bShouldAdvertise = true;
        settings.bUsesPresence = true;
        settings.Set(SERVER_NAME_KEY, ServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

        Session->CreateSession(0, SESSION_NAME, settings);
    }
}

void UPuzzlePlatformsGameInstance::OnHostSessionCreated(FName SessionName, bool success)
{
    UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance::OnSessionCreated(%s)"), *SessionName.ToString());
    if (success)
    {
        UE_LOG(LogTemp, Warning, TEXT("Session creted"));
        if (Menu != nullptr)
        {
            Menu->TearDown();
        }

        UEngine* Engine = GetEngine();
        if (!ensure(Engine!=nullptr)) return;
        UWorld* World = GetWorld();
        if (!ensure(World!=nullptr)) return;

        Engine->AddOnScreenDebugMessage(0, 2, FColor::Green,TEXT("Hosting"));
        World->ServerTravel("/Game/PuzzlePlatform/Maps/MAP_Lobby?listen");
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Session was not creted"));
    }
}

void UPuzzlePlatformsGameInstance::StartSession()
{
    UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance::StartSession"));
    if (Session.IsValid())
    {
        Session->StartSession(SESSION_NAME);
    }
}

void UPuzzlePlatformsGameInstance::JoinByGameAddress(const FString& Address)
{
    UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance::JoinByIp(%s)"), *Address);

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

void UPuzzlePlatformsGameInstance::Join(uint32 SessionIndex)
{
    UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance::Join(%d)"), SessionIndex);

    if (!ensure(SessionSearch.IsValid())) return;
    if (!ensure(Session.IsValid())) return;

    if (Menu != nullptr)
    {
        Menu->TearDown();
    }

    Session->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[SessionIndex]);
}

void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
    UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance::LoadMainMenu()"));

    APlayerController* PlayerController = GetFirstLocalPlayerController();

    if (!ensure(PlayerController!=nullptr)) return;

    PlayerController->ClientTravel("/Game/PuzzlePlatform/Maps/MAP_MainMenu", TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstance::QuitGame()
{
    UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance::QuitGame()"));

    APlayerController* PlayerController = GetFirstLocalPlayerController();

    if (!ensure(PlayerController!=nullptr)) return;

    PlayerController->ConsoleCommand("quit");
}
