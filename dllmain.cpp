#include <Includes.h>
#include <fstream>
#include <ostream>
#include <string>

// this is maybe the worst cheat I've ever made

bool DllMain( void* hModule, int  ul_reason_for_call, void* lpReserved )
{
    if ( ul_reason_for_call == DLL_PROCESS_ATTACH )
    {
        FortniteClientWin64Shipping = reinterpret_cast< uintptr_t >( GetModuleHandleA( 0 ) );

        SDK::MathLibrary = SDK::UObject::FindObject<SDK::UKismetMathLibrary*>( L"Engine.Default__KismetMathLibrary" );
        SDK::GameplayStatics = SDK::UObject::FindObject<SDK::UGameplayStatics*>( L"Engine.Default__GameplayStatics" );
        SDK::FortLibrary = SDK::UObject::FindObject<SDK::UFortKismetLibrary*>( L"FortniteGame.Default__FortKismetLibrary" );
        SDK::SystemLibrary = SDK::UObject::FindObject<SDK::UKismetSystemLibrary*>( L"Engine.Default__KismetSystemLibrary" );
        SDK::StringLibrary = SDK::UObject::FindObject<SDK::UKismetStringLibrary*>( L"Engine.Default__KismetStringLibrary" );

        Implementation::Font = SDK::UObject::FindObject<SDK::UFont*>( L"Engine/EngineFonts/Roboto.Roboto" , reinterpret_cast< SDK::UObject* >( -1 ) );
        Implementation::Player = SDK::UObject::FindObject<SDK::UObject*>( L"FortniteGame.FortPlayerPawnAthena" );
        Implementation::Weapon = SDK::UObject::FindObject<SDK::UObject*>( L"FortniteGame.FortWeaponRanged" );
        Implementation::SupplyDrop = SDK::UObject::FindObject<SDK::UObject*>( L"FortniteGame.FortAthenaSupplyDrop" );
        Implementation::Pickup = SDK::UObject::FindObject<SDK::UObject*>( L"FortniteGame.FortPickup" );
        Implementation::Container = SDK::UObject::FindObject<SDK::UObject*>( L"FortniteGame.BuildingContainer" );
        Implementation::Weakspot = SDK::UObject::FindObject<SDK::UObject*>( L"FortniteGame.BuildingWeakSpot" );
        Implementation::Vehicle = SDK::UObject::FindObject<SDK::UObject*>( L"FortniteGame.FortAthenaVehicle" );
        Implementation::Building = SDK::UObject::FindObject<SDK::UObject*>( L"FortniteGame.BuildingTrap" );
        Implementation::Pickaxe = SDK::UObject::FindObject<SDK::UObject*>( L"FortniteGame.FortWeaponPickaxeAthena" );
        Implementation::Projectile = SDK::UObject::FindObject<SDK::UObject*>( L"FortniteGame.FortProjectileBase" );

        Implementation::Material = SDK::UObject::FindObject<SDK::UObject*>( L"Engine.Material" );
        Implementation::LeftShift = SDK::FKey{ SDK::FName{ SDK::StringLibrary->Conv_StringToName( L"LeftShift" ) }, 0 };
        Implementation::F8 = SDK::FKey{ SDK::FName{ SDK::StringLibrary->Conv_StringToName( L"F8" ) }, 0 };
        Implementation::RightMouseButton = SDK::FKey{ SDK::FName{ SDK::StringLibrary->Conv_StringToName( L"RightMouseButton" ) }, 0 };
        Implementation::LeftMouseButton = SDK::FKey{ SDK::FName{ SDK::StringLibrary->Conv_StringToName( L"LeftMouseButton" ) }, 0 };
        Implementation::Insert = SDK::FKey{ SDK::FName{ SDK::StringLibrary->Conv_StringToName( L"Insert" ) }, 0 };

        SDK::UWorld* World = SDK::UObject::FindObject<SDK::UWorld*>( L"Frontend" , reinterpret_cast< SDK::UObject* >( -1 ) );

        SDK::UGameInstance* OwningGameInstance = World->OwningGameInstance( );
        SDK::ULocalPlayer* LocalPlayer = OwningGameInstance->LocalPlayers( )[ 0 ];
        SDK::UGameViewportClient* ViewportClient = LocalPlayer->ViewportClient( );

        ViewportClientHook.Hook( ViewportClient , 114 , DrawTransition , &DrawTransitionOriginal );
    }

    return true;
}