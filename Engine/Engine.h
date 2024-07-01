#pragma once

namespace SDK
{
	struct ReticlePair
	{
		unsigned short TableValue;
		unsigned short TableOffset;
	};

	// STRUCTS
	template <class ArrayType>
	struct TArray
	{
		TArray( )
		{
			this->Data = nullptr;
			this->NumElements = this->MaxElements = 0;
		};

		ArrayType* Data;
		int NumElements , MaxElements;

		int32 GetSlack( ) const { return this->MaxElements - this->NumElements; }

		ArrayType& operator[]( int i )
		{
			return this->Data[ i ];
		};

		int Size( )
		{
			return this->NumElements;
		}

		bool IsValidIndex( int i )
		{
			return bool( i < this->NumElements );
		}

		bool IsValid( )
		{ 
			return this->Data && this->NumElements > 0 && this->MaxElements >= this->NumElements;
		}

		template<size_t N>
		bool New( ArrayType( &elems )[ N ] )
		{
			//Allocate new array
			ArrayType* NewAllocation = new ArrayType[ sizeof( ArrayType ) * N ];

			//Fill with old data
			for ( int i = 0; i < this->NumElements - 1; i++ )
			{
				NewAllocation[ i ] = this->Data[ i ];
			}

			this->NumElements = this->MaxElements = N;

			return true;
		}

		bool Add( ArrayType& Element )
		{
			if ( GetSlack( ) <= 0 )
				return false;

			Data[ NumElements ] = Element;
			NumElements++;

			return true;
		}

		bool Remove( int32 Index )
		{
			if ( !Valid( Index ) )
				return false;

			NumElements--;

			for ( int i = Index; i < NumElements; i++ )
			{
				/* NumElements was decremented, acessing i + 1 is safe */
				Data[ i ] = Data[ i + 1 ];
			}

			return true;
		}
	};

	class FAllocatedString;

	struct FString : public TArray<wchar_t>
	{
		FString( ) { };

		FString( const wchar_t* Other )
		{
			this->MaxElements = this->NumElements = *Other ? static_cast< int >( NoCRT::__wcslen( Other ) ) + 1 : 0;

			if ( this->NumElements )
			{
				this->Data = const_cast< wchar_t* >( Other );
			}
		};

		FString( const wchar_t* Other , int Size )
		{
			this->MaxElements = this->NumElements = Size;

			if ( this->NumElements )
			{
				this->Data = const_cast< wchar_t* >( Other );
			}
		};

		operator bool( ) { return bool( this->Data ); }

		std::string ToString( )
		{
			if ( *this )
			{
				std::wstring WData( Data );
#pragma warning(suppress: 4244)
				return std::string( WData.begin( ) , WData.end( ) );
			}

			return "";
		}

		wchar_t* c_str( )
		{
			return this->Data;
		}

		int Size( )
		{
			return this->NumElements;
		}
	};

	class FAllocatedString : public FString
	{
	public:
		FAllocatedString( ) = delete;

	public:
		FAllocatedString( int32 Size )
		{
			Data = new wchar_t [ Size * sizeof( wchar_t ) ];
			NumElements = 0x0;
			MaxElements = Size;
		}

		~FAllocatedString( )
		{
			if ( Data )
				delete[] Data;

			NumElements = 0x0;
			MaxElements = 0x0;
		}

	public:
		inline operator FString( ) { return *reinterpret_cast< FString* >( this ); }
		inline operator const FString( ) const { return *reinterpret_cast< const FString* >( this ); }
	};

	struct FVector
	{
		FVector( ) : X( ) , Y( ) , Z( ) { }
		FVector( double X , double Y , double Z ) : X( X ) , Y( Y ) , Z( Z ) { }

		FVector operator + ( const FVector& other ) const { return { this->X + other.X, this->Y + other.Y, this->Z + other.Z }; }
		FVector operator - ( const FVector& other ) const { return { this->X - other.X, this->Y - other.Y, this->Z - other.Z }; }
		FVector operator * ( double offset ) const { return { this->X * offset, this->Y * offset, this->Z * offset }; }
		FVector operator / ( double offset ) const { return { this->X / offset, this->Y / offset, this->Z / offset }; }

		FVector& operator *= ( const double other ) { this->X *= other; this->Y *= other; this->Z *= other; return *this; }
		FVector& operator /= ( const double other ) { this->X /= other; this->Y /= other; this->Z /= other; return *this; }

		FVector& operator = ( const FVector& other ) { this->X = other.X; this->Y = other.Y; this->Z = other.Z; return *this; }
		FVector& operator += ( const FVector& other ) { this->X += other.X; this->Y += other.Y; this->Z += other.Z; return *this; }
		FVector& operator -= ( const FVector& other ) { this->X -= other.X; this->Y -= other.Y; this->Z -= other.Z; return *this; }
		FVector& operator *= ( const FVector& other ) { this->X *= other.X; this->Y *= other.Y; this->Z *= other.Z; return *this; }
		FVector& operator /= ( const FVector& other ) { this->X /= other.X; this->Y /= other.Y; this->Z /= other.Z; return *this; }

