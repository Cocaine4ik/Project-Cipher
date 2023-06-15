// Copyright Epic Games, Inc. All Rights Reserved.

#include "PCGameModeBase.h"

#include "PCCipherCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "PCCipherCharacter.h"
#include "PCGameHUD.h"
#include "PCPlayerController.h"

APCGameModeBase::APCGameModeBase()
{
    DefaultPawnClass = APCCipherCharacter::StaticClass();
    PlayerControllerClass = APCPlayerController::StaticClass();
    HUDClass = APCGameHUD::StaticClass();
}