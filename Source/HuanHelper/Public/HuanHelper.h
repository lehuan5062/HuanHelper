// Copyright 2023 Lê Vương Gia Huân

#pragma once

// core
#include "Modules/ModuleManager.h"
#include "Math/UnrealMathUtility.h"

class FHuanHelperModule : public IModuleInterface
{
public:
	template<typename E> static constexpr decltype(auto) RandomEnumerator() noexcept
	{
		checkSlow(std::is_enum_v<E>) return static_cast<E>(FMath::RandHelper(static_cast<int32>(E::max)));
	}
};