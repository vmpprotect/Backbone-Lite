#pragma once

namespace __std
{
	template <class _Ty>
	struct remove_reference
	{
		using type = _Ty;
	};

	template <class _Ty>
	struct remove_reference<_Ty&>
	{
		using type = _Ty;
	};

	template <class _Ty>
	struct remove_reference<_Ty&&>
	{
		using type = _Ty;
	};

	template <class _Ty>
	using remove_reference_t = typename remove_reference<_Ty>::type;

	template <class _Ty>
	struct remove_const
	{
		using type = _Ty;
	};

	template <class _Ty>
	struct remove_const<const _Ty>
	{
		using type = _Ty;
	};

	template <class _Ty>
	using remove_const_t = typename remove_const<_Ty>::type;
}

#define UniqueBuildValue (char)((((__TIME__[7] - '0') * 1000) + ((__TIME__[6] - '0') * 100) + ((__TIME__[4] - '0') * 10) + (__TIME__[5] - '0') % 9997) % 127)
#define UniqueBuildValueSmall (char)(((__TIME__[7] - '0') % 10) + 1)

namespace skc
{
	template<class _Ty>
	using clean_type = typename __std::remove_const_t<__std::remove_reference_t<_Ty>>;

	char g_key1 = UniqueBuildValue , g_key2 = UniqueBuildValueSmall;

	template <int _size , char _key1 , char _key2 , typename T>
	class skCrypter
	{
	public:
		__forceinline constexpr skCrypter( T* data )
		{
			crypt( data );
		}

		__forceinline T* get( )
		{
			return _storage;
		}

		__forceinline int size( ) // (w)char count
		{
			return _size;
		}

		__forceinline  char key( )
		{
			return _key1;
		}

		__forceinline  T* encrypt( )
		{
			if ( !isEncrypted( ) )
				crypt( _storage );

			return _storage;
		}

		__forceinline  T* decrypt( )
		{
			if ( isEncrypted( ) )
				crypt( _storage );

			return _storage;
		}

		__forceinline bool isEncrypted( )
		{
			return _storage[ _size - 1 ] != 0;
		}

		__forceinline void clear( )
		{
			for ( int i = 0; i < _size; i++ )
			{
				_storage[ i ] = 0;
			}
		}

		__forceinline operator T* ( )
		{
			decrypt( );

			return _storage;
		}

	private:
		__forceinline constexpr void crypt( T* data )
		{
			for ( int i = 0; i < _size; i++ )
			{
				_storage[ i ] = data[ i ] ^ ( _key1 + i % ( 1 + _key2 ) );
			}
		}

		T _storage[ _size ]{};
	};

	__forceinline constexpr void StaticCrypt( wchar_t* data , int size )
	{
		for ( int i = 0; i < size; i++ )
		{
			data[ i ] = data[ i ] ^ ( g_key1 + i % ( 1 + g_key2 ) );
		}
	}
}

#define Encrypt(str) skCrypt_key(str, UniqueBuildValue, UniqueBuildValueSmall)
#define skCrypt_key(str, key1, key2) []() { \
			constexpr static auto crypted = skc::skCrypter \
				<sizeof(str) / sizeof(str[0]), key1, key2, skc::clean_type<decltype(str[0])>>((skc::clean_type<decltype(str[0])>*)str); \
					return crypted; }()