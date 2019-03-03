// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TimeEnhancements.h"

#define LOCTEXT_NAMESPACE "FTimeEnhancementsModule"

void FTimeEnhancementsModule::StartupModule()
{

  UE_LOG(TimeEnhancementsLog, Log, TEXT("Loading TimeEnhancements Module"));
}

void FTimeEnhancementsModule::ShutdownModule()
{
  UE_LOG(TimeEnhancementsLog, Log, TEXT("Unloading TimeEnhancements Module"));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_PRIMARY_GAME_MODULE(FTimeEnhancementsModule, TimeEnhancements, "TimeEnhancements")