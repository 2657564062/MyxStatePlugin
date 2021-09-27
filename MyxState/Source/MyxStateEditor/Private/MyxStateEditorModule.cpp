// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyxStateEditorModule.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"

#define LOCTEXT_NAMESPACE "FMyxStateEditorModule"

#define IMAGE_PLUGIN_BRUSH( RelativePath, ... ) FSlateImageBrush( RelativePathToPluginPath( RelativePath, ".png" ), __VA_ARGS__ )

void FMyxStateEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	Style = MakeShareable(new FSlateStyleSet("MyxStateEditorStyle"));
	Style->Set("ClassThumbnail.MyxState", new IMAGE_PLUGIN_BRUSH("Icons/MyxState_256x", FVector2D(64.f, 64.f)));
	Style->Set("ClassThumbnail.MyxStateMachine", new IMAGE_PLUGIN_BRUSH("Icons/MyxStateMachine_256x", FVector2D(64.f, 64.f)));
	Style->Set("ClassIcon.MyxState", new IMAGE_PLUGIN_BRUSH("Icons/MyxState_256x", FVector2D(16.f, 16.f)));
	Style->Set("ClassIcon.MyxStateMachine", new IMAGE_PLUGIN_BRUSH("Icons/MyxStateMachine_256x", FVector2D(16.f, 16.f)));

	FSlateStyleRegistry::RegisterSlateStyle(*Style);
}

void FMyxStateEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FSlateStyleRegistry::UnRegisterSlateStyle(Style->GetStyleSetName());
}

FString FMyxStateEditorModule::RelativePathToPluginPath(const FString& RelativePath, const ANSICHAR* Extension)
{
	static FString ContentDir = IPluginManager::Get().FindPlugin(TEXT("MyxState"))->GetContentDir();
	return (ContentDir / RelativePath) + Extension;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMyxStateEditorModule, MyxStateEditor)