#pragma once

#include <iostream>
#include <Windows.h>

#include <Safety/Imports.h>

uintptr_t FortniteClientWin64Shipping = 0;

#include <Memory/NoCRT.h>
#include <Memory/Vector.h>
#include <Memory/Map.h>

#include <Safety/SKCrypter.h>
#include <Memory/Signature.h>
#include <Memory/PageTable.h>

#include <Engine/Engine.h>
#include <Engine/Classes.h>
#include <Engine/Objects.h>
#include <Memory/WalkVFT.h>

namespace Implementation
{
	SDK::UFont* Font = nullptr;
	SDK::UObject* Player = nullptr;
	SDK::UObject* Weapon = nullptr;
	SDK::UObject* SupplyDrop = nullptr;
	SDK::UObject* Pickup = nullptr;
	SDK::UObject* Container = nullptr;
	SDK::UObject* Vehicle = nullptr;	
	SDK::UObject* Projectile = nullptr;
	SDK::UObject* Weakspot = nullptr;
	SDK::UObject* Building = nullptr;
	SDK::UObject* Pickaxe = nullptr;
	SDK::UObject* Material = nullptr;

	SDK::FVector2D ScreenSize = SDK::FVector2D( );
	SDK::FVector2D ScreenCenter = SDK::FVector2D( );

	SDK::FKey Insert = SDK::FKey( );
	SDK::FKey LeftMouseButton = SDK::FKey( );
	SDK::FKey RightMouseButton = SDK::FKey( );
	SDK::FKey F8 = SDK::FKey( );
	SDK::FKey LeftShift = SDK::FKey( );

	SDK::UCanvas* Canvas = nullptr;
	SDK::APlayerController* PlayerController = nullptr;

	bool bAimbotActive = false;
	SDK::FRotator AimbotRotationTarget = SDK::FRotator( );

	bool bSilentAimActive = false;
	SDK::FVector SilentAimLocationTarget = SDK::FVector( );
}

#include <Engine/Custom.h>
#include <Memory/VTableHook.h>
static ShadowVMT ViewportClientHook;

#include <Framework/Wrapper.h>
#include <Framework/Framework.h>
#include <Framework/Radar.h>

#include <Hooks/Settings.h>
#include <Hooks/GetSearchTime.h>
#include <Hooks/GetControlRotation.h>
#include <Hooks/GetWeaponTargetingTransform.h>
#include <Hooks/Exploits.h>
#include <Safety/Humanization.h>
#include <Hooks/DrawTransition.h>