// Copyright 2023 Lê Vương Gia Huân

// HuanHelper
#include "AddReceiverComponent.h"

// engine
#include "GameFramework/Actor.h"
#include "Engine/GameInstance.h"

// ModularGameplay
#include "Components/GameFrameworkComponentManager.h"

// owning actor will receive modular component(s)
void UAddReceiverComponent::BeginPlay()
{
	Super::BeginPlay();

	const auto&& owner{ GetOwner() };
	ComponentManager = owner->GetGameInstance()->GetSubsystem<UGameFrameworkComponentManager>();
	checkSlow(ComponentManager.IsValid()) ComponentManager->AddReceiver(owner);
}

// remove component receiver
void UAddReceiverComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason); ComponentManager->RemoveReceiver(GetOwner());
}