#pragma once

namespace NoCRT
{
	__forceinline int __strlen( const char* str )
	{
		const char* s;
		for ( s = str; *s; ++s );
		return ( s - str );
	}

	int __fabs( int _X )
	{
		int s = _X >> 31;
		return ( _X ^ s ) - s;
	}

	double __sqrtf( double Number )
	{
		if ( Number < 0 )
		{
			return ( -( double ) ( ( ( double ) ( 1e+300 * 1e+300 ) ) * 0.0 ) );
		}

		if ( Number <= 1.192092896e-07 )
		{
			return 0.0;
		}

		double MySqrt = Number;

		while ( __fabs( MySqrt - Number / MySqrt ) > 1.192092896e-07 * MySqrt )
		{
			MySqrt = ( MySqrt + Number / MySqrt ) / 2.0;
		}

		return MySqrt;
	}

	__forceinline int __wcslen( const wchar_t* s )
	{
		int len = 0;

		while ( s[ len ] != L'\0' )
		{
			if ( s[ ++len ] == L'\0' )
				return len;
			if ( s[ ++len ] == L'\0' )
				return len;
			if ( s[ ++len ] == L'\0' )
				return len;
			++len;
		}

		return len;
	}

	__forceinline int __wcslen2( wchar_t* str )
	{
		int counter = 0;
		if ( !str )
			return 0;
		for ( ; *str != '\0'; ++str )
			++counter;
		return counter;
	}

	__forceinline int __wcsicmp_insensitive( wchar_t* cs , wchar_t* ct )
	{
		auto len_cs = __wcslen2( cs );
		auto len_ct = __wcslen2( ct );

		if ( len_cs < len_ct )
			return false;

		for ( size_t i = 0; i <= len_cs - len_ct; i++ )
		{
			bool match = true;

			for ( size_t j = 0; j < len_ct; j++ )
			{
				// Convert characters to lowercase manually
				wchar_t csChar = ( cs[ i + j ] >= L'A' && cs[ i + j ] <= L'Z' ) ? ( cs[ i + j ] + L'a' - L'A' ) : cs[ i + j ];
				wchar_t ctChar = ( ct[ j ] >= L'A' && ct[ j ] <= L'Z' ) ? ( ct[ j ] + L'a' - L'A' ) : ct[ j ];

				if ( csChar != ctChar )
				{
					match = false;
					break;
				}
			}

			if ( match )
				return true;
		}

		return false;
	}

	bool __isxdigit( char c )
	{
		return ( c >= '0' && c <= '9' ) ||
			( c >= 'a' && c <= 'f' ) ||
			( c >= 'A' && c <= 'F' );
	}

	unsigned long __strtoul( const char* str , char** endptr , int base = 16 )
	{
		unsigned long result = 0;
		const char* ptr = str;

		while ( __isxdigit( *ptr ) )
		{
			result *= base;
			if ( *ptr >= '0' && *ptr <= '9' )
			{
				result += *ptr - '0';
			}
			else if ( *ptr >= 'a' && *ptr <= 'f' )
			{
				result += *ptr - 'a' + 10;
			}
			else if ( *ptr >= 'A' && *ptr <= 'F' )
			{
				result += *ptr - 'A' + 10;
			}
			++ptr;
		}

		if ( endptr )
		{
			*endptr = const_cast< char* >( ptr );
		}

		return result;
	}

	inline float __fabs( double x )
	{
		if ( x < 0.0 )
		{
			return -x;
		}

		return x;
	}

	__forceinline void* __memcpy( void* dest , const void* src , unsigned long long count )
	{
		char* char_dest = ( char* ) dest;
		char* char_src = ( char* ) src;
		if ( ( char_dest <= char_src ) || ( char_dest >= ( char_src + count ) ) )
		{
			while ( count > 0 )
			{
				*char_dest = *char_src;
				char_dest++;
				char_src++;
				count--;
			}
		}
		else
		{
			char_dest = ( char* ) dest + count - 1;
			char_src = ( char* ) src + count - 1;
			while ( count > 0 )
			{
				*char_dest = *char_src;
				char_dest--;
				char_src--;
				count--;
			}
		}

		return dest;
	}

	__forceinline void* __memset( void* dst0 , int c0 , unsigned int len )
	{
		unsigned int i;
		unsigned int fill;
		unsigned int chunks = len / sizeof( fill );
		char* char_dest = ( char* ) dst0;
		unsigned int* uint_dest = ( unsigned int* ) dst0;
		fill = ( c0 << 24 ) + ( c0 << 16 ) + ( c0 << 8 ) + c0;

		for ( i = len; i > chunks * sizeof( fill ); i-- )
		{
			char_dest[ i - 1 ] = c0;
		}

		for ( i = chunks; i > 0; i-- )
		{
			uint_dest[ i - 1 ] = fill;
		}

		return dst0;
	}

	__forceinline unsigned int __strncmp( const char* s1 , const char* s2 , size_t n )
	{
		if ( n == 0 )
			return ( 0 );
		do
		{
			if ( *s1 != *s2++ )
				return ( *( unsigned char* ) s1 - *( unsigned char* )--s2 );
			if ( *s1++ == 0 )
				break;
		} while ( --n != 0 );
		return ( 0 );
	}

	__forceinline char* __strstr( const char* s , const char* find )
	{
		char c , sc;
		size_t len;
		if ( ( c = *find++ ) != 0 )
		{
			len = __strlen( find );
			do
			{
				do
				{
					if ( ( sc = *s++ ) == 0 )
					{
						return ( 0 );
					}
				} while ( sc != c );
			} while ( __strncmp( s , find , len ) != 0 );
			s--;
		}
		return ( ( char* ) s );
	}

	__forceinline unsigned int __rand( )
	{
		int start_range = 10;
		int end_range = 30;

		static unsigned int rand = 0xACE1U;

		if ( start_range == end_range )
		{
			return start_range;
		}

		rand += 0x3AD;
		rand %= ( end_range - start_range + 1 );

		while ( rand < start_range )
		{
			rand = rand + ( end_range - start_range + 1 );
		}

		return rand;
	}
}