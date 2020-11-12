// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "Components/Button.h"
#include "FoundSessionRow.h"

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
    UE_LOG(LogTemp, Warning, TEXT("Constructor of main menu"));

    static ConstructorHelpers::FClassFinder<UUserWidget> FoundSessionRowBPWClass(
        TEXT("/Game/MenuSystem/WBP_FoundSessionRow"));
    if (!ensure(FoundSessionRowBPWClass.Class!=nullptr)) return;
    FoundSessionRowClass = FoundSessionRowBPWClass.Class;
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
    // if (!ensure(JoinByIp!=nullptr)) return false;
    if (!ensure(Refresh!=nullptr)) return false;

    UE_LOG(LogTemp, Warning, TEXT("Lets bind buttons"));

    // Main Menu
    Host->OnClicked.AddDynamic(this, &UMainMenu::OnclickHost);
    JoinMenu->OnClicked.AddDynamic(this, &UMainMenu::OnClickJoinMenu);

    // Join a Game
    CancelJoinMenu->OnClicked.AddDynamic(this, &UMainMenu::OnClickBackToMainMenu);
    // JoinByIp->OnClicked.AddDynamic(this, &UMainMenu::OnClickJoinByIp);
    Join->OnClicked.AddDynamic(this, &UMainMenu::OnClickJoinBySession);
    Refresh->OnClicked.AddDynamic(this, &UMainMenu::OnClickRefreshSessions);

    // Create a game
    CancelHost->OnClicked.AddDynamic(this, &UMainMenu::OnClickCancelHost);
    CreateHost->OnClicked.AddDynamic(this, &UMainMenu::OnClickCreateHost);

    //Quit game
    QuitGame->OnClicked.AddDynamic(this, &UMainMenu::OnClickQuitGame);

    UE_LOG(LogTemp, Warning, TEXT("Buttons binded"));

    return true;
}

void UMainMenu::OnclickHost()
{
    UE_LOG(LogTemp, Warning, TEXT("Lets' host game"));

    SwitchMenu(HostGameMenu);
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

void UMainMenu::OnClickCancelHost()
{
    UE_LOG(LogTemp, Warning, TEXT("UMainMenu::OnClickCancelHost()"));
    SwitchMenu(MainMenu);
}

void UMainMenu::OnClickJoinMenu()
{
    UE_LOG(LogTemp, Warning, TEXT("UMainMenu::OnclickJoinMenu()"));
    SwitchMenu(JoinGameMenu);

    if (!ensure(MenuInterface!=nullptr)) return;

    MenuInterface->RefreshSessions();
    // SetServersList({"Test1", "Test2"});
}

// void UMainMenu::OnClickJoinByIp()
// {
//     UE_LOG(LogTemp, Warning, TEXT("UMainMenu::OnclickJoin()"));
//
//     if (MenuInterface != nullptr)
//     {
//         UE_LOG(LogTemp, Warning, TEXT("Call interface Join"));
//
//         MenuInterface->JoinByGameAddress(IPAddress->GetText().ToString());
//     }
// }

void UMainMenu::SetServersList(TArray<FServerData> ServerNames)
{
    UE_LOG(LogTemp, Warning, TEXT("UMainMenu::SetServersList()"));

    if (ScrollBoxSessions != nullptr)
    {
        ScrollBoxSessions->ClearChildren();
        uint32 index = 0;
        for (const FServerData& ServerData : ServerNames)
        {
            class UFoundSessionRow* Row = CreateWidget<UFoundSessionRow>(this, FoundSessionRowClass);
            Row->ServerName->SetText(FText::FromString(ServerData.ServerName));
            Row->HostUsername->SetText(FText::FromString(ServerData.HostUsername));
            Row->Players->SetText(
                FText::FromString(
                    FString::Printf(TEXT("%d/%d"), ServerData.PlayersCount, ServerData.MaxPlayers)));
            Row->Ping->SetText(FText::FromString(FString::Printf(TEXT("%d"), ServerData.Ping)));
            Row->ServerName->SetText(FText::FromString(ServerData.ServerName));

            Row->Setup(this, index);
            ++index;
            ScrollBoxSessions->AddChild(Row);
        }
    }
}

void UMainMenu::SelectIndex(uint32 SessionIndex)
{
    UE_LOG(LogTemp, Warning, TEXT("UMainMenu::SelectIndex(%d)"), SessionIndex);

    if (SelectedSessionRowIndex.IsSet())
    {
        UFoundSessionRow* Previous = Cast<UFoundSessionRow>(
            ScrollBoxSessions->GetChildAt(SelectedSessionRowIndex.GetValue()));
        if (Previous != nullptr)
        {
            Previous->IsSelectedRow = false;
        }
    }

    UFoundSessionRow* ToSelect = Cast<UFoundSessionRow>(ScrollBoxSessions->GetChildAt(SessionIndex));
    if (ToSelect != nullptr)
    {
        ToSelect->IsSelectedRow = true;
    }

    SelectedSessionRowIndex = SessionIndex;
}

void UMainMenu::OnClickJoinBySession()
{
    UE_LOG(LogTemp, Warning, TEXT("UMainMenu::OnClickJoinBySession()"));
    if (SelectedSessionRowIndex.IsSet() && MenuInterface != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("SelectedSessionRowIndex=%d"), SelectedSessionRowIndex.GetValue());
        MenuInterface->Join(SelectedSessionRowIndex.GetValue());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("SelectedSessionRowIndex is not set"));
    }
}

void UMainMenu::OnClickRefreshSessions()
{
    UE_LOG(LogTemp, Warning, TEXT("UMainMenu::OnClickRefreshSessions()"));

    if (MenuInterface != nullptr)
    {
        MenuInterface->RefreshSessions();
    }
}

void UMainMenu::OnClickQuitGame()
{
    UE_LOG(LogTemp, Warning, TEXT("UMainMenu::OnClickQuitGame()"));

    if (MenuInterface != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Call interface Join"));

        MenuInterface->QuitGame();
    }
}

void UMainMenu::OnClickCreateHost()
{
    UE_LOG(LogTemp, Warning, TEXT("UMainMenu::OnClickCreateHost()"));
    if (MenuInterface != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Call interface Host"));
        
        MenuInterface->Host(GetServerName());
    }
}

FString UMainMenu::GetServerName()
{
    return GameName->GetText().ToString();
}
