#pragma once

class Signature
{
private:
	DWORD Count;

	PIMAGE_NT_HEADERS Sponge( uintptr_t Moudle )
	{
		return ( PIMAGE_NT_HEADERS ) ( ( BYTE* ) Moudle + PIMAGE_DOS_HEADER( Moudle )->e_lfanew );
	}

	bool CheckMask( BYTE* Buffer , const char* Pattern , const char* Mask )
	{
		for ( ; *Mask; Pattern++ , Mask++ , Buffer++ )
		{
			if ( *Mask == '?' || *Buffer == *( BYTE* ) Pattern )
				continue;
			return false;
		}

		return true;
	}

	BYTE* GetMask( BYTE* Start , DWORD Size , const char* Pattern , const char* Mask )
	{
		for ( auto x = 0; x < Size - NoCRT::__strlen( Mask ); x++ )
		{
			BYTE* addr = ( BYTE* ) Start + x;
			if ( CheckMask( addr , Pattern , Mask ) )
				return addr;
		}

		return nullptr;
	}
public:
	BYTE* Find( const char* Pattern , const char* Mask , DWORD Occurence = 0 )
	{
		if ( Occurence ) Occurence -= 1;

		size_t Size = Sponge( FortniteClientWin64Shipping )->OptionalHeader.SizeOfImage;
		for ( int x = 0; x < Size - NoCRT::__strlen( Mask ); x++ )
		{
			BYTE* Address = ( BYTE* ) ( FortniteClientWin64Shipping + x );

			if ( CheckMask( Address , Pattern , Mask ) )
			{
				if ( !Occurence || Count == Occurence && Address )
				{
					Count = 0;
					return Address;
				}

				if ( Count < Occurence )
				{
					Address = GetMask( ( BYTE* ) FortniteClientWin64Shipping + x , ( BYTE* ) Size - Address , Pattern , Mask );
					++Count;
					continue;
				}
			}
		}

		return nullptr;
	}
};