#pragma once
#include <vector>

namespace WalkVFT
{
	namespace Memory
	{
		bool IsInProcessRange( uintptr_t Address )
		{
			PIMAGE_NT_HEADERS NtHeader = reinterpret_cast< PIMAGE_NT_HEADERS >( FortniteClientWin64Shipping + reinterpret_cast< PIMAGE_DOS_HEADER >( FortniteClientWin64Shipping )->e_lfanew );

			return Address > FortniteClientWin64Shipping && Address < ( NtHeader->OptionalHeader.SizeOfImage + FortniteClientWin64Shipping );
		}

		template<typename Type = const char*>
		inline uint8_t* FindByStringInAllSections( Type RefStr )
		{
			uintptr_t ImageBase = SDK::GetBaseAddress( );
			PIMAGE_DOS_HEADER DosHeader = ( PIMAGE_DOS_HEADER ) ( ImageBase );
			PIMAGE_NT_HEADERS NtHeader = ( PIMAGE_NT_HEADERS ) ( ImageBase + DosHeader->e_lfanew );

			const DWORD SizeOfImage = NtHeader->OptionalHeader.SizeOfImage;

			uint8_t* SearchStart = ( uint8_t* ) ImageBase;
			DWORD SearchRange = SizeOfImage;

			for ( int i = 0; i < ( int ) SearchRange; i++ )
			{
				if ( ( SearchStart[ i ] == uint8_t( 0x4C ) || SearchStart[ i ] == uint8_t( 0x48 ) ) && SearchStart[ i + 1 ] == uint8_t( 0x8D ) )
				{
					const uint8_t* StrPtr = *( int32_t* ) ( SearchStart + i + 3 ) + 7 + SearchStart + i;

					if ( !IsInProcessRange( ( uintptr_t ) StrPtr ) )
						continue;

					if constexpr ( std::is_same<Type , const char*>( ) )
					{
						if ( strcmp( ( const char* ) RefStr , ( const char* ) StrPtr ) == 0 )
						{
							return { SearchStart + i };
						}
					}
					else
					{
						auto a = std::wstring( ( const wchar_t* ) StrPtr );

						if ( wcscmp( ( const wchar_t* ) RefStr , ( const wchar_t* ) StrPtr ) == 0 )
						{
							return { SearchStart + i };
						}
					}
				}
			}

			return nullptr;
		}

		inline bool IsFunctionRet( uint8_t* Address )
		{
			int Align = 0x10 - ( uintptr_t( Address ) % 0x10 );
			//if (Opcode == RET && (OpcodeBefore is a POP opcode || OpcodeTwoBefore is a different POP Opcode)
			return Address[ 0 ] == 0xC3 && Address[ Align ] == 0x40 && ( ( Address[ -1 ] >= 0x58 && Address[ -1 ] <= 0x5F ) || ( Address[ -2 ] == 0x41 && ( Address[ -1 ] >= 0x58 && Address[ -1 ] <= 0x5F ) ) );
		}

		inline uint8_t* FindFunctionEnd( uint8_t* Address )
		{
			if ( !Address )
				return nullptr;

			int Align = 0x10 - ( uintptr_t( Address ) % 0x10 );

			for ( int i = 0; i < 0xFFFF; i++ )
			{
				if ( IsFunctionRet( Address + i ) )
				{
					return Address + i;
				}
				if ( ( uintptr_t( Address + i ) % 0x10 == 0 ) && ( Address[ i ] == 0x40 && ( Address[ i + 1 ] >= 0x50 && Address[ i + 1 ] <= 0x57 ) && ( Address[ i + 2 ] >= 0x50 && Address[ i + 2 ] <= 0x57 ) ) )
				{
					return Address + i;
				}
			}

			return nullptr;
		}

		inline uintptr_t FindNextFunctionStart( uint8_t* Address )
		{
			if ( !Address )
				return 0x0;

			uintptr_t FuncEnd = ( uintptr_t ) FindFunctionEnd( Address );

			return FuncEnd % 0x10 != 0 ? FuncEnd + ( 0x10 - ( FuncEnd % 0x10 ) ) : FuncEnd;
		}

