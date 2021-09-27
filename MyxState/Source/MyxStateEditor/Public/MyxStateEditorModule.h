// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FSlateStyleSet;

class FMyxStateEditorModule : public IModuleInterface
{
private:
	TSharedPtr<FSlateStyleSet> Style;

	FString RelativePathToPluginPath(const FString& RelativePath, const ANSICHAR* Extension);

public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
