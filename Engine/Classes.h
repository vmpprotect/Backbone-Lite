#pragma once

namespace SDK
{
	// Forward declarations of classes
	class UWorld;
	class UScruct;
	class UObject;

	class UObject
	{
	public:
		uint64_t GetVTable( )
		{
			return *( uint64_t* ) ( this + 0x0 ); // UObject::vtable
		}

		EObjectFlags GetObjectFlags( )
		{
			return *( EObjectFlags* ) ( this + 0x8 ); // UObject::ObjectFlags
		}

		int GetInternalIndex( )
		{
			return *( int* ) ( this + 0xC ); // UObject::InternalIndex
		}

		FName GetNamePrivate( )
		{
			return *( FName* ) ( this + 0x18 ); // UObject::NamePrivate
		}

		UObject* GetOuterPrivate( )
		{
			return *( UObject** ) ( this + 0x20 ); // UObject::OuterPrivate
		}

		void ProcessEvent( UObject* UFunction , void* Params )
		{
			if ( auto VTable = *( void*** ) this )
			{
				reinterpret_cast< void( __cdecl* )( UObject* , UObject* , void* ) >( VTable[ 78 ] )( this , UFunction , Params );
			}
		}

		static UObject* StaticFindObject( UObject* Class , UObject* Outer , const wchar_t* Name , bool ExactClass )
		{
			static void* Address = nullptr;
			if ( !Address )
			{
				auto Enc_Mask = Encrypt( "xxxx?xxxxxxxxxxxxxxx????xxx????xxx????xxxxxx????xxx" );
				auto Enc_Pattern = Encrypt( "\x48\x89\x5C\x24\x00\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\xAC\x24\x00\x00\x00\x00\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x85\x00\x00\x00\x00\x48\x83\xFA" );
				Address = ( void* ) ( Signature( ).Find( Enc_Pattern.decrypt( ) , Enc_Mask.decrypt( ) ) ) , Enc_Pattern.clear( ) , Enc_Mask.clear( );
			}

			return reinterpret_cast< UObject * ( __cdecl* )( UObject* , UObject* , const wchar_t* , bool ) >( Address )( Class , Outer , Name , ExactClass );
		}

		static UObject* StaticLoadObject( void* ObjectClass , void* InOuter , const TCHAR* InName , const TCHAR* Filename , uint64_t LoadFlags , void* Sandbox , bool bAllowObjectReconciliation , void* InstancingContext )
		{
			static void* Address = nullptr;
			if ( !Address )
			{
				auto Enc_Mask = Encrypt( "xxxxxxxxxxxxxxxxx????xxx????xxx????xxxxxx????xxx????xxxxxx" );
				auto Enc_Pattern = Encrypt( "\x40\x55\x53\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\xAC\x24\x00\x00\x00\x00\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x85\x00\x00\x00\x00\x48\x8B\x85\x00\x00\x00\x00\x45\x33\xE4\x4C\x8B\xB5" );
				Address = ( void* ) ( Signature( ).Find( Enc_Pattern.decrypt( ) , Enc_Mask.decrypt( ) ) ) , Enc_Pattern.clear( ) , Enc_Mask.clear( );
			}

			return reinterpret_cast< UObject * ( __cdecl* )( void* , void* , const TCHAR* , const TCHAR* , uint64_t , void* , bool , void* ) >( Address )( ObjectClass , InOuter , InName , Filename , LoadFlags , Sandbox , bAllowObjectReconciliation , InstancingContext );
		}

		template <class Type>
		static Type FindObject( const wchar_t* Name , UObject* Outer = nullptr )
		{
			return reinterpret_cast< Type >( UObject::StaticFindObject( nullptr , Outer , Name , false ) );
		}

		template <class Type>
		static Type LoadObject( const wchar_t* Name )
		{
			return reinterpret_cast< Type >( UObject::StaticLoadObject( nullptr , nullptr , ( TCHAR* ) Name , nullptr , 0 , nullptr , false , nullptr ) );
		}

		UObject* GetClassPrivate( );  // UObject::ClassPrivate
		bool ObjectIsA( class UObject* Class );
	};

	class FMemory : public UObject
	{
	public:
		static uintptr_t Malloc( int Count , uint32 Alignment )
		{
			static void* Address = nullptr;
			if ( !Address )
			{
				auto Enc_Mask = Encrypt( "xxxx?xxxxxxxxxxxxxx?xxx????xx" );
				auto Enc_Pattern = Encrypt( "\x48\x89\x5C\x24\x00\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x83\xEC\x00\x4C\x8B\x25\x00\x00\x00\x00\x33\xED" );
				Address = ( void* ) ( Signature( ).Find( Enc_Pattern.decrypt( ) , Enc_Mask.decrypt( ) ) ) , Enc_Pattern.clear( ) , Enc_Mask.clear( );
			}

			return reinterpret_cast< uintptr_t( __cdecl* )( uintptr_t , int ) >( Address )( Count , Alignment );
		}

		static void Free( void* Original )
		{
			static void* Address = nullptr;
			if ( !Address )
			{
				auto Enc_Mask = Encrypt( "xxxxx????xxxx?xxxx" );
				auto Enc_Pattern = Encrypt( "\x48\x85\xC9\x0F\x84\x00\x00\x00\x00\x57\x48\x83\xEC\x00\x4C\x89\x74\x24" );
				Address = ( void* ) ( Signature( ).Find( Enc_Pattern.decrypt( ) , Enc_Mask.decrypt( ) ) ) , Enc_Pattern.clear( ) , Enc_Mask.clear( );
			}

			reinterpret_cast< void( __cdecl* )( void* ) >( Address )( Original );
		}
	};

	class USoundBase : public UObject
	{
	public:

	};

	class UFont : public UObject
	{
	public:
		int32_t LegacyFontSize( )
		{
			return *( int32_t* ) ( this + 0x13c );
		}
	};

	class UTexture : public UObject
	{
	public:

	};

	class UTexture2D : public UTexture
	{
	public:

	};

	class UCanvas : public UObject
	{
	public:
		float ClipX( )
		{
			return *( float* ) ( this + 0x30 );
		}

		float ClipY( )
		{
			return *( float* ) ( this + 0x34 );
		}

		UTexture2D* DefaultTexture( )
		{
			return *( UTexture2D** ) ( this + 0x70 );
		}

		void K2_DrawBox( FVector2D ScreenPosition , FVector2D ScreenSize , float Thickness , FLinearColor RenderColor )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"Canvas.K2_DrawBox" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FVector2D& ScreenPosition;
				FVector2D& ScreenSize;
				float Thickness;
				FLinearColor& RenderColor;
			} Params = { ScreenPosition, ScreenSize, Thickness, RenderColor };