		static void* FindPatternInRange( std::vector<int>&& Signature , uint8_t* Start , uintptr_t Range , bool bRelative = false , uint32_t Offset = 0 , int SkipCount = 0 )
		{
			const auto PatternLength = Signature.size( );
			const auto PatternBytes = Signature.data( );

			for ( int i = 0; i < ( Range - PatternLength ); i++ )
			{
				bool bFound = true;
				int CurrentSkips = 0;

				for ( auto j = 0ul; j < PatternLength; ++j )
				{
					if ( Start[ i + j ] != PatternBytes[ j ] && PatternBytes[ j ] != -1 )
					{
						bFound = false;
						break;
					}
				}
				if ( bFound )
				{
					if ( CurrentSkips != SkipCount )
					{
						CurrentSkips++;
						continue;
					}

					uintptr_t Address = uintptr_t( Start + i );
					if ( bRelative )
					{
						if ( Offset == -1 )
							Offset = ( uint32_t ) PatternLength;

						Address = ( ( Address + Offset + 4 ) + *( int32_t* ) ( Address + Offset ) );
					}
					return ( void* ) Address;
				}
			}

			return nullptr;
		}

		void* FindPatternInRange( const char* Signature , uint8_t* Start , uintptr_t Range , bool bRelative = false , uint32_t Offset = 0 )
		{
			static auto patternToByte = [ ]( const char* pattern ) -> std::vector<int>
				{
					auto Bytes = std::vector<int>{};
					const auto Start = const_cast< char* >( pattern );
					const auto End = const_cast< char* >( pattern ) + strlen( pattern );

					for ( auto Current = Start; Current < End; ++Current )
					{
						if ( *Current == '?' )
						{
							++Current;
							if ( *Current == '?' ) ++Current;
							Bytes.push_back( -1 );
						}
						else { Bytes.push_back( strtoul( Current , &Current , 16 ) ); }
					}
					return Bytes;
				};

			return FindPatternInRange( patternToByte( Signature ) , Start , Range , bRelative , Offset );
		}

		uintptr_t PatternScan( uintptr_t ModuleBaseAddress , const char* Signature , int PointerIndex = 0 , bool RelativeAddress = false )
		{
			static auto patternToByte = [ ]( const char* pattern ) { auto bytes = std::vector<int>{}; const auto start = const_cast< char* >( pattern ); const auto end = const_cast< char* >( pattern ) + strlen( pattern ); for ( auto current = start; current < end; ++current ) { if ( *current == '?' ) { ++current; if ( *current == '?' ) ++current; bytes.push_back( -1 ); } else bytes.push_back( strtoul( ( const char* ) current , &current , 16 ) ); } return bytes; };

			const auto DOSHeader = ( PIMAGE_DOS_HEADER ) ModuleBaseAddress;
			const auto NtHeaders = ( PIMAGE_NT_HEADERS ) ( ( std::uint8_t* ) ModuleBaseAddress + DOSHeader->e_lfanew );

			const auto SizeOfImage = NtHeaders->OptionalHeader.SizeOfImage;
			auto PatternBytes = patternToByte( Signature );
			const auto ScanBytes = reinterpret_cast< std::uint8_t* >( ModuleBaseAddress );

			const auto Size = PatternBytes.size( );
			const auto Data = PatternBytes.data( );

			for ( auto i = 0ul; i < SizeOfImage - Size; ++i )
			{
				bool Found = true; for ( auto j = 0ul; j < Size; ++j ) { if ( ScanBytes[ i + j ] != Data[ j ] && Data[ j ] != -1 ) { Found = false; break; } }

				if ( Found )
				{
					if ( RelativeAddress )
					{
						return ( ( uintptr_t ) ( ( UINT_PTR ) ( reinterpret_cast< uintptr_t >( &ScanBytes[ i ] ) ) + *( PINT ) ( ( UINT_PTR ) ( reinterpret_cast< uintptr_t >( &ScanBytes[ i ] ) ) + ( ( PointerIndex ) -sizeof( INT ) ) ) + ( PointerIndex ) ) );
					}
					else
					{
						return reinterpret_cast< uintptr_t >( &ScanBytes[ i ] );
					}
				}
			}

			return NULL;
		}
	}

