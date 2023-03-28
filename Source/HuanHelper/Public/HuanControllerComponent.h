// Copyright 2023 Lê Vương Gia Huân

#pragma once

// engine
#include "Components/ActorComponent.h"

//
#include "HuanControllerComponent.generated.h"

// can't use within for blueprint's parent
UCLASS(Blueprintable)
class HUANHELPER_API UHuanControllerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// set in begin play
	UPROPERTY(BlueprintReadOnly, Category = HuanHelper) TObjectPtr<APlayerController> PlayerController;

	UFUNCTION(BlueprintPure, Category = HuanHelper) static UHuanControllerComponent* GetHuanControllerComponent() noexcept;

protected:
	UPROPERTY(BlueprintReadOnly, Category = HuanHelper) TWeakObjectPtr<class UUserWidget> PauseMenu;

	UFUNCTION(BlueprintCallable, Category = HuanHelper) void TogglePause() noexcept;

	// handle input
	virtual void BeginPlay() override;

private:
	// set in begin play
	static TWeakObjectPtr<UHuanControllerComponent> HuanControllerComponent;
};