		operator bool( ) { return bool( this->X || this->Y || this->Z ); }
		friend bool operator == ( const FVector& a , const FVector& b ) { return a.X == b.X && a.Y == b.Y && a.Z == b.Z; }
		friend bool operator != ( const FVector& a , const FVector& b ) { return !( a == b ); }

		double Dot( const FVector& V ) { return X * V.X + Y * V.Y + Z * V.Z; }
		double SizeSquared( ) { return X * X + Y * Y + Z * Z; }

		bool Normalize( )
		{
			while ( this->X > 180.0f )
			{
				this->X -= 360.0f;
			}
			while ( this->X < -180.0f )
			{
				this->X += 360.0f;
			}
			while ( this->Y > 180.0f )
			{
				this->Y -= 360.0f;
			}
			while ( this->Y < -180.0f )
			{
				this->Y += 360.0f;
			}

			this->Z = 0;
		}

		void Clamp( float Min , float Max )
		{
			if ( this->X < Min )
			{
				this->X = Min;
			}
			else if ( this->X > Max )
			{
				this->X = Max;
			}

			if ( this->Y < Min )
			{
				this->Y = Min;
			}
			else if ( this->Y > Max )
			{
				this->Y = Max;
			}

			this->Z = 0;
		}

		double X , Y , Z;
	};

	struct FVector2D
	{
		FVector2D( ) : X( ) , Y( ) { }
		FVector2D( double X , double Y ) : X( X ) , Y( Y ) { }

		FVector2D operator + ( const FVector2D& other ) const { return { this->X + other.X, this->Y + other.Y }; }
		FVector2D operator - ( const FVector2D& other ) const { return { this->X - other.X, this->Y - other.Y }; }
		FVector2D operator * ( double offset ) const { return { this->X * offset, this->Y * offset }; }
		FVector2D operator / ( double offset ) const { return { this->X / offset, this->Y / offset }; }

		FVector2D& operator *= ( const double other ) { this->X *= other; this->Y *= other; return *this; }
		FVector2D& operator /= ( const double other ) { this->X /= other; this->Y /= other; return *this; }

		FVector2D& operator = ( const FVector2D& other ) { this->X = other.X; this->Y = other.Y; return *this; }
		FVector2D& operator += ( const FVector2D& other ) { this->X += other.X; this->Y += other.Y; return *this; }
		FVector2D& operator -= ( const FVector2D& other ) { this->X -= other.X; this->Y -= other.Y; return *this; }
		FVector2D& operator *= ( const FVector2D& other ) { this->X *= other.X; this->Y *= other.Y; return *this; }
		FVector2D& operator /= ( const FVector2D& other ) { this->X /= other.X; this->Y /= other.Y; return *this; }

		operator bool( ) { return bool( this->X || this->Y ); }
		friend bool operator == ( const FVector2D& A , const FVector2D& B ) { return A.X == B.X && A.Y == A.Y; }
		friend bool operator != ( const FVector2D& A , const FVector2D& B ) { return !( A == B ); }

		double X , Y;
	};

	struct FRotator
	{
		FRotator( ) : Pitch( ) , Yaw( ) , Roll( ) { }
		FRotator( double Pitch , double Yaw , double Roll ) : Pitch( Pitch ) , Yaw( Yaw ) , Roll( Roll ) { }

		FRotator operator + ( const FRotator& other ) const { return { this->Pitch + other.Pitch, this->Yaw + other.Yaw, this->Roll + other.Roll }; }
		FRotator operator - ( const FRotator& other ) const { return { this->Pitch - other.Pitch, this->Yaw - other.Yaw, this->Roll - other.Roll }; }
		FRotator operator * ( double offset ) const { return { this->Pitch * offset, this->Yaw * offset, this->Roll * offset }; }
		FRotator operator / ( double offset ) const { return { this->Pitch / offset, this->Yaw / offset, this->Roll / offset }; }

		FRotator& operator *= ( const double other ) { this->Pitch *= other; this->Yaw *= other; this->Roll *= other; return *this; }
		FRotator& operator /= ( const double other ) { this->Pitch /= other; this->Yaw /= other; this->Roll /= other; return *this; }

		FRotator& operator = ( const FRotator& other ) { this->Pitch = other.Pitch; this->Yaw = other.Yaw; this->Roll = other.Roll; return *this; }
		FRotator& operator += ( const FRotator& other ) { this->Pitch += other.Pitch; this->Yaw += other.Yaw; this->Roll += other.Roll; return *this; }
		FRotator& operator -= ( const FRotator& other ) { this->Pitch -= other.Pitch; this->Yaw -= other.Yaw; this->Roll -= other.Roll; return *this; }
		FRotator& operator *= ( const FRotator& other ) { this->Pitch *= other.Pitch; this->Yaw *= other.Yaw; this->Roll *= other.Roll; return *this; }
		FRotator& operator /= ( const FRotator& other ) { this->Pitch /= other.Pitch; this->Yaw /= other.Yaw; this->Roll /= other.Roll; return *this; }

		operator bool( ) { return bool( this->Pitch || this->Yaw || this->Roll ); }
		friend bool operator == ( const FRotator& a , const FRotator& b ) { return a.Pitch == b.Pitch && a.Yaw == b.Yaw && a.Roll == b.Roll; }
		friend bool operator != ( const FRotator& a , const FRotator& b ) { return !( a == b ); }

