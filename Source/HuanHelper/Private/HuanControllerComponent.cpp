// Copyright 2023 Lê Vương Gia Huân

// HuanHelper
#include "HuanControllerComponent.h"
#include "HuanHelperSetting.h"

// engine
#include "GameFramework/PlayerController.h"

// UMG
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

// EnhancedInput
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"

// set in begin play
TWeakObjectPtr<UHuanControllerComponent> UHuanControllerComponent::HuanControllerComponent{ nullptr };

void UHuanControllerComponent::TogglePause() noexcept
{
	checkSlow(!PlayerController.IsNull())
	{
		const auto&& bNotPaused{ !PlayerController->IsPaused() };

		// toggle pause
		PlayerController->SetPause(bNotPaused);

		// toggle pause menu
		if (bNotPaused)
		{
			static decltype(auto) PauseMenuClass{ GetMutableDefault<UHuanHelperSetting>()->PauseMenuClass };

			if (ensure(!PauseMenuClass.IsNull()))
			{
				PauseMenu = CreateWidget<UUserWidget>(PlayerController, PauseMenuClass.LoadSynchronous());
				PauseMenu->AddToViewport();

				UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController, PauseMenu.Get());
			}
		}
		else
		{
			if (ensure(PauseMenu.IsValid()))
			{
				PauseMenu->RemoveFromParent(); PauseMenu.Reset();

				UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
			}
		}

		PlayerController->SetShowMouseCursor(bNotPaused);
	}
}

// handle input
void UHuanControllerComponent::BeginPlay()
{
	Super::BeginPlay();

	HuanControllerComponent = this;

	static decltype(auto) InputMapping{ GetMutableDefault<UHuanHelperSetting>()->DefaultInputMapping };

	// add mapping to player controller
	if (ensure(!InputMapping.IsNull()))
	{
		PlayerController = Cast<APlayerController>(GetOwner());

		PlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()
			->AddMappingContext(InputMapping.LoadSynchronous(), 0);

		static decltype(auto) PauseAction{ GetMutableDefault<UHuanHelperSetting>()->PauseAction };

		// start binding action(s)
		if (ensure(!PauseAction.IsNull()))
		{
			auto&& EnhancedInput{ NewObject<UEnhancedInputComponent>() };

			EnhancedInput->BindAction(PauseAction.LoadSynchronous(),
				ETriggerEvent::Started, this, &UHuanControllerComponent::TogglePause);

			PlayerController->PushInputComponent(MoveTemp(EnhancedInput));

			// pause on play
			TogglePause();
		}
	}
}

UHuanControllerComponent* UHuanControllerComponent::GetHuanControllerComponent() noexcept
{
	checkSlow(HuanControllerComponent.IsValid()) return HuanControllerComponent.Get();
}