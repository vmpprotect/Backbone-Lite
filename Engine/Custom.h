#pragma once

namespace Custom
{
	bool K2_Project( SDK::FVector WorldLocation , SDK::FVector2D* ScreenLocation )
	{
		SDK::FVector ReturnValue = Implementation::Canvas->K2_Project( WorldLocation );

		if ( ReturnValue.Z <= 0.0 )
		{
			ReturnValue.X *= -1.0;
			ReturnValue.Y *= -1.0;

			ReturnValue.X += Implementation::ScreenSize.X;
			ReturnValue.Y += Implementation::ScreenSize.Y;
		}

		if ( ReturnValue.Z > 0.0 )
		{
			*ScreenLocation = SDK::FVector2D( ReturnValue.X , ReturnValue.Y );
		}

		return ScreenLocation;
	}

	double InterpolatedValue( double CurrentScalar , double MaxScalar , double MinValue , double MaxValue )
	{
		MaxScalar = SDK::MathLibrary->FMin( MaxScalar , CurrentScalar );

		double InterpolatedValue = MaxValue - ( MaxValue - MinValue ) * ( MaxScalar / CurrentScalar );

		InterpolatedValue = SDK::MathLibrary->Clamp( InterpolatedValue , MinValue , MaxValue );

		return InterpolatedValue;
	}

	SDK::FName GetNameFromString( SDK::FString InString )
	{
		static map<wchar_t* , SDK::FName> Names;
		auto it = Names.find( InString.c_str( ) );
		if ( it != Names.end( ) )
			return it->second;

		SDK::FName OutName = SDK::StringLibrary->Conv_StringToName( InString );
		Names.insert( InString.c_str( ) , OutName );

		return OutName;
	}

	SDK::FVector GetSocketLocation( SDK::USkeletalMeshComponent* Mesh , SDK::FString InSocketName )
	{
		SDK::FName SocketName = Custom::GetNameFromString( InSocketName );

		return Mesh->GetSocketLocation( SocketName );
	}

	bool InScreen( SDK::FVector2D ScreenLocation )
	{
		if ( ScreenLocation.X < 5.0 || ScreenLocation.X > Implementation::ScreenSize.X - ( 5.0 * 2 ) && ScreenLocation.Y < 5.0 || ScreenLocation.Y > Implementation::ScreenSize.Y - ( 5.0 * 2 ) )
			return false;
		return true;
	}

	bool InRect( double Radius , SDK::FVector2D ScreenLocation )
	{
		return Implementation::ScreenCenter.X >= ( Implementation::ScreenCenter.X - Radius ) && Implementation::ScreenCenter.X <= ( Implementation::ScreenCenter.X + Radius ) &&
			ScreenLocation.Y >= ( ScreenLocation.Y - Radius ) && ScreenLocation.Y <= ( ScreenLocation.Y + Radius );
	}

	bool InCircle( double Radius , SDK::FVector2D ScreenLocation )
	{
		if ( InRect( Radius , ScreenLocation ) )
		{
			double dx = Implementation::ScreenCenter.X - ScreenLocation.X; dx *= dx;
			double dy = Implementation::ScreenCenter.Y - ScreenLocation.Y; dy *= dy;
			return dx + dy <= Radius * Radius;
		} return false;
	}

	SDK::FLinearColor GetColorByTier( SDK::EFortRarity Tier )
	{
		switch ( Tier )
		{
		case SDK::EFortRarity::Common:
			return SDK::FLinearColor( 0.4f , 0.4f , 0.4f , 1.f );
		case SDK::EFortRarity::Uncommon:
			return SDK::FLinearColor( 0.2f , 1.f , 0.2f , 1.f );
		case SDK::EFortRarity::Rare:
			return SDK::FLinearColor( 0.2f , 0.2f , 0.9f , 1.f );
		case SDK::EFortRarity::Epic:
			return SDK::FLinearColor( 1.f , 0.2f , 1.f , 1.f );
		case SDK::EFortRarity::Legendary:
			return SDK::FLinearColor( 1.f , 1.f , 0.2f , 1.f );
		case SDK::EFortRarity::Mythic:
			return SDK::FLinearColor( 1.f , 0.84f , 0.f , 1.f );
		default:
			return SDK::FLinearColor( 0.4f , 0.4f , 0.4f , 1.f );
		}
	}

	SDK::FString GetNameByPlatform( SDK::FString Platform )
	{
		if ( Platform == SDK::FString( L"WIN" ) )
			return SDK::FString( L"Windows" );
		else if ( Platform == SDK::FString( L"XBL" ) )
			return SDK::FString( L"XBox" );
		else if ( Platform == SDK::FString( L"PSN" ) || Platform == SDK::FString( L"PS5" ) )
			return SDK::FString( L"PlayStation" );
		else if ( Platform == SDK::FString( L"SWT" ) )
			return SDK::FString( L"Nintendo Switch" );
		else if ( Platform == SDK::FString( L"AND" ) )
			return SDK::FString( L"Android" );
		else if ( Platform == SDK::FString( L"MAC" ) )
			return SDK::FString( L"MacOS" );
		else if ( Platform == SDK::FString( L"LNX" ) )
			return SDK::FString( L"Linux" );
		else if ( Platform == SDK::FString( L"IOS" ) )
			return SDK::FString( L"Apple" );
		return SDK::FString( L"" );
	}