		FRotator operator/( double Scalar )
		{
			return FRotator( this->Pitch / Scalar , this->Yaw / Scalar , this->Roll / Scalar );
		}

		FVector Euler( ) const
		{
			return FVector( Pitch , Yaw , Roll );
		}

		FRotator Normalize( )
		{
			while ( this->Yaw > 180.0 )
				this->Yaw -= 360.0;
			while ( this->Yaw < -180.0 )
				this->Yaw += 360.0;

			while ( this->Pitch > 180.0 )
				this->Pitch -= 360.0;
			while ( this->Pitch < -180.0 )
				this->Pitch += 360.0;

			this->Roll = 0.0;
			return *this;
		}

		double Pitch , Yaw , Roll;
	};

	struct FLinearColor final
	{
	public:
		float                                         R;                                                 // 0x0000(0x0004)(Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		float                                         G;                                                 // 0x0004(0x0004)(Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		float                                         B;                                                 // 0x0008(0x0004)(Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
		float                                         A;                                                 // 0x000C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	};

	float Pow22OneOver255Table[ 256 ] =
	{
		0.0f, 5.07705190066176E-06f, 2.33280046660989E-05f, 5.69217657121931E-05f, 0.000107187362341234f, 0.000175123977503027f, 0.000261543754548491f, 0.000367136269815943f, 0.000492503787191433f,
		0.000638182842167022f, 0.000804658499513058f, 0.000992374304074325f, 0.0012017395234384f, 0.00143313458967186f, 0.00168691531678928f, 0.00196341621339647f, 0.00226295316070643f,
		0.00258582559623417f, 0.00293231832393836f, 0.00330270303200364f, 0.00369723957890013f, 0.00411617709328275f, 0.00455975492252602f, 0.00502820345685554f, 0.00552174485023966f,
		0.00604059365484981f, 0.00658495738258168f, 0.00715503700457303f, 0.00775102739766061f, 0.00837311774514858f, 0.00902149189801213f, 0.00969632870165823f, 0.0103978022925553f,
		0.0111260823683832f, 0.0118813344348137f, 0.0126637200315821f, 0.0134733969401426f, 0.0143105193748841f, 0.0151752381596252f, 0.0160677008908869f, 0.01698805208925f, 0.0179364333399502f,
		0.0189129834237215f, 0.0199178384387857f, 0.0209511319147811f, 0.0220129949193365f, 0.0231035561579214f, 0.0242229420675342f, 0.0253712769047346f, 0.0265486828284729f, 0.027755279978126f,
		0.0289911865471078f, 0.0302565188523887f, 0.0315513914002264f, 0.0328759169483838f, 0.034230206565082f, 0.0356143696849188f, 0.0370285141619602f, 0.0384727463201946f, 0.0399471710015256f,
		0.0414518916114625f, 0.0429870101626571f, 0.0445526273164214f, 0.0461488424223509f, 0.0477757535561706f, 0.049433457555908f, 0.0511220500564934f, 0.052841625522879f, 0.0545922772817603f,
		0.0563740975519798f, 0.0581871774736854f, 0.0600316071363132f, 0.0619074756054558f, 0.0638148709486772f, 0.0657538802603301f, 0.0677245896854243f, 0.0697270844425988f, 0.0717614488462391f,
		0.0738277663277846f, 0.0759261194562648f, 0.0780565899581019f, 0.080219258736215f, 0.0824142058884592f, 0.0846415107254295f, 0.0869012517876603f, 0.0891935068623478f, 0.0915183529989195f,
		0.0938758665255778f, 0.0962661230633397f, 0.0986891975410945f, 0.1011451642096f, 0.103634096655137f, 0.106156067812744f, 0.108711149979039f, 0.11129941482466f, 0.113920933406333f,
		0.116575776178572f, 0.119264013005047f, 0.121985713169619f, 0.124740945387051f, 0.127529777813422f, 0.130352278056234f, 0.1332085131843f, 0.136098549737202f, 0.139023453734703f,
		0.141980290685736f, 0.144972125597231f, 0.147998022982685f, 0.151058046870511f, 0.154152260812165f, 0.157280727890073f, 0.160443510725344f, 0.16364067148529f, 0.166872271890766f,
		0.170138373223312f, 0.173439036332135f, 0.176774321640903f, 0.18014428915439f, 0.183548998464951f, 0.186988508758844f, 0.190462878823409f, 0.193972167048093f, 0.19751643144034f,
		0.201095729621346f, 0.204710118836677f, 0.208359655960767f, 0.212044397502288f, 0.215764399609395f, 0.219519718074868f, 0.223310408341127f, 0.227136525505149f, 0.230998124323267f,
		0.23489525921588f, 0.238827984272048f, 0.242796353254002f, 0.24680041960155f, 0.2508402364364f, 0.254915856566385f, 0.259027332489606f, 0.263174716398492f, 0.267358060183772f,
		0.271577415438375f, 0.275832833461245f, 0.280124365261085f, 0.284452061560024f, 0.288815972797219f, 0.293216149132375f, 0.297652640449211f, 0.302125496358853f, 0.306634766203158f,
		0.311180499057984f, 0.315762743736397f, 0.32038154879181f, 0.325036962521076f, 0.329729032967515f, 0.334457807923889f, 0.339223334935327f, 0.344025661302187f, 0.348864834082879f,
		0.353740900096629f, 0.358653905926199f, 0.363603897920553f, 0.368590922197487f, 0.373615024646202f, 0.37867625092984f, 0.383774646487975f, 0.388910256539059f, 0.394083126082829f,
		0.399293299902674f, 0.404540822567962f, 0.409825738436323f, 0.415148091655907f, 0.420507926167587f, 0.425905285707146f, 0.43134021380741f, 0.436812753800359f, 0.442322948819202f,
		0.44787084180041f, 0.453456475485731f, 0.45907989242416f, 0.46474113497389f, 0.470440245304218f, 0.47617726539744f, 0.481952237050698f, 0.487765201877811f, 0.493616201311074f,
		0.49950527660303f, 0.505432468828216f, 0.511397818884879f, 0.517401367496673f, 0.523443155214325f, 0.529523223417277f, 0.535641609315311f, 0.541798355950137f, 0.547993502196972f,
		0.554227087766085f, 0.560499152204328f, 0.566809734896638f, 0.573158875067523f, 0.579546611782525f, 0.585972983949661f, 0.592438030320847f, 0.598941789493296f, 0.605484299910907f,
		0.612065599865624f, 0.61868572749878f, 0.625344720802427f, 0.632042617620641f, 0.638779455650817f, 0.645555272344934f, 0.652370105410821f, 0.659223991813387f, 0.666116968775851f,
		0.673049073280942f, 0.680020342172095f, 0.687030812154625f, 0.694080519796882f, 0.701169501531402f, 0.708297793656032f, 0.715465432335048f, 0.722672453600255f, 0.729918893352071f,
		0.737204787360605f, 0.744530171266715f, 0.751895080583051f, 0.759299550695091f, 0.766743616862161f, 0.774227314218442f, 0.781750677773962f, 0.789313742415586f, 0.796916542907978f,
		0.804559113894567f, 0.81234148989849f, 0.819963705323528f, 0.827725794455034f, 0.835527791460841f, 0.843369730392169f, 0.851251645184515f, 0.859173569658532f, 0.867135537520905f,
		0.875137582365205f, 0.883179737672745f, 0.891262036813419f, 0.899384513046529f, 0.907547199521614f, 0.915750129279253f, 0.923993335251873f, 0.932276850264543f, 0.940600707035753f,
		0.948964938178195f, 0.957369576199527f, 0.96581465350313f, 0.974300202388861f, 0.982826255053791f, 0.99139284359294f, 1.0f
	};

