#pragma once
#define DLL_PROCESS_ATTACH 1
#define DLL_THREAD_ATTACH 2
#define DLL_THREAD_DETACH 3
#define DLL_PROCESS_DETACH 0

#define M_PI 3.14159265358979323846
#define DBL_MAX 1.7976931348623158e+308
#define DBL_MIN 2.2250738585072014e-308
#define FLT_MAX 3.402823466e+38F
#define FLT_MIN 1.175494351e-38F
#define INT_MAX 2147483647
#define INT_MIN (-2147483647 - 1)
#define INT32_MIN (-2147483647i32 - 1)

typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int* PUINT;

typedef unsigned __int64   uintptr_t;
typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;
typedef unsigned __int64   size_t;

typedef signed char        int_least8_t;
typedef short              int_least16_t;
typedef int                int_least32_t;
typedef long long          int_least64_t;
typedef unsigned char      uint_least8_t;
typedef unsigned short     uint_least16_t;
typedef unsigned int       uint_least32_t;
typedef unsigned long long uint_least64_t;

typedef signed char        int_fast8_t;
typedef int                int_fast16_t;
typedef int                int_fast32_t;
typedef long long          int_fast64_t;
typedef unsigned char      uint_fast8_t;
typedef unsigned int       uint_fast16_t;
typedef unsigned int       uint_fast32_t;
typedef unsigned long long uint_fast64_t;

typedef __int8 int8;
typedef __int16 int16;
typedef __int32 int32;
typedef __int64 int64;
typedef unsigned __int8 uint8;
typedef unsigned __int16 uint16;
typedef unsigned __int32 uint32;
typedef unsigned __int64 uint64;

typedef long long          intmax_t;
typedef unsigned long long uintmax_t;
typedef void* PVOID;
typedef unsigned long ULONG;

typedef char* PCHAR;

typedef uint64_t ULONG_PTR;
//typedef char TCHAR;

typedef struct _ImageFileHeader
{
	WORD Machine;
	WORD NumberOfSections;
	DWORD TimeDateStamp;
	DWORD PointerToSymbolTable;
	DWORD NumberOfSymbols;
	WORD SizeOfOptionalHeader;
	WORD Characteristics;
} ImageFileHeader, * PImageFileHeader;

struct ImageDataDirectory
{
	unsigned long virtualAddress;
	unsigned long size;
};

typedef struct _ImageOptionalHeader64
{
	WORD                 Magic;
	BYTE                 MajorLinkerVersion;
	BYTE                 MinorLinkerVersion;
	DWORD                SizeOfCode;
	DWORD                SizeOfInitializedData;
	DWORD                SizeOfUninitializedData;
	DWORD                AddressOfEntryPoint;
	DWORD                BaseOfCode;
	uintptr_t            ImageBase;
	DWORD                SectionAlignment;
	DWORD                FileAlignment;
	WORD                 MajorOperatingSystemVersion;
	WORD                 MinorOperatingSystemVersion;
	WORD                 MajorImageVersion;
	WORD                 MinorImageVersion;
	WORD                 MajorSubsystemVersion;
	WORD                 MinorSubsystemVersion;
	DWORD                Win32VersionValue;
	DWORD                SizeOfImage;
	DWORD                SizeOfHeaders;
	DWORD                CheckSum;
	WORD                 Subsystem;
	WORD                 DllCharacteristics;
	uintptr_t            SizeOfStackReserve;
	uintptr_t            SizeOfStackCommit;
	uintptr_t            SizeOfHeapReserve;
	uintptr_t            SizeOfHeapCommit;
	DWORD                LoaderFlags;
	DWORD                NumberOfRvaAndSizes;
	ImageDataDirectory datadirectory[16];
} ImageOptionalHeader64, * PImageOptionalHeader64;

//typedef struct _IMAGE_DOS_HEADER
//{
//	WORD e_magic;
//	WORD e_cblp;
//	WORD e_cp;
//	WORD e_crlc;
//	WORD e_cparhdr;
//	WORD e_minalloc;
//	WORD e_maxalloc;
//	WORD e_ss;
//	WORD e_sp;
//	WORD e_csum;
//	WORD e_ip;
//	WORD e_cs;
//	WORD e_lfarlc;
//	WORD e_ovno;
//	WORD e_res[4];
//	WORD e_oemid;
//	WORD e_oeminfo;
//	WORD e_res2[10];
//	long e_lfanew;
//} IMAGE_DOS_HEADER, * PIMAGE_DOS_HEADER;
//
//typedef struct _IMAGE_NT_HEADERS
//{
//	DWORD Signature;
//	ImageFileHeader FileHeader;
//	ImageOptionalHeader64 OptionalHeader;
//} IMAGE_NT_HEADERS, * PIMAGE_NT_HEADERS;