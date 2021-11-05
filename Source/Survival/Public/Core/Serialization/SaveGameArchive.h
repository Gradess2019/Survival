// Copyright Gradess. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"


struct SURVIVAL_API FSaveGameArchive : public FObjectAndNameAsStringProxyArchive
{
	FSaveGameArchive(FArchive& InInnerArchive, bool bInLoadIfFindFails = true)
		: FObjectAndNameAsStringProxyArchive(InInnerArchive, bInLoadIfFindFails)
	{
		ArIsSaveGame = true;
		ArNoDelta = true;
		// Optional, useful when saving/loading variables without resetting the level.
		// Serialize variables even if weren't modified and mantain their default values.
	}

	virtual FArchive& operator<<(UObject*& Object) override;
};