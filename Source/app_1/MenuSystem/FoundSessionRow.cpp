// Fill out your copyright notice in the Description page of Project Settings.


#include "FoundSessionRow.h"

bool UFoundSessionRow::Initialize()
{
    UE_LOG(LogTemp, Warning, TEXT("UFoundSessionRow::Initialize()"));

    if (!Super::Initialize())
    {
        return false;
    }


    return true;
}

void UFoundSessionRow::Setup(class UMainMenu* Menu_, uint32 Index_)
{
    UE_LOG(LogTemp, Warning, TEXT("UFoundSessionRow::Setup"));
    if (!ensure(RowButton!= nullptr)) return;

    RowButton->OnClicked.AddDynamic(this, &UFoundSessionRow::OnClicked);
    this->Menu = Menu_;
    this->Index = Index_;
}

void UFoundSessionRow::OnClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("UFoundSessionRow::Setup"));
    Menu->SelectIndex(Index);
}