	FLinearColor FromRGB( int r , int g , int b )
	{
		FLinearColor LinearColor;
		LinearColor.R = Pow22OneOver255Table[ r ];
		LinearColor.G = Pow22OneOver255Table[ g ];
		LinearColor.B = Pow22OneOver255Table[ b ];
		LinearColor.A = 1.f;
		return LinearColor;
	}

	struct FPlane : public FVector
	{
		FPlane( ) : W( ) { }
		FPlane( double W ) : W( W ) { }

		double W;
	};

	struct FMatrix
	{
		FMatrix( ) : XPlane( ) , YPlane( ) , ZPlane( ) , WPlane( ) { }
		FMatrix( FPlane XPlane , FPlane YPlane , FPlane ZPlane , FPlane WPlane ) : XPlane( XPlane ) , YPlane( YPlane ) , ZPlane( ZPlane ) , WPlane( WPlane ) { }

		FPlane XPlane , YPlane , ZPlane , WPlane;
	};

	struct FName
	{
		FName( ) : Index( ) { }
		FName( int Index ) : Index( Index ) { }

		operator bool( ) { return bool( this->Index ); }
		friend bool operator	== ( const FName& a , const FName& b ) { return a.Index == b.Index; }
		friend bool operator	!= ( const FName& a , const FName& b ) { return !( a == b ); }

		uint32_t Index;
		uint32_t Number;
	};

	class FTextData
	{
	public:
		char Details[ 0x28 ];
		FString String;
	};

	struct FText
	{
		FTextData* Data;

		FString Get( )
		{
			if ( this->Data )
			{
				return Data->String;
			}

			return nullptr;
		}
	};

	struct FKey
	{
		FName KeyName;
		char Details[ 0x10 ];
	};

	struct FHitResult
	{
		unsigned char UnknownData69[ 0x4 ];
		int32_t FaceIndex; // 0x00(0x04)
		float Time; // 0x04(0x04)
		float Distance; // 0x08(0x04)
		char pad_C[ 0x4 ]; // 0x0c(0x04)
		struct FVector Location; // 0x10(0x18)
		struct FVector ImpactPoint; // 0x28(0x18)
		struct FVector Normal; // 0x40(0x18)
		struct FVector ImpactNormal; // 0x58(0x18)
		struct FVector TraceStart; // 0x70(0x18)
		struct FVector TraceEnd; // 0x88(0x18)
		float PenetrationDepth; // 0xa0(0x04)
		int32_t MyItem; // 0xa4(0x04)
		int32_t Item; // 0xa8(0x04)
		char ElementIndex; // 0xac(0x01)
		char bBlockingHit : 1; // 0xad(0x01)
		char bStartPenetrating : 1; // 0xad(0x01)
		char pad_AD_2 : 6; // 0xad(0x01)
		char pad_AE[ 0x2 ]; // 0xae(0x02)
		void* PhysMaterial; // 0xb0(0x08)
		void* HitObjectHandle; // 0xb8(0x20)
		void* Component; // 0xd8(0x08)
		char pad_E0[ 0x8 ]; // 0xe0(0x08)
		struct FName BoneName; // 0xe8(0x04)
		struct FName MyBoneName; // 0xec(0x04)
	};

