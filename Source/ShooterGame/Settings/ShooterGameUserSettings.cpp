// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterGameUserSettings.h"

#include "Performance/MaxTickRateHandlerModule.h"
#include "Performance/LatencyMarkerModule.h"

UShooterGameUserSettings::UShooterGameUserSettings()
{
	SetToDefaults();
}

void UShooterGameUserSettings::SetToDefaults()
{
	Super::SetToDefaults();

	GraphicsQuality = 1;	
	bIsLanMatch = true;
	bIsDedicatedServer = false;
	bIsForceSystemResolution = false;
}

void UShooterGameUserSettings::ApplySettings(bool bCheckForCommandLineOverrides)
{
	if (GraphicsQuality == 0)
	{
		ScalabilityQuality.SetFromSingleQualityLevel(1);
	}
	else
	{
		ScalabilityQuality.SetFromSingleQualityLevel(3);
	}

	Super::ApplySettings(bCheckForCommandLineOverrides);
}