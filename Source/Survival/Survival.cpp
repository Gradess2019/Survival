// Copyright Epic Games, Inc. All Rights Reserved.

#include "Survival.h"
#include "Modules/ModuleManager.h"

#if WITH_GAMEPLAY_DEBUGGER
#if CPP
#include "Debugger/DebuggerCategoryRegistrar.inl"
#endif
#include "Debugger/GridDebuggerCategory.h"
#endif

#if WITH_GAMEPLAY_DEBUGGER
const FName FSurvivalGameModule::GridDebuggerCategoryName = FName("Grid");
#endif

void FSurvivalGameModule::StartupModule()
{
	IModuleInterface::StartupModule();

#if WITH_GAMEPLAY_DEBUGGER
	FDebuggerCategoryRegistrar::RegisterCategory<FGridDebuggerCategory>(GridDebuggerCategoryName, 6);
#endif
}

void FSurvivalGameModule::ShutdownModule()
{
	IModuleInterface::ShutdownModule();

#if WITH_GAMEPLAY_DEBUGGER
	FDebuggerCategoryRegistrar::UnregisterCategory(GridDebuggerCategoryName);
#endif
}

IMPLEMENT_PRIMARY_GAME_MODULE(FSurvivalGameModule, Survival, "Survival");