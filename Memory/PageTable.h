#pragma once
#include <tlhelp32.h>

namespace PageTable
{
	__int64 GetTextSection( )
	{
		__int64 TextSection = __int64( 0 );

		for ( int i = 0; i < 25; i++ )
		{
			if (*(__int32*)( FortniteClientWin64Shipping + ( i * 0x1000 ) + 0x250 ) == 0x260E020B )
			{
				TextSection = FortniteClientWin64Shipping + ( ( i + 1 ) * 0x1000 );
			}
		}

		return TextSection;
	}

	unsigned int GetProcessID( std::wstring name )
	{
		const auto snapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS , 0 );

		PROCESSENTRY32 entry{ };
		entry.dwSize = sizeof( PROCESSENTRY32 );

		Process32First( snapshot , &entry );
		do
		{
			if ( !name.compare( entry.szExeFile ) )
			{
				return entry.th32ProcessID;
			}

		} while ( Process32Next( snapshot , &entry ) );

		return 0;
	}

	uint64_t FindTextSection( HANDLE hProcess , uintptr_t baseAddress )
	{
		MEMORY_BASIC_INFORMATION mbi;
		uintptr_t address = baseAddress;

		while ( VirtualQueryEx( hProcess , reinterpret_cast< LPCVOID >( address ) , &mbi , sizeof( mbi ) ) )
		{
			if ( mbi.State == MEM_COMMIT && ( mbi.Protect & PAGE_EXECUTE_READ ) )
			{
				return reinterpret_cast< uint64_t >( mbi.BaseAddress );
			}
			address += mbi.RegionSize;
		}

		return 0;
	}
}