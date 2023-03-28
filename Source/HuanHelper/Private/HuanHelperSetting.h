// Copyright 2023 Lê Vương Gia Huân

#pragma once

// DeveloperSetting
#include "Engine/DeveloperSettings.h"

//
#include "HuanHelperSetting.generated.h"

UCLASS(config = HuanHelper, DefaultConfig)
class HUANHELPER_API UHuanHelperSetting : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	// set category in project settings
	UHuanHelperSetting(const FObjectInitializer& ObjectInitializer);

	// input mapping used for HuanControllerComponent
	UPROPERTY(category = HuanHelper, config, EditAnywhere, meta = (ConfigRestartRequired = true))
		const TSoftObjectPtr<const class UInputMappingContext> DefaultInputMapping;

	// input action for pausing
	UPROPERTY(category = HuanHelper, config, EditAnywhere, meta = (ConfigRestartRequired = true))
		const TSoftObjectPtr<const class UInputAction> PauseAction;

	UPROPERTY(category = HuanHelper, config, EditAnywhere, meta = (ConfigRestartRequired = true))
		const TSoftClassPtr<UUserWidget> PauseMenuClass;
};