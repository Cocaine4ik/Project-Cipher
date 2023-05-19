// Copyright Epic Games, Inc. All Rights Reserved.

#include "PCGameModeBase.h"
#include "Player/PCBaseCharacter.h"
#include "UObject/ConstructorHelpers.h"

APCGameModeBase::APCGameModeBase()
{
    DefaultPawnClass = APCBaseCharacter::StaticClass();
}