	template<class TEnum>
	class TEnumAsByte
	{
	public:
		inline TEnumAsByte( )
		{
		}

		inline TEnumAsByte( TEnum _value )
			: value( static_cast< uint8_t >( _value ) )
		{
		}

		explicit inline TEnumAsByte( int32_t _value )
			: value( static_cast< uint8_t >( _value ) )
		{
		}

		explicit inline TEnumAsByte( uint8_t _value )
			: value( _value )
		{
		}

		inline operator TEnum( ) const
		{
			return ( TEnum ) value;
		}

		inline TEnum GetValue( ) const
		{
			return ( TEnum ) value;
		}

	private:
		uint8_t value;
	};


	class FWeakObjectPtr
	{
	public:
		uint32_t                                         ObjectIndex;                                       // 0x0000(0x0004)(NOT AUTO-GENERATED PROPERTY)
		uint32_t                                         ObjectSerialNumber;                                // 0x0004(0x0004)(NOT AUTO-GENERATED PROPERTY)

	public:
		class UObject* Get( );
		class UObject* operator->( ) const;
		bool operator==( const FWeakObjectPtr& Other ) const;
		bool operator!=( const FWeakObjectPtr& Other ) const;
		bool operator==( const class UObject* Other ) const;
		bool operator!=( const class UObject* Other ) const;
	};

	template<typename UEType>
	class TWeakObjectPtr : public FWeakObjectPtr
	{
	public:
		UEType* Get( )
		{
			return static_cast< UEType* >( FWeakObjectPtr::Get( ) );
		}

		UEType* operator->( )
		{
			return static_cast< UEType* >( FWeakObjectPtr::Get( ) );
		}
	};

	template<typename TObjectID>
	class TPersistentObjectPtr
	{
	public:
		FWeakObjectPtr                                WeakPtr;                                           // 0x0000(0x0008)(NOT AUTO-GENERATED PROPERTY)
		TObjectID                                     ObjectID;                                          // 0x0008(0x0000)(NOT AUTO-GENERATED PROPERTY)

	public:
		class UObject* Get( )
		{
			return WeakPtr.Get( );
		}
		class UObject* operator->( ) const
		{
			return WeakPtr.Get( );
		}
	};

	struct FSoftObjectPath
	{
	public:
		FName AssetPathName;
		FString SubPathString;
	};

	class FSoftObjectPtr : public TPersistentObjectPtr<FSoftObjectPath>
	{
	};

	template<typename UEType>
	class TSoftObjectPtr : public FSoftObjectPtr
	{
	public:
		UEType* Get( )
		{
			return static_cast< UEType* >( TPersistentObjectPtr::Get( ) );
		}
		UEType* operator->( ) const
		{
			return static_cast< UEType* >( TPersistentObjectPtr::Get( ) );
		}
	};

	struct FGuid
	{
		int32_t A; // 0x00(0x04)
		int32_t B; // 0x04(0x04)
		int32_t C; // 0x08(0x04)
		int32_t D; // 0x0c(0x04)
	};

	struct FRankedProgressReplicatedData
	{
		FString RankType; // 0x00(0x10)
		int32_t Rank; // 0x10(0x04)
		char pad_14[ 0x4 ]; // 0x14(0x04)
	};

	struct FBatchedThickLines
	{
		FVector Start;
		FVector End;
		float Thickness;
		FLinearColor Color;
		FLinearColor HitProxyColor;
		float DepthBias;
		uint32 bScreenSpace;
	};

	// ENUMS

	enum class EFortWeaponCoreAnimation : uint8
	{
		Melee = 0 ,
		Pistol = 1 ,
		Shotgun = 2 ,
		PaperBlueprint = 3 ,
		Rifle = 4 ,
		MeleeOneHand = 5 ,
		MachinePistol = 6 ,
		RocketLauncher = 7 ,
		GrenadeLauncher = 8 ,
		GoingCommando = 9 ,
		AssaultRifle = 10 ,
		TacticalShotgun = 11 ,
		SniperRifle = 12 ,
		TrapPlacement = 13 ,
		ShoulderLauncher = 14 ,
		AbilityDecoTool = 15 ,
		Crossbow = 16 ,
		C4 = 17 ,
		RemoteControl = 18 ,
		DualWield = 19 ,
		AR_BullPup = 20 ,
		AR_ForwardGrip = 21 ,
		MedPackPaddles = 22 ,
		SMG_P90 = 23 ,
		AR_DrumGun = 24 ,
		Consumable_Small = 25 ,
		Consumable_Large = 26 ,
		Balloon = 27 ,
		MountedTurret = 28 ,
		CreativeTool = 29 ,
		ExplosiveBow = 30 ,
		AshtonIndigo = 31 ,
		AshtonChicago = 32 ,
		MeleeDualWield = 33 ,
		Unarmed = 34 ,
		MAX = 35
	};