	SDK::FLinearColor GetColorByPlatform( SDK::FString Platform )
	{
		if ( Platform == SDK::FString( L"WIN" ) )
			return SDK::FLinearColor( 1.f , 1.f , 1.f , 1.f );
		else if ( Platform == SDK::FString( L"XBL" ) )
			return SDK::FLinearColor( 0.0627f , 0.4863f , 0.0627f , 1.0f );
		if ( Platform == SDK::FString( L"PSN" ) || Platform == SDK::FString( L"PS5" ) )
			return SDK::FLinearColor( 0.f , 0.188f , 0.529f , 1.f );
		else if ( Platform == SDK::FString( L"SWT" ) )
			return SDK::FLinearColor( 0.902f , 0.0f , 0.0706f , 1.f );
		else if ( Platform == SDK::FString( L"AND" ) )
			return SDK::FLinearColor( 0.2392f , 0.8627f , 0.5176f , 1.f );
		else if ( Platform == SDK::FString( L"MAC" ) )
			return SDK::FLinearColor( 0.5569f , 0.5569f , 0.5765f , 1.f );
		else if ( Platform == SDK::FString( L"LNX" ) )
			return SDK::FLinearColor( 1.f , 0.843f , 0.f , 1.f );
		else if ( Platform == SDK::FString( L"IOS" ) )
			return SDK::FLinearColor( 0.f , 0.4784f , 1.f , 1.f );
		return SDK::FLinearColor( 1.f , 0.f , 0.f , 1.f );
	}

	SDK::FString GetRankByProgress( int32_t Rank )
	{
		switch ( Rank )
		{
		case 0:
		case 1:
		case 2:
			return SDK::FString( L"T-UI-Icon-Habenaro-Bronze" );
		case 3:
		case 4:
		case 5:
			return SDK::FString( L"T-UI-Icon-Habenaro-Silver" );
		case 6:
		case 7:
		case 8:
			return SDK::FString( L"T-UI-Icon-Habenaro-Gold" );
		case 9:
		case 10:
		case 11:
			return SDK::FString( L"T-UI-Icon-Habenaro-Platinum" );
		case 12:
		case 13:
		case 14:
			return SDK::FString( L"T-UI-Icon-Habenaro-Diamond" );
		case 15:
			return SDK::FString( L"T-UI-Icon-Habenaro-Elite" );
		case 16:
			return SDK::FString( L"T-UI-Icon-Habenaro-Champion" );
		case 17:
			return SDK::FString( L"T-UI-Icon-Habenaro-Unreal" );
		default:
			return SDK::FString( L"None" );
		}
	}

	SDK::FLinearColor GetColorByRank( int32_t Rank )
	{
		switch ( Rank )
		{
		case 0:
		case 1:
		case 2:
			return SDK::FLinearColor( 0.902f , 0.580f , 0.227f , 1.0f );
		case 3:
		case 4:
		case 5:
			return SDK::FLinearColor( 0.843f , 0.843f , 0.843f , 1.0f );
		case 6:
		case 7:
		case 8:
			return SDK::FLinearColor( 1.0f , 0.871f , 0.0f , 1.0f );
		case 9:
		case 10:
		case 11:
			return SDK::FLinearColor( 0.0f , 0.7f , 0.7f , 1.0f );
		case 12:
		case 13:
		case 14:
			return SDK::FLinearColor( 0.0f , 0.0f , 0.7f , 1.0f );
		case 15:
			return SDK::FLinearColor( 0.7f , 0.7f , 0.7f , 1.0f );
		case 16:
			return SDK::FLinearColor( 1.0f , 0.6f , 0.0f , 1.0f );
		case 17:
			return SDK::FLinearColor( 0.6f , 0.0f , 0.6f , 1.0f );
		default:
			return SDK::FLinearColor( 0.0f , 0.7859f , 1.0f , 1.0f );
		}
	}

	SDK::FString GetBuildByType( SDK::EFortBuildingType Build )
	{
		switch ( Build )
		{
		case SDK::EFortBuildingType::Wall:
			return SDK::FString( L"Wall" );
		case SDK::EFortBuildingType::Floor:
			return SDK::FString( L"Floor" );
		case SDK::EFortBuildingType::Corner:
			return SDK::FString( L"Corner" );
		case SDK::EFortBuildingType::Deco:
			return SDK::FString( L"Deco" );
		case SDK::EFortBuildingType::Prop:
			return SDK::FString( L"Prop" );
		case SDK::EFortBuildingType::Stairs:
			return SDK::FString( L"Stairs" );
		case SDK::EFortBuildingType::Roof:
			return SDK::FString( L"Roof" );
		case SDK::EFortBuildingType::Pillar:
			return SDK::FString( L"Pillar" );
		case SDK::EFortBuildingType::SpawnedItem:
			return SDK::FString( L"Spawned Item" );
		case SDK::EFortBuildingType::Container:
			return SDK::FString( L"Container" );
		case SDK::EFortBuildingType::Trap:
			return SDK::FString( L"Trap" );
		case SDK::EFortBuildingType::GenericCenterCellActor:
			return SDK::FString( L"Generic Center Cell Actor" );
		case SDK::EFortBuildingType::StructuralCorner:
			return SDK::FString( L"Structural Corner" );
		case SDK::EFortBuildingType::None:
		default:
			return SDK::FString( L"None" );
		}
	}
}