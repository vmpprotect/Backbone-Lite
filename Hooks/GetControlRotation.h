#pragma once

SDK::FRotator* ( *GetControlRotationOriginal )( SDK::APlayerController* , SDK::FRotator* );
SDK::FRotator* GetControlRotation( SDK::APlayerController* PlayerController , SDK::FRotator* Rotation )
{
	GetControlRotationOriginal( PlayerController , Rotation );

	if ( Implementation::bAimbotActive && Implementation::AimbotRotationTarget )
	{
		*Rotation = Implementation::AimbotRotationTarget;
	}

	return Rotation;
}