	enum class EFortItemTier : uint8
	{
		No_Tier = 0 ,
		I = 1 ,
		II = 2 ,
		III = 3 ,
		IV = 4 ,
		V = 5 ,
		VI = 6 ,
		VII = 7 ,
		VIII = 8 ,
		IX = 9 ,
		X = 10 ,
		NumItemTierValues = 11 ,
		EFortItemTier_MAX = 12
	};

	enum EFortRarity : uint8_t
	{
		Common = 0 ,
		Uncommon = 1 ,
		Rare = 2 ,
		Epic = 3 ,
		Legendary = 4 ,
		Mythic = 5 ,
		Transcendent = 6 ,
		Unattainable = 7 ,
		NumRarityValues = 8 ,
		EFortRarity_MAX = 9
	};

	enum class ECollisionChannel : uint8_t
	{
		ECC_WorldStatic = 0 ,
		ECC_WorldDynamic = 1 ,
		ECC_Pawn = 2 ,
		ECC_Visibility = 3 ,
		ECC_Camera = 4 ,
		ECC_PhysicsBody = 5 ,
		ECC_Vehicle = 6 ,
		ECC_Destructible = 7 ,
		ECC_EngineTraceChannel1 = 8 ,
		ECC_EngineTraceChannel2 = 9 ,
		ECC_EngineTraceChannel3 = 10 ,
		ECC_EngineTraceChannel4 = 11 ,
		ECC_EngineTraceChannel5 = 12 ,
		ECC_EngineTraceChannel6 = 13 ,
		ECC_GameTraceChannel1 = 14 ,
		ECC_GameTraceChannel2 = 15 ,
		ECC_GameTraceChannel3 = 16 ,
		ECC_GameTraceChannel4 = 17 ,
		ECC_GameTraceChannel5 = 18 ,
		ECC_GameTraceChannel6 = 19 ,
		ECC_GameTraceChannel7 = 20 ,
		ECC_GameTraceChannel8 = 21 ,
		ECC_GameTraceChannel9 = 22 ,
		ECC_GameTraceChannel10 = 23 ,
		ECC_GameTraceChannel11 = 24 ,
		ECC_GameTraceChannel12 = 25 ,
		ECC_GameTraceChannel13 = 26 ,
		ECC_GameTraceChannel14 = 27 ,
		ECC_GameTraceChannel15 = 28 ,
		ECC_GameTraceChannel16 = 29 ,
		ECC_GameTraceChannel17 = 30 ,
		ECC_GameTraceChannel18 = 31 ,
		ECC_OverlapAll_Deprecated = 32 ,
		ECC_MAX = 33
	};

	enum class ETraceTypeQuery : uint8
	{
		TraceTypeQuery1 = 0 ,
		TraceTypeQuery2 = 1 ,
		TraceTypeQuery3 = 2 ,
		TraceTypeQuery4 = 3 ,
		TraceTypeQuery5 = 4 ,
		TraceTypeQuery6 = 5 ,
		TraceTypeQuery7 = 6 ,
		TraceTypeQuery8 = 7 ,
		TraceTypeQuery9 = 8 ,
		TraceTypeQuery10 = 9 ,
		TraceTypeQuery11 = 10 ,
		TraceTypeQuery12 = 11 ,
		TraceTypeQuery13 = 12 ,
		TraceTypeQuery14 = 13 ,
		TraceTypeQuery15 = 14 ,
		TraceTypeQuery16 = 15 ,
		TraceTypeQuery17 = 16 ,
		TraceTypeQuery18 = 17 ,
		TraceTypeQuery19 = 18 ,
		TraceTypeQuery20 = 19 ,
		TraceTypeQuery21 = 20 ,
		TraceTypeQuery22 = 21 ,
		TraceTypeQuery23 = 22 ,
		TraceTypeQuery24 = 23 ,
		TraceTypeQuery25 = 24 ,
		TraceTypeQuery26 = 25 ,
		TraceTypeQuery27 = 26 ,
		TraceTypeQuery28 = 27 ,
		TraceTypeQuery29 = 28 ,
		TraceTypeQuery30 = 29 ,
		TraceTypeQuery31 = 30 ,
		TraceTypeQuery32 = 31 ,
		TraceTypeQuery_MAX = 32 ,
		ETraceTypeQuery_MAX = 33 ,
	};

	enum class EDrawDebugTrace : uint8
	{
		None = 0 ,
		ForOneFrame = 1 ,
		ForDuration = 2 ,
		Persistent = 3 ,
		EDrawDebugTrace_MAX = 4 ,
	};

	enum class EBlendMode : uint8
	{
		BLEND_Opaque = 0 ,
		BLEND_Masked = 1 ,
		BLEND_Translucent = 2 ,
		BLEND_Additive = 3 ,
		BLEND_Modulate = 4 ,
		BLEND_AlphaComposite = 5 ,
		BLEND_AlphaHoldout = 6 ,
		BLEND_TranslucentColoredTransmittance = 7 ,
		BLEND_MAX = 8 ,
		BLEND_TranslucentGreyTransmittance = 2 ,
		BLEND_ColoredTransmittanceOnly = 4
	};

