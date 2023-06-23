// Project Cipher. All Rights Reserved.

#pragma once

#include "PCDelegates.h"
#include "Delegates/DelegateCombinations.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractSignature, bool);

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnValueChangedSignature, float, float)