			this->ProcessEvent( Function , &Params );
		}

		void K2_DrawLine( FVector2D ScreenPositionA , FVector2D ScreenPositionB , float Thickness , FLinearColor RenderColor )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"Canvas.K2_DrawLine" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FVector2D ScreenPositionA;
				FVector2D ScreenPositionB;
				float Thickness;
				FLinearColor RenderColor;
			} Params = { ScreenPositionA, ScreenPositionB, Thickness, RenderColor };

			this->ProcessEvent( Function , &Params );
		}

		void K2_DrawText( UFont* RenderFont , FString RenderText , FVector2D ScreenPosition , FLinearColor RenderColor , bool bCentreX , bool bCentreY , bool bOutlined )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"Canvas.K2_DrawText" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				UObject* RenderFont;
				FString RenderText;
				FVector2D ScreenPosition;
				FVector2D Scale;
				FLinearColor RenderColor;
				float Kerning;
				FLinearColor ShadowColor;
				FVector2D ShadowOffset;
				bool bCentreX;
				bool bCentreY;
				bool bOutlined;
				FLinearColor OutlineColor;
			} Params = { RenderFont, RenderText, ScreenPosition, FVector2D( 1.0, 1.0 ), RenderColor, 0.f, FLinearColor( ), FVector2D( ), bCentreX, bCentreY, true, FLinearColor( 0.004 , 0.004 , 0.004 , 1 ) };

			this->ProcessEvent( Function , &Params );
		}

		void K2_DrawPolygon( UTexture* RenderTexture , FVector2D ScreenPosition , FVector2D Radius , int32_t NumberOfSides , FLinearColor RenderColor )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"Canvas.K2_DrawPolygon" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				UTexture* RenderTexture;
				FVector2D ScreenPosition;
				FVector2D Radius;
				int32_t NumberOfSides;
				FLinearColor RenderColor;
			} Params = { RenderTexture, ScreenPosition, Radius, NumberOfSides, RenderColor };

			this->ProcessEvent( Function , &Params );
		}

		void K2_DrawTexture( UTexture* RenderTexture , FVector2D ScreenPosition , FVector2D ScreenSize , FVector2D CoordinatePosition , FVector2D CoordinateSize , FLinearColor RenderColor , EBlendMode BlendMode , float Rotation , FVector2D PivotPoint )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"Canvas.K2_DrawTexture" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct K2_DrawTexture_Params
			{
			public:
				UObject* RenderTexture;
				FVector2D ScreenPosition;
				FVector2D ScreenSize;
				FVector2D CoordinatePosition;
				FVector2D CoordinateSize;
				FLinearColor RenderColor;
				EBlendMode BlendMode;
				float Rotation;
				FVector2D PivotPoint;
			};

			K2_DrawTexture_Params Params;
			Params.RenderTexture = RenderTexture;
			Params.ScreenPosition = ScreenPosition;
			Params.ScreenSize = ScreenSize;
			Params.CoordinatePosition = CoordinatePosition;
			Params.CoordinateSize = CoordinateSize;
			Params.RenderColor = RenderColor;
			Params.BlendMode = BlendMode;
			Params.Rotation = Rotation;
			Params.PivotPoint = PivotPoint;

			this->ProcessEvent( Function , &Params );
		}

		FVector K2_Project( FVector WorldLocation )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"Canvas.K2_Project" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FVector WorldLocation;
				FVector ReturnValue;
			} Params = { WorldLocation };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		void K2_Deproject( FVector2D ScreenPosition , FVector* WorldOrigin , FVector* WorldDirection )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"Canvas.K2_Deproject" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
			public:
				FVector2D ScreenPosition;
				FVector WorldOrigin;
				FVector WorldDirection;
			}Parameters;

			Parameters.ScreenPosition = ScreenPosition;

			this->ProcessEvent( Function , &Parameters );

			*WorldOrigin = Parameters.WorldOrigin;
			*WorldDirection = Parameters.WorldDirection;
		}
	};

	class AHUD : public UObject
	{
	public:

	};

	class UActorComponent : public UObject
	{
	public:

	};

	class UCameraComponent : public UActorComponent
	{
	public:

	};

	class APlayerCameraManager : public UObject
	{
	public:
		float GetFOVAngle( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"PlayerCameraManager.GetFOVAngle" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				float ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		FVector GetCameraLocation( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"PlayerCameraManager.GetCameraLocation" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FVector ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		FRotator GetCameraRotation( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"PlayerCameraManager.GetCameraRotation" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FRotator ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}
	};

	class AActor : public UObject
	{
	public:
		void DisableInput( UObject* PlayerController )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"Actor.DisableInput" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				UObject* PlayerController;
			} Params = { PlayerController };

			this->ProcessEvent( Function , &Params );
		}

		void EnableInput( UObject* PlayerController )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"Actor.EnableInput" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				UObject* PlayerController;
			} Params = { PlayerController };

			this->ProcessEvent( Function , &Params );
		}

		FVector GetVelocity( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"Actor.GetVelocity" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FVector ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		bool K2_TeleportTo( FVector DestLocation , FRotator DestRotation )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"Actor.K2_TeleportTo" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FVector DestLocation;
				FRotator DestRotation;
				bool ReturnValue;
			} Params = { DestLocation, DestRotation };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		bool K2_SetActorLocation( FVector NewLocation , bool bSweep , bool bTeleport )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"Actor.K2_SetActorLocation" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FVector NewLocation;
				bool bSweep;
				FHitResult SweepHitResult;
				bool bTeleport;
				FVector ReturnValue;
			} Params = { NewLocation , bSweep, 0, bTeleport };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		FVector K2_GetActorLocation( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"Actor.K2_GetActorLocation" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FVector ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		bool K2_SetActorRotation( FRotator NewRotation , bool bTeleportPhysics )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"Actor.K2_SetActorRotation" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FRotator& NewRotation;
				bool bTeleportPhysics;
				bool ReturnValue;
			} Params = { NewRotation, bTeleportPhysics };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		FRotator K2_GetActorRotation( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"Actor.K2_GetActorRotation" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FRotator ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		void SetActorTickEnabled( bool bEnabled )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"Actor.SetActorTickEnabled" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				bool bEnabled;
			} Params = { bEnabled };

			this->ProcessEvent( Function , &Params );
		}

		void SetActorTickInterval( float TickInterval )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"Actor.SetActorTickInterval" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				float TickInterval;
			} Params = { TickInterval };

			this->ProcessEvent( Function , &Params );
		}

		void SetActorScale3D( FVector NewScale3D )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"Actor.SetActorScale3D" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FVector& NewScale3D;
			} Params = { NewScale3D };

			this->ProcessEvent( Function , &Params );
		}

		void SetNetDormancy( ENetDormancy NewDormancy )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"Actor.SetNetDormancy" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				ENetDormancy NewDormancy;
			} Params = { NewDormancy };

			this->ProcessEvent( Function , &Params );
		}
	};

	class UFortPlayerStateComponent_Habanero : public AActor
	{
	public:
		FRankedProgressReplicatedData GetRankedProgress( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortPlayerStateComponent_Habanero.GetRankedProgress" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FRankedProgressReplicatedData ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}
	};

	class AFortPlayerStateAthena : public AActor
	{
	public:
		int32_t SeasonLevelUIDisplay( )
		{
			return *( int32_t* ) ( this + 0x1228 );
		}

		int32_t KillScore( )
		{
			return *( int32_t* ) ( this + 0x1224 );
		}
	};

	class AFortPlayerState : public AFortPlayerStateAthena
	{
	public:
		UFortPlayerStateComponent_Habanero* HabaneroComponent( )
		{
			return *( UFortPlayerStateComponent_Habanero** ) ( this + 0x9F0 );
		}

		FString GetPlatform( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortPlayerState.GetPlatform" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FString ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}
	};

	class AFortPlayerStateZone : public AFortPlayerState
	{
	public:
		int32_t GetSpectatorCount( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortPlayerStateZone.GetSpectatorCount" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				int32_t ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}
	};

	class APlayerState : public AFortPlayerStateZone
	{
	public:
		void GetPlayerName( AActor* AcknowledgedPawn , wchar_t* PlayerName )
		{
			uint64_t FTextOut;
			uint32_t Length;

			if ( !AcknowledgedPawn )
			{
				Length = *( uint32_t* ) ( this + 0x330 );
				FTextOut = *( uint64_t* ) ( this + 0x328 );
			}
			else
			{
				uint64_t fstring = *( uint64_t* ) ( this + 0xab0 );
				Length = *( uint32_t* ) ( fstring + 16 );
				FTextOut = *( uint64_t* ) ( fstring + 8 );
			}

			NoCRT::__memcpy( PlayerName , ( void* ) FTextOut , Length * sizeof( wchar_t ) );

			auto v6 = Length;
			if ( !v6 )
			{
				*PlayerName = FString( L"None" );
				return;
			}

			char v21;
			uint32_t v22;
			uint32_t i;
			uint32_t v25;
			WORD* v23;

			v21 = v6 - 1;
			if ( !( DWORD ) v6 )
				v21 = 0;
			v22 = 0;
			v23 = ( WORD* ) PlayerName;
			for ( i = ( v21 ) & 3; ; *v23++ += i & 7 )
			{
				v25 = v6 - 1;
				if ( !( DWORD ) v6 )
					v25 = 0;
				if ( v22 >= v25 )
					break;
				i += 3;
				++v22;
			}
		}

		bool IsABot( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"PlayerState.IsABot" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FString ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}
	};

	class UMaterialInterface : public UObject
	{
	public:

	};

	class UMaterial : public UMaterialInterface
	{
	public:
		void SetBlendMode( EBlendMode Value )
		{
			*( EBlendMode* ) ( this + 0x129 ) = Value;
		}

		void SetbDisableDepthTest( bool Value )
		{
			char bDisableDepthTest = *( BYTE* ) ( this + 0x1B0 );
			bDisableDepthTest |= ( Value << 0 );
			*( BYTE* ) ( this + 0x1B0 ) = bDisableDepthTest;
		}

		void SetWireframe( bool Value )
		{
			char Wireframe = *( BYTE* ) ( this + 0x1C0 );
			Wireframe |= ( Value << 6 );
			*( BYTE* ) ( this + 0x1C0 ) = Wireframe;
		}
	};

	class UMaterialInstance : public UMaterialInterface
	{
	public:

	};

	class UMaterialInstanceDynamic : public UMaterialInstance
	{
	public:
		void SetVectorParameterValue( FName ParameterName , FLinearColor& Value )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"MaterialInstanceDynamic.SetVectorParameterValue" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FName ParameterName;
				FLinearColor Value;
			} Params = { };

			Params.ParameterName = ParameterName;
			Params.Value = Value;

			this->ProcessEvent( Function , &Params );
		}

		FLinearColor K2_GetVectorParameterValue( FName ParameterName )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"MaterialInstanceDynamic.K2_GetVectorParameterValue" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FName ParameterName;
				FLinearColor ReturnValue;
			} Params = { ParameterName };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		void SetScalarParameterValue( FName ParameterName , float Value )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"MaterialInstanceDynamic.SetScalarParameterValue" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FName ParameterName;
				float Value;
			} Params = { };

			Params.ParameterName = ParameterName;
			Params.Value = Value;

			this->ProcessEvent( Function , &Params );
		}

		float K2_GetScalarParameterValue( FName ParameterName )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"MaterialInstanceDynamic.K2_GetScalarParameterValue" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FName ParameterName;
				float ReturnValue;
			} Params = { ParameterName };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}
	};

	class UPrimitiveComponent : public UObject
	{
	public:
		void SetCustomDepthStencilValue( int Value )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"PrimitiveComponent.SetCustomDepthStencilValue" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				int Value;
			} Params = { Value };

			this->ProcessEvent( Function , &Params );
		}

		void SetRenderCustomDepth( bool bValue )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"PrimitiveComponent.SetRenderCustomDepth" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				bool bValue;
			} Params = { bValue };

			this->ProcessEvent( Function , &Params );
		}

		UMaterialInstanceDynamic* CreateDynamicMaterialInstance( int32 ElementIndex , UMaterialInterface* Parent , FName OptionalName )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"PrimitiveComponent.CreateDynamicMaterialInstance" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				int32 ElementIndex;
				UMaterialInterface* Parent;
				FName OptionalName;
				UMaterialInstanceDynamic* ReturnValue;
			} Params = { ElementIndex, Parent, OptionalName };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		void SetMaterial( int32_t ElementIndex , UMaterialInterface* Material )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"PrimitiveComponent.SetMaterial" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				int32_t ElementIndex;
				UMaterialInterface* Material;
			} Params = { ElementIndex, Material };

			this->ProcessEvent( Function , &Params );
		}

		UMaterialInterface* GetMaterial( int32_t ElementIndex )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"PrimitiveComponent.GetMaterial" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				int32_t ElementIndex;
				UMaterialInterface* ReturnValue;
			} Params = { ElementIndex };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}
	};

	class USceneComponent : public UPrimitiveComponent
	{
	public:
		FVector GetSocketLocation( FName InSocketName )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"SceneComponent.GetSocketLocation" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FName InSocketName;
				FVector ReturnValue;
			} Params{ InSocketName };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		FVector GetForwardVector( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"SceneComponent.GetForwardVector" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FVector ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		FVector K2_GetComponentLocation( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"SceneComponent.K2_GetComponentLocation" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FVector ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}
	};

	class UMeshComponent : public USceneComponent
	{
	public:
		TArray<UMaterialInterface*> GetMaterials( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"MeshComponent.GetMaterials" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				TArray<UMaterialInterface*> ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}
	};

	class UStaticMeshComponent : public UMeshComponent
	{
	public:

	};

	class USkinnedMeshComponent : public UStaticMeshComponent
	{
	public:
		FName GetBoneName( int32 BoneIndex )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"SkinnedMeshComponent.GetBoneName" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				int32 BoneIndex;
				FName ReturnValue;
			} Params{ BoneIndex };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		int GetNumBones( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"SkinnedMeshComponent.GetNumBones" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				int ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}
	};

	class USkeletalMeshComponent : public USkinnedMeshComponent
	{
	public:
		void SetGlobalAnimRateScale( float Value )
		{
			*( float* ) ( this + 0xA28 ) = Value;
		}

		FVector GetBoneLocation( int BoneID )
		{
			return this->GetSocketLocation( this->GetBoneName( BoneID ) );
		}
	};

	class UItemDefinitionBase : public UObject
	{
	public:
		FText ItemName( )
		{
			return *( FText* ) ( this + 0x40 );
		}
	};

	class UFortItemDefinition : public UItemDefinitionBase
	{
	public:
		EFortRarity Rarity( )
		{
			return *( EFortRarity* ) ( this + 0x9A );
		}

		TSoftObjectPtr<UTexture2D> GetSmallPreviewImage( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortItemDefinition.GetSmallPreviewImage" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				TSoftObjectPtr<UTexture2D> ReturnValue;
			} Params = { true };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}
	};

	class UFortWeaponRangedItemDefinition : public UFortItemDefinition
	{
	public:
		bool HasLightweightProjectile( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortWeaponRangedItemDefinition.HasLightweightProjectile" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				bool ReturnValue;
			} Params = { true };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}
	};

	class UFortWeaponItemDefinition : public UFortWeaponRangedItemDefinition
	{
	public:

	};

	class FFortBaseWeaponStats : public UObject
	{
	public:

	};

	class AFortWeapon : public AActor
	{
	public:
		float GetProjectileGravity( )
		{
			return *( float* ) ( this + 0x1CE4 );
		}

		float GetProjectileSpeed( )
		{
			return *( float* ) ( this + 0x1A78 );
		}

		UFortWeaponItemDefinition* WeaponData( )
		{
			return *( UFortWeaponItemDefinition** ) ( this + 0x510 );
		}

		EFortWeaponCoreAnimation WeaponCoreAnimation( )
		{
			return *( EFortWeaponCoreAnimation* ) ( this + 0x1300 );
		}

		float GetProjectileSpeed( float ChargePercent )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortWeapon.GetProjectileSpeed" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				float ChargePercent;
				float ReturnValue;
			} Params = { ChargePercent };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		FVector GetTargetingSourceLocation( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortWeapon.GetTargetingSourceLocation" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FVector ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		void EnableAltCenterReticle( bool bNewEnabled )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortWeaponRanged.EnableAltCenterReticle" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				bool bNewEnabled;
			} Params = { bNewEnabled };

			this->ProcessEvent( Function , &Params );
		}

		void EnableAltOuterReticle( bool bNewEnabled )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortWeaponRanged.EnableAltOuterReticle" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				bool bNewEnabled;
			} Params = { bNewEnabled };

			this->ProcessEvent( Function , &Params );
		}

		void EnableCornersReticle( bool bNewEnabled )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortWeaponRanged.EnableCornersReticle" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				bool bNewEnabled;
			} Params = { bNewEnabled };

			this->ProcessEvent( Function , &Params );
		}

		bool CanFire( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortWeapon.CanFire" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				bool bPrimaryFire;
				bool ReturnValue;
			} Params = { true };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		FVector GetMuzzleLocation( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortWeapon.GetMuzzleLocation" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				int PatternIndex;
				FVector ReturnValue;
			} Params{ 0 };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		int GetBulletsPerClip( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortWeapon.GetBulletsPerClip" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				int ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		bool IsReloading( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortWeapon.IsReloading" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				bool ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		int GetMagazineAmmoCount( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortWeapon.GetMagazineAmmoCount" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				int ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		int GetRemainingAmmo( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortWeapon.GetRemainingAmmo" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				int ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}
	};

	class AFortWeaponRanged : public AFortWeapon
	{
	public:

	};

	class UFortVehicleFuelComponent : public AActor
	{
	public:
		void SetServerFuel( float Value )
		{
			*( float* ) ( this + 0x110 ) = Value;
		}

		void SetInfiniteFuel( float Value )
		{
			*( float* ) ( this + 0x280 ) = Value;
		}

		float GetFuelCapacity( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortVehicleFuelComponent.GetFuelCapacity" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				float ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}
	};

	class UFortPhysicsVehicleConfigs : public AActor
	{
	public:
		void SetDragCoefficient2( float Value )
		{
			*( float* ) ( this + 0x4C0 ) = Value;
		}
	};

	class AFortAthenaVehicle : public AActor
	{
	public:
		UFortVehicleFuelComponent* CachedFuelComponent( )
		{
			return *( UFortVehicleFuelComponent** ) ( this + 0x12E8 );
		}

		UFortPhysicsVehicleConfigs* FortPhysicsVehicleConfigs( )
		{
			return *( UFortPhysicsVehicleConfigs** ) ( this + 0x1B70 );
		}

		bool SetVehicleStencilHighlighted( AActor* PotentialVehicle , bool bHighlighted , int32_t StencilValueOverride )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortAthenaVehicle.SetVehicleStencilHighlighted" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				AActor* PotentialVehicle;
				bool bHighlighted;
				int32_t StencilValueOverride;
				bool ReturnValue;
			} Params = { PotentialVehicle, bHighlighted, StencilValueOverride };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		float GetSteeringAngle( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortAthenaVehicle.GetSteeringAngle" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				float ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		bool CanContainPlayers( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortAthenaVehicle.CanContainPlayers" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				bool ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		float GetHealth( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortAthenaVehicle.GetHealth" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				float ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		float GetMaxHealth( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortAthenaVehicle.GetMaxHealth" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				float ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}
	};

	class APawn : public AActor
	{
	public:
		USceneComponent* RootComponent( )
		{
			return *( USceneComponent** ) ( this + 0x198 );
		}

		APlayerState* PlayerState( )
		{
			return *( APlayerState** ) ( this + 0x2B0 );
		}

		void AddMovementInput( FVector WorldDirection , float ScaleValue , bool bForce )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"Pawn.AddMovementInput" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FVector& WorldDirection;
				float ScaleValue;
				bool bForce;
			} Params = { WorldDirection, ScaleValue, bForce };

			this->ProcessEvent( Function , &Params );
		}
	};

	class ACharacter : public APawn
	{
	public:
		USkeletalMeshComponent* Mesh( )
		{
			return *( USkeletalMeshComponent** ) ( this + 0x318 );
		}

		bool CanJump( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"Character.CanJump" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				bool ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}
	};

	class AFortPawn : public ACharacter
	{
	public:
		AFortWeapon* CurrentWeapon( )
		{
			return *( AFortWeapon** ) ( this + 0xA68 );
		}

		void PrototypeCharacterMovement( EMovementMode MovementMode , FVector LaunchVelocity )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortPawn.PrototypeCharacterMovement" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				EMovementMode MovementMode;
				FVector& LaunchVelocity;
			} Params = { MovementMode, LaunchVelocity };

			this->ProcessEvent( Function , &Params );
		}

		TArray<AFortWeapon*> GetCurrentWeaponList( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortPawn.GetCurrentWeaponList" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				TArray<AFortWeapon*> ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		bool IsDead( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortPawn.IsDead" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				bool ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		bool IsDBNO( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortPawn.IsDBNO" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				bool ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		char GetTeam( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortPawn.GetTeam" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				char ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		void PawnStartFire( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortPawn.PawnStartFire" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				char FireModeNum;
			} Params = { 1 };

			this->ProcessEvent( Function , &Params );
		}

		void PawnStopFire( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortPawn.PawnStopFire" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				char FireModeNum;
			} Params = { 1 };

			this->ProcessEvent( Function , &Params );
		}
	};

	class AFortAIPawn : public AFortPawn
	{
	public:
		void ResetAIRotationRateToDefault( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortAIPawn.ResetAIRotationRateToDefault" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{

			} Params = { };

			this->ProcessEvent( Function , &Params );
		}

		void SetCanInteract( bool CanInteract )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortAIPawn.SetCanInteract" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				bool CanInteract;
			} Params = { CanInteract };

			this->ProcessEvent( Function , &Params );
		}

		void SetCanSleep( bool InCanSleep )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortAIPawn.SetCanSleep" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				bool InCanSleep;
			} Params = { InCanSleep };

			this->ProcessEvent( Function , &Params );
		}
	};

	class AFortPlayerPawn : public AFortPawn
	{
	public:
		AFortAthenaVehicle* CurrentVehicle( )
		{
			return *( AFortAthenaVehicle** ) ( this + 0x2A10 );
		}

		bool IsInVehicle( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortPlayerPawn.IsInVehicle" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				bool ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		bool IsDrivingVehicle( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortPlayerPawn.IsDrivingVehicle" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				bool ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		bool IsSprinting( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortPlayerPawn.IsSprinting" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				bool ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		bool IsParachuteOpen( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortPlayerPawn.IsParachuteOpen" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				bool ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		bool IsSkyDiving( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortPlayerPawn.IsSkyDiving" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				bool ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}
	};

	class AFortPlayerPawnAthena : public AFortPlayerPawn
	{
	public:

	};

	class APlayerPawn_Athena_Generic_Parent_C : public AFortPlayerPawnAthena
	{
	public:
		TArray<USkeletalMeshComponent*> SkeletalMeshes( )
		{
			return *( TArray<USkeletalMeshComponent*>* )( this + 0x4bf0 );
		}
	};

	class APlayerPawn_Athena_Generic_C : public APlayerPawn_Athena_Generic_Parent_C
	{
	public:

	};

	class APlayerPawn_Athena_C : public APlayerPawn_Athena_Generic_C
	{
	public:

	};

	class ASpectatorPawn : public APlayerPawn_Athena_C
	{
	public:

	};

	class BGA_Athena_SCMachine_C : public AActor
	{
	public:

	};

	class AFortPickupEffect : public AActor
	{
	public:
		UStaticMeshComponent* StaticMesh( )
		{
			return *( UStaticMeshComponent** ) ( this + 0x290 );
		}
	};

	class AFortPickup : public AActor
	{
	public:
		UFortItemDefinition* PrimaryPickupItemEntry( )
		{
			return *( UFortItemDefinition** ) ( this + 0x350 + 0x18 );
		}

		AFortPickupEffect* PickupEffectBlueprint( )
		{
			return *( AFortPickupEffect** ) ( this + 0x5b8 );
		}
	};

	class UBaseBuildingStaticMeshComponent : public UMeshComponent
	{
	public:

	};

	class ABuildingSMActor : public AActor
	{
	public:
		UBaseBuildingStaticMeshComponent* StaticMeshComponent( )
		{
			return *( UBaseBuildingStaticMeshComponent** ) ( this + 0x898 );
		}
	};

	struct BuildingContainer_Bitfield
	{
		char bForceSpawnLootOnDestruction : 1;
		char bForceTossLootOnSpawn : 1;
		char bAlreadySearched : 1;
		char bGivePickupsDirectlyToPlayer : 1;
		char bDisableSpawnLoot : 1;
		char bDoNotDropLootOnDestruction : 1;
		char bSkipRollForDestruction : 1;
	};

	class ABuildingContainer : public ABuildingSMActor
	{
	public:
		bool bAlreadySearched( )
		{
			BuildingContainer_Bitfield bAlreadySearched_Struct = *( BuildingContainer_Bitfield* ) ( this + 0xd92 );
			return bAlreadySearched_Struct.bAlreadySearched;
		}
	};

	struct BuildingWeakSpot_Bitfield
	{
		char bHit : 1;
		char bFadeOut : 1;
		char bActive : 1;
	};

	class ABuildingWeakSpot : public AActor
	{
	public:
		bool bHit( )
		{
			BuildingWeakSpot_Bitfield bHit_Struct = *( BuildingWeakSpot_Bitfield* ) ( this + 0x2C0 );
			return bHit_Struct.bHit;
		}

		bool bActive( )
		{
			BuildingWeakSpot_Bitfield bActive_Struct = *( BuildingWeakSpot_Bitfield* ) ( this + 0x2C0 );
			return bActive_Struct.bActive;
		}
	};

	class AFortAthenaSupplyDrop : public AActor
	{
	public:

	};

	class ABuildingTrap : public AActor
	{
	public:
		float GetArmTime( )
		{
			static UObject* Function;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"BuildingTrap.GetArmTime" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				float ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}
	};

	class AAthenaSuperDingo : public AActor
	{
	public:

	};

	class AFortProjectileBase : public AActor
	{
	public:

	};

	class ABuildingActor : public AActor
	{
	public:
		EFortBuildingType BuildingType( )
		{
			return *( EFortBuildingType* ) ( this + 0x4CD );
		}

		uint8 TeamIndex( )
		{
			return *( uint8* ) ( this + 0x4CF );
		}

		bool IsPlayerBuilt( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"BuildingActor.IsPlayerBuilt" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				bool ReturnValue;
			} Params;

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		bool HasHealthLeft( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"BuildingActor.HasHealthLeft" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				bool ReturnValue;
			} Params;

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		void SetQuestHighlight( bool Enabled )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"BuildingActor.SetQuestHighlight" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				bool Enabled;
			} Params = { Enabled };

			this->ProcessEvent( Function , &Params );
		}

		void SetSuppressHealthBar( bool bNewValue )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"BuildingActor.SetSuppressHealthBar" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				bool bNewValue;
			} Params = { bNewValue };

			this->ProcessEvent( Function , &Params );
		}

		float GetHealth( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"BuildingActor.GetHealth" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				float ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		float GetMaxHealth( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"BuildingActor.GetMaxHealth" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				float ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		void ForceBuildingHealth( float NewHealth )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"BuildingActor.ForceBuildingHealth" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				float NewHealth;
			} Params = { NewHealth };

			this->ProcessEvent( Function , &Params );
		}

		void SetHealth( float NewHealth )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"BuildingActor.SetHealth" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				float NewHealth;
			} Params = { NewHealth };

			this->ProcessEvent( Function , &Params );
		}
	};

	class AController : public AActor
	{
	public:
		APlayerState* PlayerState( )
		{
			return *( APlayerState** ) ( this + 0x298 );
		}

		void SetIgnoreLookInput( bool bNewLookInput )
		{
			static UObject* Function;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"Controller.SetIgnoreLookInput" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				bool bNewLookInput;
			} Params = { bNewLookInput };

			this->ProcessEvent( Function , &Params );
		}
	};

	class AFortPlayerController : public AController
	{
	public:
		TArray<ABuildingActor*> HighlightedPrimaryBuildings( )
		{
			return *( TArray<ABuildingActor*>* )( this + 0x18F8 );
		}
	};

	class APlayerController : public AFortPlayerController
	{
	public:
		APlayerPawn_Athena_C* AcknowledgedPawn( )
		{
			return *( APlayerPawn_Athena_C** ) ( this + 0x338 );
		}

		APlayerCameraManager* PlayerCameraManager( )
		{
			return *( APlayerCameraManager** ) ( this + 0x348 );
		}

		float InputYawScale( )
		{
			return *( float* ) ( this + 0x538 );
		}

		float InputPitchScale( )
		{
			return *( float* ) ( this + 0x53c );
		}

		ASpectatorPawn* GetSpectatorPawn( )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"PlayerController.GetSpectatorPawn" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				ASpectatorPawn* ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		void AddYawInput( float Val )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"PlayerController.AddYawInput" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				float Val;
			} Params = { Val };

			this->ProcessEvent( Function , &Params );
		}

		void AddPitchInput( float Val )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"PlayerController.AddPitchInput" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				float Val;
			} Params = { Val };

			this->ProcessEvent( Function , &Params );
		}

		AHUD* GetHUD( )
		{
			static UObject* Function;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"PlayerController.GetHUD" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				AHUD* ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		void FOV( float NewFOV )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"PlayerController.FOV" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				float NewFOV;
			} Params = { NewFOV };

			this->ProcessEvent( Function , &Params );
		}

		FVector2D GetMousePosition( )
		{
			static UObject* Function;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"PlayerController.GetMousePosition" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				float LocationX;
				float LocationY;
				bool ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return FVector2D( double( Params.LocationX ) , double( Params.LocationY ) );
		}

		bool IsInputKeyDown( FKey key )
		{
			static UObject* Function;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"PlayerController.IsInputKeyDown" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FKey key;
				bool ReturnValue;
			} Params = { key };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		void ClientIgnoreMoveInput( bool bIgnore )
		{
			static UObject* Function;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"PlayerController.ClientIgnoreMoveInput" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				bool bIgnore;
			} Params = { bIgnore };

			this->ProcessEvent( Function , &Params );
		}

		bool WasInputKeyJustPressed( FKey key )
		{
			static UObject* Function;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"PlayerController.WasInputKeyJustPressed" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FKey key;
				bool ReturnValue;
			} Params = { key };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		void SetMouseLocation( int32_t X , int32_t Y )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"PlayerController.SetMouseLocation" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				int32_t X;
				int32_t Y;
			} Params = { X, Y };

			this->ProcessEvent( Function , &Params );
		}
	};

	class UGameViewportClient : public UObject
	{
	public:
		bool LineTraceSingle( UObject* World , const FVector& Start , const FVector& End )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetSystemLibrary.LineTraceSingle" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				UObject* WorldContextObject;                                       // (ConstParm, Parm, ZeroConstructor)
				FVector                                     Start;                                                    // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
				FVector                                     End;                                                      // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
				TEnumAsByte<ETraceTypeQuery>                       TraceChannel;                                             // (Parm, ZeroConstructor, IsPlainOldData)
				bool                                               bTraceComplex;                                            // (Parm, ZeroConstructor, IsPlainOldData)
				TArray<uint64_t>                                   ActorsToIgnore;                                           // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
				TEnumAsByte<EDrawDebugTrace>                       DrawDebugType;                                            // (Parm, ZeroConstructor, IsPlainOldData)
				FHitResult                                  OutHit;                                                   // (Parm, OutParm, IsPlainOldData)
				bool                                               bIgnoreSelf;                                              // (Parm, ZeroConstructor, IsPlainOldData)
				FLinearColor                                TraceColor;                                               // (Parm, ZeroConstructor, IsPlainOldData)
				FLinearColor                                TraceHitColor;                                            // (Parm, ZeroConstructor, IsPlainOldData)
				float                                              DrawTime;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
				bool                                               ReturnValue;
			} params;
			params.WorldContextObject = World;
			params.Start = Start;
			params.End = End;
			params.TraceChannel = ETraceTypeQuery::TraceTypeQuery2;
			params.bTraceComplex = true;
			params.ActorsToIgnore = TArray<uint64_t>( );
			params.DrawDebugType = EDrawDebugTrace::None;
			params.bIgnoreSelf = true;
			params.TraceColor = FLinearColor( );
			params.TraceHitColor = FLinearColor( );
			params.DrawTime = 0.0f;

			this->ProcessEvent( Function , &params );

			return !params.ReturnValue;
		}

		UWorld* World( )
		{
			return *( UWorld** ) ( this + 0x78 );
		}
	};

	class UPlayer : public UObject
	{
	public:
		APlayerController* PlayerController( )
		{
			return *( APlayerController** ) ( this + 0x30 );
		}
	};

	class UFortClientSettingsRecord : public UObject
	{
	public:
		float HUDScale( )
		{
			return *( float* ) ( this + 0x518 );
		}
	};

	class UFortLocalPlayer : public UPlayer
	{
	public:
		UFortClientSettingsRecord* ClientSettingsRecord( )
		{
			return *( UFortClientSettingsRecord** ) ( this + 0x378 );
		}
	};

	class USceneViewState : public UObject
	{
	public:
		FMatrix Projection( )
		{
			return *( FMatrix* ) ( this + 0x900 );
		}
	};

	class ULocalPlayer : public UFortLocalPlayer
	{
	public:
		UGameViewportClient* ViewportClient( )
		{
			return *( UGameViewportClient** ) ( this + 0x78 );
		}

		USceneViewState* GetViewState( )
		{
			TArray <USceneViewState*> ViewState = *( TArray <USceneViewState*>* )( this + 0xd0 );

			return ViewState[ 1 ];
		}
	};

	class UGameInstance : public UObject
	{
	public:
		TArray <ULocalPlayer*> LocalPlayers( )
		{
			return *( TArray <ULocalPlayer*>* )( this + 0x38 );
		}
	};

	class UGameUserSettings : public UObject
	{
	public:

	};

	class UFortGameUserSettings : public UGameUserSettings
	{
	public:

	};

	class UFortKismetLibrary : public UObject
	{
	public:
		FHitResult GetPlayerAimPointHit( AFortPlayerController* SourcePlayer , float MaxRange , TArray<AActor*>& IgnoredActors )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortKismetLibrary.CheckLineOfSightToActorWithChannel" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				AFortPlayerController* SourcePlayer;
				float MaxRange;
				TArray<AActor*>& IgnoredActors;
				FHitResult ReturnValue;
			} Params = { SourcePlayer, MaxRange, IgnoredActors };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		bool OnSameTeam( AActor* ActorA , AActor* ActorB )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortKismetLibrary.OnSameTeam" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				AActor* ActorA;
				AActor* ActorB;
				bool ReturnValue;
			} Params = { ActorA, ActorB };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		FString GetHumanReadableName( AActor* Actor )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortKismetLibrary.GetHumanReadableName" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				AActor* Actor;
				FString ReturnValue;
			} Params = { Actor };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		bool CheckLineOfSightToActorWithChannel( FVector SourcePos , AActor* Target , ECollisionChannel TargetFilterChannel , AActor* Source )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortKismetLibrary.CheckLineOfSightToActorWithChannel" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FVector SourcePos;
				AActor* Target;
				ECollisionChannel TargetFilterChannel;
				AActor* Source;
				bool ReturnValue;
			} Params = { SourcePos, Target, TargetFilterChannel, Source };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		bool GetSafeZoneLocation( UObject* WorldContextObject , int32_t SafeZoneIndex , FVector& OutLocation )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortKismetLibrary.GetSafeZoneLocation" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				UObject* WorldContextObject;
				int32_t SafeZoneIndex;
				FVector& OutLocation;
				bool ReturnValue;
			} Params = { WorldContextObject, SafeZoneIndex, OutLocation };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		int32_t GetCurrentSafeZonePhase( UObject* WorldContextObject )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"FortKismetLibrary.GetCurrentSafeZonePhase" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				UObject* WorldContextObject;
				int32_t ReturnValue;
			} Params = { WorldContextObject };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

	};

	class UKismetMathLibrary : public UObject
	{
	public:
		FVector2D Vector2DInterpTo( FVector2D Current , FVector2D Target , float DeltaTime , float InterpSpeed )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.Vector2DInterpTo" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FVector2D Current;
				FVector2D Target; float DeltaTime;
				float InterpSpeed;
				FVector2D ReturnValue;
			} Params = { Current , Target , DeltaTime , InterpSpeed };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		FVector VLerp( FVector A , FVector B , float Alpha )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.VLerp" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FVector A; FVector B; float Alpha;
				FVector ReturnValue;
			} Params = { A, B, Alpha };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		int32_t round( double A )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.round" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				int32_t A;
				int32_t ReturnValue;
			} Params = { A };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		FLinearColor LinearColorLerpUsingHSV( FLinearColor A , FLinearColor B , float Alpha )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.LinearColorLerpUsingHSV" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
			public:
				FLinearColor A;
				FLinearColor B;
				float Alpha;
				FLinearColor ReturnValue;
			}Parameters;

			Parameters.A = A;
			Parameters.B = B;
			Parameters.Alpha = Alpha;

			this->ProcessEvent( Function , &Parameters );

			return Parameters.ReturnValue;
		}

		FVector Vector_ClampSize2D( FVector& A , float Min , float Max )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.Vector_ClampSize2D" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FVector& A;
				float Min;
				float Max;
			} Params = { A, Min, Max };

			this->ProcessEvent( Function , &Params );

			return Params.A;
		}

		FVector Conv_RotatorToVector( FRotator InRot )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.Conv_RotatorToVector" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FRotator InRot;
				FVector ReturnValue;
			} Params = { InRot };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		float NormalizeAxis( float Angle )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.NormalizeAxis" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				float Angle;
				float ReturnValue;
			} Params = { Angle };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		int32_t FMod( double Dividend , double Divisor , double& Remainder )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.FMod" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				double Dividend; double Divisor; double& Remainder;
				int32_t ReturnValue;
			} Params = { Dividend, Divisor, Remainder };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		double FMin( double A , double B )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.FMin" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				double A , B;
				double ReturnValue;
			} Params = { A, B };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		int32_t Max( int32_t A , int32_t B )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.Max" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				int32_t A , B;
				int32_t ReturnValue;
			} Params = { A, B };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		double FMax( double A , double B )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.FMax" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				double A , B;
				double ReturnValue;
			} Params = { A, B };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		FRotator RLerp( FRotator A , FRotator B , float Alpha , bool bShortestPath )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.Lerp" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FRotator A; FRotator B; float Alpha; bool bShortestPath;
				FRotator ReturnValue;
			} Params = { A, B, Alpha, bShortestPath };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		double Lerp( double A , double B , double Alpha )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.Lerp" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				double A , B , Alpha;
				double ReturnValue;
			} Params = { A, B, Alpha };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		double Clamp( double Value , double Min , double Max )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.FClamp" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				double Value , Min , Max;
				double ReturnValue;
			} Params = { Value, Min, Max };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		double sin( double A )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.sin" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				double A;
				double ReturnValue;
			} Params = { A };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		double cos( double A )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.cos" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				double A;
				double ReturnValue;
			} Params = { A };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		double acos( double A )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.acos" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				double A;
				double ReturnValue;
			} Params = { A };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		double tan( double A )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.tan" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				double A;
				double ReturnValue;
			} Params = { A };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		double asin( double A )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.asin" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				double A;
				double ReturnValue;
			} Params = { A };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		double atan( double A )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.atan" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				double A;
				double ReturnValue;
			} Params = { A };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		double Atan2( double Y , double X )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.Atan2" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				double Y;
				double X;
				double ReturnValue;
			} Params = { Y, X };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		double abs( double A )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.abs" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				double A;
				double ReturnValue;
			} Params = { A };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		double Pow( double Base , double exp )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.MultiplyMultiply_FloatFloat" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				double Base;
				double exp;
				double ReturnValue;
			} Params = { Base, exp };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		double Vector_Distance( FVector V1 , FVector V2 )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.Vector_Distance" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FVector v1;
				FVector v2;
				double ReturnValue;
			} Params = { V1, V2 };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		double Vector_Distance2D( FVector2D v1 , FVector2D v2 )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.Vector_Distance2D" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FVector v1;
				FVector v2;
				double ReturnValue;
			} Params = { FVector( v1.X, v1.Y, 0.0 ), FVector( v2.X, v2.Y, 0.0 ) };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		double sqrt( double A )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.sqrt" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				double A;
				double ReturnValue;
			} Params = { A };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		int32 RandomIntegerInRange( int32 Min , int32 Max )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.RandomIntegerInRange" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				int32 Min;
				int32 Max;
				int32 ReturnValue;
			} Params = { Min, Max };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		double RandomFloatInRange( double Min , double Max )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.RandomFloatInRange" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				double Min;
				double Max;
				double ReturnValue;
			} Params = { Min, Max };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		float DegreesToRadians( float A )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.DegreesToRadians" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				float A;
				float ReturnValue;
			} Params = { A };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		double RadiansToDegrees( double A )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.RadiansToDegrees" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				double A;
				double ReturnValue;
			} Params = { A };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		FVector GetRightVector( FRotator InRot )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.GetRightVector" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FRotator InRot;
				FVector ReturnValue;
			} Params = { InRot };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		FVector GetForwardVector( FRotator InRot )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.GetForwardVector" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FRotator InRot;
				FVector ReturnValue;
			} Params = { InRot };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		FRotator FindLookAtRotation( FVector& Start , FVector& Target )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.FindLookAtRotation" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FVector Start;
				FVector Target;
				FRotator ReturnValue;
			} Params = { Start, Target };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		FRotator RInterpTo_Constant( FRotator& Current , FRotator& Target , float DeltaTime , float InterpSpeed )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.RInterpTo_Constant" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FRotator Current;
				FRotator Target;
				float DeltaTime;
				float InterpSpeed;
				FRotator ReturnValue;
			} Params = { Current, Target, DeltaTime, InterpSpeed };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		FRotator RInterpTo( FRotator& Current , FRotator& Target , float DeltaTime , float InterpSpeed )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetMathLibrary.RInterpTo" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FRotator Current;
				FRotator Target;
				float DeltaTime;
				float InterpSpeed;
				FRotator ReturnValue;
			} Params = { Current, Target, DeltaTime, InterpSpeed };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}
	};

	class UGameplayStatics : public UObject
	{
	public:
		TArray<UObject*> GetAllActorsOfClass( UObject* WorldContextObject , UObject* ActorClass )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"GameplayStatics.GetAllActorsOfClass" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				UObject* WorldContextObject;
				UObject* ActorClass;
				TArray<UObject*> OutActors;
			} Params = { WorldContextObject, ActorClass };

			this->ProcessEvent( Function , &Params );

			return Params.OutActors;
		}

		bool ObjectIsA( UObject* Object , UObject* ObjectClass )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"GameplayStatics.ObjectIsA" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				UObject* Object;
				UObject* ObjectClass;
				bool ReturnValue;
			} Params = { Object, ObjectClass };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		double GetWorldDeltaSeconds( UObject* WorldContextObject )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"GameplayStatics.GetWorldDeltaSeconds" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				UObject* WorldContextObject;
				double ReturnValue;
			} Params = { WorldContextObject };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		double GetTimeSeconds( UObject* WorldContextObject )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"GameplayStatics.GetTimeSeconds" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				UObject* WorldContextObject;
				double ReturnValue;
			} Params = { WorldContextObject };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}
	};

	class UKismetSystemLibrary : public UObject
	{
	public:
		void GetComponentBounds( USceneComponent* Component , FVector* Origin , FVector* BoxExtent , float* SphereRadius )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetSystemLibrary.GetComponentBounds" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
			public:
				USceneComponent* Component;
				FVector Origin;
				FVector BoxExtent;
				float SphereRadius;
			}Parameters;

			Parameters.Component = Component;

			this->ProcessEvent( Function , &Parameters );

			if ( Origin != nullptr )
				*Origin = Parameters.Origin;

			if ( BoxExtent != nullptr )
				*BoxExtent = Parameters.BoxExtent;

			if ( SphereRadius != nullptr )
				*SphereRadius = Parameters.SphereRadius;
		}

		bool LineTraceSingle( UObject* WorldContextObject , FVector Start , FVector End , ETraceTypeQuery TraceChannel , bool bTraceComplex , TArray<AActor*> ActorsToIgnore , EDrawDebugTrace DrawDebugType , FHitResult* OutHit , bool bIgnoreSelf , FLinearColor TraceColor , FLinearColor TraceHitColor , float DrawTime )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetSystemLibrary.LineTraceSingle" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
			public:
				UObject* WorldContextObject;
				FVector Start;
				FVector End;
				ETraceTypeQuery TraceChannel;
				bool bTraceComplex;
				uint8 Pad_1C02[ 0x6 ];
				TArray<AActor*> ActorsToIgnore;
				EDrawDebugTrace DrawDebugType;
				uint8 Pad_1C04[ 0x3 ];
				FHitResult OutHit;
				bool bIgnoreSelf;
				uint8 Pad_1C05[ 0x3 ];
				FLinearColor TraceColor;
				FLinearColor TraceHitColor;
				float DrawTime;
				bool ReturnValue;
				uint8 Pad_1C06[ 0x7 ];
			}Parms;

			Parms.WorldContextObject = WorldContextObject;
			Parms.Start = Start;
			Parms.End = End;
			Parms.TraceChannel = TraceChannel;
			Parms.bTraceComplex = bTraceComplex;
			Parms.ActorsToIgnore = ActorsToIgnore;
			Parms.DrawDebugType = DrawDebugType;
			Parms.bIgnoreSelf = bIgnoreSelf;
			Parms.TraceColor = TraceColor;
			Parms.TraceHitColor = TraceHitColor;
			Parms.DrawTime = DrawTime;

			this->ProcessEvent( Function , &Parms );

			*OutHit = Parms.OutHit;

			return Parms.ReturnValue;
		}

		FString GetObjectName( UObject* Object )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetSystemLibrary.GetObjectName" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				UObject* Object;
				FString ReturnValue;
			} Params = { Object };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		FString GetPathName( UObject* Object )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetSystemLibrary.GetPathName" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				UObject* Object;
				FString ReturnValue;
			} Params = { Object };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}
	};

	class UKismetStringLibrary : public UObject
	{
	public:
		int32_t Len( FString S )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetStringLibrary.Len" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FString& S;
				int32_t ReturnValue;
			} Params = { S };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		FString Conv_IntToString( int32 InInt )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetStringLibrary.Conv_IntToString" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				int32 InInt;
				FString ReturnValue;
			} Params = { InInt };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		bool Contains( FString SearchIn , FString Substring , bool bUseCase , bool bSearchFromEnd )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetStringLibrary.Contains" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FString SearchIn;
				FString Substring;
				bool bUseCase;
				bool bSearchFromEnd;
				bool ReturnValue;
			} Params = { SearchIn, Substring, bUseCase, bSearchFromEnd };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		FName Conv_StringToName( FString InString )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetStringLibrary.Conv_StringToName" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FString InString;
				FName ReturnValue;
			} Params = { InString };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		FString Conv_NameToString( FName InName )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetStringLibrary.Conv_NameToString" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FName InName;
				FString ReturnValue;
			} Params = { InName };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		FString BuildString_Int( FString AppendTo , FString Prefix , int InInt , FString Suffix )
		{
			static UObject* Function = 0;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetStringLibrary.BuildString_Int" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FString AppendTo;
				FString Prefix;
				int InInt;
				FString Suffix;
				FString ReturnValue;
			} Params = { AppendTo, Prefix, InInt, Suffix };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}

		FString BuildString_Double( FString AppendTo , FString Prefix , double InDouble , FString Suffix )
		{
			static UObject* Function;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetStringLibrary.BuildString_Double" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				FString AppendTo;
				FString Prefix;
				double InDouble;
				FString Suffix;
				FString ReturnValue;
			} Params = { AppendTo, Prefix, InDouble, Suffix };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}
	};

	static UFortKismetLibrary* FortLibrary = nullptr;
	static UKismetSystemLibrary* SystemLibrary = nullptr;
	static UKismetMathLibrary* MathLibrary = nullptr;
	static UGameplayStatics* GameplayStatics = nullptr;
	static UKismetStringLibrary* StringLibrary = nullptr;

	class UEngine : public UObject
	{
	public:
		UFont* MediumFont( )
		{
			return *( UFont** ) ( this + 0x70 );
		}

		void ExecuteConsoleCommand( UObject* WorldContextObject , FString Command , APlayerController* SpecificPlayer )
		{
			static UObject* Function;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"KismetSystemLibrary.ExecuteConsoleCommand" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				UObject* WorldContextObject;
				FString Command;
				APlayerController* SpecificPlayer;
			} Params = { WorldContextObject, Command, SpecificPlayer };

			this->ProcessEvent( Function , &Params );
		}
	};

	class AWorldSettings : public UObject
	{
	public:
		float WorldGravityZ( )
		{
			return *( float* ) ( this + 0x310 );
		}
	};

	class ULevel : public UObject
	{
	public:
		AWorldSettings* WorldSettings( )
		{
			return *( AWorldSettings** ) ( this + 0x2a8 );
		}

		TArray<AActor*> Actors( )
		{
			return *( TArray<AActor*>* )( this + 0xA0 );
		}
	};

	class AGameModeBase : public UObject
	{
	public:
		int32_t GetNumSpectators( )
		{
			static UObject* Function;
			if ( !Function )
			{
				auto Enc_Function = Encrypt( L"GameModeBase.GetNumSpectators" );
				Function = FindObject<UObject*>( Enc_Function.decrypt( ) ); Enc_Function.clear( );
			}

			struct
			{
				int32_t ReturnValue;
			} Params = { };

			this->ProcessEvent( Function , &Params );

			return Params.ReturnValue;
		}
	};

	class AFortGameState : public UObject
	{
	public:

	};

	class UWorld : public UObject
	{
	public:
		AGameModeBase* AuthorityGameMode( )
		{
			return *( AGameModeBase** ) ( this + 0x158 );
		}

		UGameInstance* OwningGameInstance( )
		{
			return *( UGameInstance** ) ( this + 0x1d8 );
		}

		FVector GetCameraLocation( )
		{
			return *( FVector* ) ( *( uintptr_t* ) ( this + 0x110 ) );
		}

		FRotator GetCameraRotation( )
		{
			uintptr_t RotationPointer = *( uintptr_t* ) ( this + 0x120 );
			FRotator ReturnValue = FRotator( *( double* ) ( RotationPointer ) , *( double* ) ( RotationPointer + 0x20 ) , *( double* ) ( RotationPointer + 0x1D0 ) );

			ReturnValue.Yaw = ( ( MathLibrary->Atan2( ReturnValue.Pitch * -1.0 , ReturnValue.Yaw ) * ( 180.0 / M_PI ) ) * -1.0 ) * -1.0;
			ReturnValue.Pitch = MathLibrary->asin( ReturnValue.Roll ) * ( 180.0 / M_PI );
			ReturnValue.Roll = 0.0;

			return ReturnValue;
		}

		ULevel* PersistentLevel( )
		{
			return *( ULevel** )( this + 0x30 );
		}

		TArray<ULevel*> Levels( )
		{
			return *( TArray<ULevel*>* )( this + 0x178 );
		}
	};

	SDK::FRotator NormalizeAxis( SDK::FRotator Rotation )
	{
		while ( Rotation.Yaw > 180.f )
			Rotation.Yaw -= 360.f;
		while ( Rotation.Yaw < -180.f )
			Rotation.Yaw += 360.f;

		while ( Rotation.Roll > 180.f )
			Rotation.Roll -= 360.f;
		while ( Rotation.Roll < -180.f )
			Rotation.Roll += 360.f;

		while ( Rotation.Pitch > 180.f )
			Rotation.Pitch -= 360.f;
		while ( Rotation.Pitch < -180.f )
			Rotation.Pitch += 360.f;

		return Rotation;
	}
}