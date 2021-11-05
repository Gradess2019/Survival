// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class FSurvivalGameModule: public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	virtual bool IsGameModule() const override
	{
		return true;
	}

private:
	#if WITH_GAMEPLAY_DEBUGGER
	static const FName GridDebuggerCategoryName;
	#endif
};
