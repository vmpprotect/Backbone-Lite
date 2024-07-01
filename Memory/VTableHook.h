#pragma once

class ShadowVMT
{
public:
	template <typename Type>
	bool Hook( SDK::UObject* Address, int Index, void* Function, Type* Original )
	{
		this->VirtualTable = *( uintptr_t** ) ( Address );

		// Check if the virtual table wasn't the last hooked function
		if ( this->LastHookedFunctionAddress && this->LastHookedFunctionIndex )
		{
			if ( this->LastHookedFunctionAddress == this->VirtualTable[ this->LastHookedFunctionIndex ] )
			{
				return false;
			}
		}

		// Check if the virtual table isn't already hooked
		if ( reinterpret_cast< void* >( this->VirtualTable[ Index ] ) != Function )
		{
			while ( this->VirtualTable[ this->VTableSize ] )
			{
				this->VTableSize++;
			}

			// Check if the virtual table is contained in the virtual function table
			if ( Index < this->VTableSize )
			{
				// Allocate memory for the fake virtual table
				this->AllocatedVTable = reinterpret_cast< uintptr_t* >( SDK::FMemory::Malloc( this->VTableSize * sizeof( uintptr_t ) , 0x10 ) );

				// Copy the virtual table's contents to the fake virtual table
				for ( int i = 0; i < this->VTableSize; i++ )
				{
					this->AllocatedVTable[ i ] = this->VirtualTable[ i ];
				}

				*Original = reinterpret_cast< Type >( this->VirtualTable[ Index ] );

				// Replace the target function with our function in the fake virtual table
				this->AllocatedVTable[ Index ] = reinterpret_cast< uintptr_t >( Function );

				// Write the target virtual table to our fake virtual table
				*( uintptr_t** ) ( Address ) = this->AllocatedVTable;

				// Pushback data
				this->LastHookedFunctionAddress = reinterpret_cast< uintptr_t >( Function );
				this->LastHookedFunctionIndex = Index;

				return true;
			}
		}

		return false;
	}

	template <typename Type>
	void Unhook( SDK::UObject* Address , Type* Original )
	{
		if ( this->VirtualTable && this->LastHookedFunctionIndex )
		{
			// Get the our fake virtual table
			uintptr_t* VirtualTable = *( uintptr_t** ) ( Address );

			// Restore the last hooked function in our fake virtual table with the original
			VirtualTable[ this->LastHookedFunctionIndex ] = reinterpret_cast< uintptr_t >( *Original );

			// Write the target virtual table with the old virtual table
			*( uintptr_t** ) Address = VirtualTable;

			// Free fake virtual table for memory leaks
			SDK::FMemory::Free( VirtualTable );

			this->LastHookedFunctionAddress = 0x0;
			this->LastHookedFunctionIndex = -1;
		}
	}

private:
	uintptr_t* VirtualTable;
	uintptr_t* AllocatedVTable;
	int VTableSize;

	uintptr_t LastHookedFunctionAddress;
	int LastHookedFunctionIndex;
};