	void WalkVFT( const char* TargetFunctionName , void** VFT , void* TargetFunction , uintptr_t& VFTIndex , int SearchRange )
	{
		for ( int i = 0; !VFTIndex && i < SearchRange; ++i )
		{
			if ( VFT[ i ] == TargetFunction )
			{
				VFTIndex = i;
				break;
			}
		}

		if ( VFTIndex )
		{
			MessageBoxA( 0 , "successfully found process event" , 0 , 0 );
		}
		else
		{
			MessageBoxA( 0 , "failed to find process event" , 0 , 0 );
		}
	}

	bool InitGObjects( )
	{
		MessageBoxA( 0 , "searching for global object array" , 0 , 0 );

		//Objects::UObject::ObjectArray.IsChunked = true;

		uintptr_t TUObjectArray = Memory::PatternScan(
			FortniteClientWin64Shipping ,
			"48 8B 05 ? ? ? ? 48 8B 0C C8 48 8D 04 D1 48 8B 00 8B 40" ,
			7 ,
			true
		);

		if ( !TUObjectArray )
		{
			return false;
		}

		//Objects::UObject::ObjectArray.ChunkedObjects = reinterpret_cast< Objects::Chunked_TUObjectArray* >( TUObjectArray );

		return true;
	}

	/*int32_t FindFunctionFlagsOffset( )
	{
		std::vector<std::pair<void* , SDK::EFunctionFlags>> Infos;

		Infos.push_back( { ObjectArray::FindObjectFast( "WasInputKeyJustPressed" ).GetAddress( ), EFunctionFlags::Final | EFunctionFlags::Native | EFunctionFlags::Public | EFunctionFlags::BlueprintCallable | EFunctionFlags::BlueprintPure | EFunctionFlags::Const } );
		Infos.push_back( { ObjectArray::FindObjectFast( "ToggleSpeaking" ).GetAddress( ), EFunctionFlags::Exec | EFunctionFlags::Native | EFunctionFlags::Public } );
		Infos.push_back( { ObjectArray::FindObjectFast( "SwitchLevel" ).GetAddress( ), EFunctionFlags::Exec | EFunctionFlags::Native | EFunctionFlags::Public } );

		int32 Ret = FindOffset( Infos );

		if ( Ret == OffsetNotFound )
		{
			for ( auto& [_ , Flags] : Infos )
				Flags = Flags | EFunctionFlags::RequiredAPI;
		}

		return FindOffset( Infos );
	}

	void InitPEIndex( )
	{
		void** Vft = WalkVFT::ObjectArray->GetByIndex( 0 )->VFTable;

		auto Resolve32BitRelativeJump = [ ]( void* FunctionPtr ) -> uint8_t*
			{
				uint8_t* Address = reinterpret_cast< uint8_t* >( FunctionPtr );
				if ( *Address == 0xE9 )
				{
					uint8_t* Ret = ( ( Address + 5 ) + *reinterpret_cast< int32_t* >( Address + 1 ) );

					if ( Memory::IsInProcessRange( uintptr_t( Ret ) ) )
						return Ret;
				}

				return reinterpret_cast< uint8_t* >( FunctionPtr );
			};

		for ( int i = 0; i < 0x150; i++ )
		{
			if ( !Vft[ i ] || !Memory::IsInProcessRange( reinterpret_cast< uintptr_t >( Vft[ i ] ) ) )
				break;

			if ( Memory::FindPatternInRange( { 0xF7, -0x1, ( int32_t ) Objects::UFunction::FunctionFlagsOffset, 0x0, 0x0, 0x0, 0x0, 0x04, 0x0, 0x0 } , Resolve32BitRelativeJump( Vft[ i ] ) , 0x400 )
				&& Memory::FindPatternInRange( { 0xF7, -0x1, ( int32_t ) Objects::UFunction::FunctionFlagsOffset, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0 } , Resolve32BitRelativeJump( Vft[ i ] ) , 0x400 ) )
			{
				WalkVFT::ProcessEvent = i;
				MessageBoxA( 0 , "Found PE" , 0 , 0 );
				return;
			}
		}

		uint8_t* StringRef = Memory::FindByStringInAllSections( L"Accessed None" );
		uintptr_t NextFunctionStart = Memory::FindNextFunctionStart( StringRef );

		WalkVFT( "ProcessEvent" , WalkVFT::ObjectArray->GetByIndex( 0 )->VFTable , reinterpret_cast< void* >( NextFunctionStart ) , WalkVFT::ProcessEvent , 0x150 );
	}*/
}