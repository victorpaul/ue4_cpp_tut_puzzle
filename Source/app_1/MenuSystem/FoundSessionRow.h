// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

#include "FoundSessionRow.generated.h"

/**
 * 
 */
UCLASS()
class APP_1_API UFoundSessionRow : public UUserWidget
{
    GENERATED_BODY()

public:

    UPROPERTY(meta=(BindWidget))
    UTextBlock* ServerName;
};
