#pragma once

namespace Humanization
{
    void AddNoise( SDK::FRotator* Rotation , float NoiseAmount )
    {
        SDK::FRotator Out = *Rotation;
        Out.Pitch += SDK::MathLibrary->RandomFloatInRange( -NoiseAmount , NoiseAmount );
        Out.Yaw += SDK::MathLibrary->RandomFloatInRange( -NoiseAmount , NoiseAmount );
        Out.Roll = 0.0;
        *Rotation = Out;
    }

    float EaseOutCubic( float t )
    {
        return 1 - SDK::MathLibrary->Pow( 1 - t , 3 );
    }

	SDK::FRotator SmoothMe( SDK::FRotator startRotation , SDK::FRotator endRotation , float SmoothScale )
	{
		SDK::FRotator ret = endRotation;

		ret.Pitch -= startRotation.Pitch;
		ret.Yaw -= startRotation.Yaw;

		//clamp
		if ( ret.Yaw < -180.0f )
			ret.Yaw += 360.0f;

		if ( ret.Yaw > 180.0f )
			ret.Yaw -= 360.0f;

		if ( ret.Pitch < -74.0f )
			ret.Pitch = -74.0f;

		if ( ret.Pitch > 74.0f )
			ret.Pitch = 74.0f;

		ret.Pitch = ( ret.Pitch / SmoothScale ) + startRotation.Pitch;
		ret.Yaw = ( ret.Yaw / SmoothScale ) + startRotation.Yaw;

		//clamp
		if ( ret.Yaw < -180.0f )
			ret.Yaw += 360.0f;

		if ( ret.Yaw > 180.0f )
			ret.Yaw -= 360.0f;

		if ( ret.Pitch < -74.0f )
			ret.Pitch = -74.0f;

		if ( ret.Pitch > 74.0f )
			ret.Pitch = 74.0f;

		ret.Roll = 0;

		return ret;
	}
}