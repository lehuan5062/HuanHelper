// Copyright 2023 Lê Vương Gia Huân

#pragma once

// engine
#include "Components/ActorComponent.h"

//
#include "AddReceiverComponent.generated.h"

// owning actor will receive modular component(s)
UCLASS(meta = (BlueprintSpawnableComponent))
class HUANHELPER_API UAddReceiverComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// owning actor will receive modular component(s)
	virtual void BeginPlay() override;

	// remove component(s) receiver from owning actor
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	// can make this actor receive modular component(s)
	TWeakObjectPtr<class UGameFrameworkComponentManager> ComponentManager;
};