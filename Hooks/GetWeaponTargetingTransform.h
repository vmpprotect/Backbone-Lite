#pragma once

double* ( *GetWeaponTargetingTransformOriginal )( SDK::AFortWeapon* , double* , double* );
double* GetWeaponTargetingTransform( SDK::AFortWeapon* CurrentWeapon , double* StartLocation , double* Angles )
{
	double* ReturnValue = GetWeaponTargetingTransformOriginal( CurrentWeapon , StartLocation , Angles );

	if ( Settings::SilentAim && ( Implementation::bSilentAimActive && Implementation::SilentAimLocationTarget ) )
	{
		Angles[ 0 ] = Implementation::SilentAimLocationTarget.X - StartLocation[ 0 ];
		Angles[ 1 ] = Implementation::SilentAimLocationTarget.Y - StartLocation[ 1 ];
		Angles[ 2 ] = Implementation::SilentAimLocationTarget.Z - StartLocation[ 2 ];
	}

	return ReturnValue;
}