	enum class EDecalBlendMode : uint8
	{
		DBM_Translucent = 0 ,
		DBM_Stain = 1 ,
		DBM_Normal = 2 ,
		DBM_Emissive = 3 ,
		DBM_DBuffer_ColorNormalRoughness = 4 ,
		DBM_DBuffer_Color = 5 ,
		DBM_DBuffer_ColorNormal = 6 ,
		DBM_DBuffer_ColorRoughness = 7 ,
		DBM_DBuffer_Normal = 8 ,
		DBM_DBuffer_NormalRoughness = 9 ,
		DBM_DBuffer_Roughness = 10 ,
		DBM_DBuffer_Emissive = 11 ,
		DBM_DBuffer_AlphaComposite = 12 ,
		DBM_DBuffer_EmissiveAlphaComposite = 13 ,
		DBM_Volumetric_DistanceFunction = 14 ,
		DBM_AlphaComposite = 15 ,
		DBM_AmbientOcclusion = 16 ,
		DBM_MAX = 17
	};

	enum class EElementType
	{
		ET_Box ,
		ET_DebugQuad ,
		ET_Text ,
		ET_ShapedText ,
		ET_Spline ,
		ET_Line ,
		ET_Gradient ,
		ET_Viewport ,
		ET_Border ,
		ET_Custom ,
		ET_CustomVerts ,
		ET_PostProcessPass ,
		ET_Count ,
	};

	enum class ESimpleElementBlendMode
	{
		SE_BLEND_Opaque = 0 ,
		SE_BLEND_Masked ,
		SE_BLEND_Translucent ,
		SE_BLEND_Additive ,
		SE_BLEND_Modulate ,
		SE_BLEND_MaskedDistanceField ,
		SE_BLEND_MaskedDistanceFieldShadowed ,
		SE_BLEND_TranslucentDistanceField ,
		SE_BLEND_TranslucentDistanceFieldShadowed ,
		SE_BLEND_AlphaComposite ,
		SE_BLEND_AlphaHoldout ,
		SE_BLEND_AlphaBlend ,
		SE_BLEND_TranslucentAlphaOnly ,
		SE_BLEND_TranslucentAlphaOnlyWriteAlpha ,
		SE_BLEND_RGBA_MASK_START ,
		SE_BLEND_RGBA_MASK_END = SE_BLEND_RGBA_MASK_START + 31 ,
		SE_BLEND_MAX ,
	};

	enum class ENetworkSmoothingMode : uint8_t
	{
		Disabled ,
		Linear ,
		Exponential ,
		Replay ,
	};

	enum class EAutoPossessAI : uint8
	{
		Disabled = 0 ,
		PlacedInWorld = 1 ,
		Spawned = 2 ,
		PlacedInWorldOrSpawned = 3 ,
		EAutoPossessAI_MAX = 4 ,
	};

	enum class EMovementMode : uint8
	{
		MOVE_None = 0 ,
		MOVE_Walking = 1 ,
		MOVE_NavWalking = 2 ,
		MOVE_Falling = 3 ,
		MOVE_Swimming = 4 ,
		MOVE_Flying = 5 ,
		MOVE_Custom = 6 ,
		MOVE_MAX = 7 ,
	};

	enum class ENetDormancy : uint8
	{
		DORM_Never = 0 ,
		DORM_Awake = 1 ,
		DORM_DormantAll = 2 ,
		DORM_DormantPartial = 3 ,
		DORM_Initial = 4 ,
		DORM_MAX = 5 ,
	};

	enum class EObjectFlags : uint32_t
	{
		RF_NoFlags = 0 ,
		RF_Public = 1 ,
		RF_Standalone = 2 ,
		RF_MarkAsNative = 4 ,
		RF_Transactional = 8 ,
		RF_ClassDefaultObject = 16 ,
		RF_ArchetypeObject = 32 ,
		RF_Transient = 64 ,
		RF_MarkAsRootSet = 128 ,
		RF_TagGarbageTemp = 256 ,
		RF_NeedInitialization = 512 ,
		RF_NeedLoad = 1024 ,
		RF_KeepForCooker = 2048 ,
		RF_NeedPostLoad = 4096 ,
		RF_NeedPostLoadSubobjects = 8192 ,
		RF_NewerVersionExists = 16384 ,
		RF_BeginDestroyed = 32768 ,
		RF_FinishDestroyed = 65536 ,
		RF_BeingRegenerated = 131072 ,
		RF_DefaultSubObject = 262144 ,
		RF_WasLoaded = 524288 ,
		RF_TextExportTransient = 1048576 ,
		RF_LoadCompleted = 2097152 ,
		RF_InheritableComponentTemplate = 4194304 ,
		RF_DuplicateTransient = 8388608 ,
		RF_StrongRefOnFrame = 16777216 ,
		RF_NonPIEDuplicateTransient = 33554432 ,
		RF_Dynamic = 67108864 ,
		RF_WillBeLoaded = 134217728
	};

	enum class EFortKickReason : uint8
	{
		NotKicked = 0 ,
		GenericKick = 1 ,
		WasBanned = 2 ,
		EncryptionRequired = 3 ,
		CrossPlayRestriction = 4 ,
		ClientIdRestriction = 5 ,
		EFortKickReason_MAX = 6
	};

