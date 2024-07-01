#pragma once

float ( *GetSearchTimeOriginal )( SDK::ABuildingActor* );
float GetSearchTime( SDK::ABuildingActor* ContainerActor )
{
	float ReturnValue = GetSearchTimeOriginal( ContainerActor );

	if ( Settings::InstantSearch )
	{
		return FLT_MAX;
	}

	return ReturnValue;
}