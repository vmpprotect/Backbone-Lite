#pragma once

namespace Objects
{
	class UClass;
	class TUObjectArray;

	class UObject
	{
	public:
		void** VFTable;
		SDK::EObjectFlags Flags;
		int32 Index;
		UClass* Class;
		SDK::FName Name;
		uint8 Pad_4A[ 0x4 ];
		SDK::UObject* Outer;
	};

	class UField : public UObject
	{
	public:
		UField* Next;
	};

	class UStruct : public UField
	{
	public:
		uint8 Pad_58[ 0x10 ];
		UStruct* Super;
		UField* Children;
		class FField* ChildProperties;
		int32 Size;
		int32 MinAlignemnt;
		uint8 Pad_59[ 0x50 ];

	public:
		bool IsSubclassOf( const UStruct* Base ) const
		{
			if ( !Base )
				return false;

			for ( const UStruct* Struct = this; Struct; Struct = Struct->Super )
			{
				if ( Struct == Base )
					return true;
			}

			return false;
		}
	};

	class UFunction : public UStruct
	{
	public:
		static uint32 FunctionFlagsOffset;
	};

	class UClass : public UStruct
	{
	public:
		uint8 Pad_5A[ 0x28 ];
		SDK::EClassCastFlags CastFlags;
		uint8 Pad_5B[ 0x30 ];
		UObject* DefaultObject;
		uint8 Pad_5C[ 0xE8 ];
	};

	struct FUObjectItem
	{
		class UObject* Object;
		uint8 Pad_0[ 0x10 ];
	};

	class Chunked_TUObjectArray
	{
	public:
		enum
		{
			ElementsPerChunk = 0x10000 ,
		};

	public:
		static inline auto DecryptPtr = [ ]( void* ObjPtr ) -> uint8*
			{
				return reinterpret_cast< uint8* >( ObjPtr );
			};

		FUObjectItem** Objects;
		uint8 Pad_0[ 0x08 ];
		int32 MaxElements;
		int32 NumElements;
		int32 MaxChunks;
		int32 NumChunks;

	public:
		inline int32 Num( ) const
		{
			return NumElements;
		}

		inline FUObjectItem** GetDecrytedObjPtr( ) const
		{
			return reinterpret_cast< FUObjectItem** >( DecryptPtr( Objects ) );
		}

		inline class UObject* GetByIndex( const int32 Index ) const
		{
			if ( Index < 0 || Index > NumElements )
				return nullptr;

			const int32 ChunkIndex = Index / ElementsPerChunk;
			const int32 InChunkIdx = Index % ElementsPerChunk;

			return GetDecrytedObjPtr( )[ ChunkIndex ][ InChunkIdx ].Object;
		}
	};

	class Fixed_TUObjectArray
	{
	public:
		static inline auto DecryptPtr = [ ]( void* ObjPtr ) -> uint8*
			{
				return reinterpret_cast< uint8* >( ObjPtr );
			};

	public:
		FUObjectItem* Objects;
		int32 MaxElements;
		int32 NumElements;

	public:
		inline int Num( ) const
		{
			return NumElements;
		}

		inline FUObjectItem* GetDecrytedObjPtr( ) const
		{
			return reinterpret_cast< FUObjectItem* >( DecryptPtr( Objects ) );
		}

		inline class UObject* GetByIndex( const int32 Index ) const
		{
			if ( Index < 0 || Index > NumElements )
				return nullptr;

			return GetDecrytedObjPtr( )[ Index ].Object;
		}
	};

	class TUObjectArray
	{
	public:
		bool IsChunked;
		Chunked_TUObjectArray* ChunkedObjects;
		Fixed_TUObjectArray* FixedObjects;

		int32 Num( )
		{
			if ( IsChunked && ChunkedObjects )
			{
				return ChunkedObjects->Num( );
			}
			else if ( IsChunked == false && FixedObjects )
			{
				return FixedObjects->Num( );
			}

			return 0;
		}

		UObject* GetByIndex( int32 Index )
		{
			if ( IsChunked && ChunkedObjects )
			{
				return ChunkedObjects->GetByIndex( Index );
			}
			else if ( IsChunked == false && FixedObjects )
			{
				return FixedObjects->GetByIndex( Index );
			}

			return nullptr;
		}
	};
}