	enum class EFortBuildingType : uint8
	{
		Wall = 0 ,
		Floor = 1 ,
		Corner = 2 ,
		Deco = 3 ,
		Prop = 4 ,
		Stairs = 5 ,
		Roof = 6 ,
		Pillar = 7 ,
		SpawnedItem = 8 ,
		Container = 9 ,
		Trap = 10 ,
		GenericCenterCellActor = 11 ,
		StructuralCorner = 12 ,
		None = 13 ,
		EFortBuildingType_MAX = 14 ,
	};

	enum class EClassCastFlags : uint64
	{
		None = 0x0000000000000000 ,

		Field = 0x0000000000000001 ,
		Int8Property = 0x0000000000000002 ,
		Enum = 0x0000000000000004 ,
		Struct = 0x0000000000000008 ,
		ScriptStruct = 0x0000000000000010 ,
		Class = 0x0000000000000020 ,
		ByteProperty = 0x0000000000000040 ,
		IntProperty = 0x0000000000000080 ,
		FloatProperty = 0x0000000000000100 ,
		UInt64Property = 0x0000000000000200 ,
		ClassProperty = 0x0000000000000400 ,
		UInt32Property = 0x0000000000000800 ,
		InterfaceProperty = 0x0000000000001000 ,
		NameProperty = 0x0000000000002000 ,
		StrProperty = 0x0000000000004000 ,
		Property = 0x0000000000008000 ,
		ObjectProperty = 0x0000000000010000 ,
		BoolProperty = 0x0000000000020000 ,
		UInt16Property = 0x0000000000040000 ,
		Function = 0x0000000000080000 ,
		StructProperty = 0x0000000000100000 ,
		ArrayProperty = 0x0000000000200000 ,
		Int64Property = 0x0000000000400000 ,
		DelegateProperty = 0x0000000000800000 ,
		NumericProperty = 0x0000000001000000 ,
		MulticastDelegateProperty = 0x0000000002000000 ,
		ObjectPropertyBase = 0x0000000004000000 ,
		WeakObjectProperty = 0x0000000008000000 ,
		LazyObjectProperty = 0x0000000010000000 ,
		SoftObjectProperty = 0x0000000020000000 ,
		TextProperty = 0x0000000040000000 ,
		Int16Property = 0x0000000080000000 ,
		DoubleProperty = 0x0000000100000000 ,
		SoftClassProperty = 0x0000000200000000 ,
		Package = 0x0000000400000000 ,
		Level = 0x0000000800000000 ,
		Actor = 0x0000001000000000 ,
		PlayerController = 0x0000002000000000 ,
		Pawn = 0x0000004000000000 ,
		SceneComponent = 0x0000008000000000 ,
		PrimitiveComponent = 0x0000010000000000 ,
		SkinnedMeshComponent = 0x0000020000000000 ,
		SkeletalMeshComponent = 0x0000040000000000 ,
		Blueprint = 0x0000080000000000 ,
		DelegateFunction = 0x0000100000000000 ,
		StaticMeshComponent = 0x0000200000000000 ,
		MapProperty = 0x0000400000000000 ,
		SetProperty = 0x0000800000000000 ,
		EnumProperty = 0x0001000000000000 ,
		USparseDelegateFunction = 0x0002000000000000 ,
		FMulticastInlineDelegateProperty = 0x0004000000000000 ,
		FMulticastSparseDelegateProperty = 0x0008000000000000 ,
		FFieldPathProperty = 0x0010000000000000 ,
		FLargeWorldCoordinatesRealProperty = 0x0080000000000000 ,
		FOptionalProperty = 0x0100000000000000 ,
		FVValueProperty = 0x0200000000000000 ,
		UVerseVMClass = 0x0400000000000000 ,
		FVRestValueProperty = 0x0800000000000000 ,
	};

	enum class EFunctionFlags : uint32
	{
		None = 0x00000000 ,

		Final = 0x00000001 ,
		RequiredAPI = 0x00000002 ,
		BlueprintAuthorityOnly = 0x00000004 ,
		BlueprintCosmetic = 0x00000008 ,
		Net = 0x00000040 ,
		NetReliable = 0x00000080 ,
		NetRequest = 0x00000100 ,
		Exec = 0x00000200 ,
		Native = 0x00000400 ,
		Event = 0x00000800 ,
		NetResponse = 0x00001000 ,
		Static = 0x00002000 ,
		NetMulticast = 0x00004000 ,
		UbergraphFunction = 0x00008000 ,
		MulticastDelegate = 0x00010000 ,
		Public = 0x00020000 ,
		Private = 0x00040000 ,
		Protected = 0x00080000 ,
		Delegate = 0x00100000 ,
		NetServer = 0x00200000 ,
		HasOutParms = 0x00400000 ,
		HasDefaults = 0x00800000 ,
		NetClient = 0x01000000 ,
		DLLImport = 0x02000000 ,
		BlueprintCallable = 0x04000000 ,
		BlueprintEvent = 0x08000000 ,
		BlueprintPure = 0x10000000 ,
		EditorOnly = 0x20000000 ,
		Const = 0x40000000 ,
		NetValidate = 0x80000000 ,

		AllFlags = 0xFFFFFFFF ,
	};
}