#pragma once

namespace Radar
{
	void Range( double* X , double* Y , float range )
	{
		if ( SDK::MathLibrary->abs( ( *X ) ) > range || SDK::MathLibrary->abs( ( *Y ) ) > range )
		{
			if ( ( *Y ) > ( *X ) )
			{
				if ( ( *Y ) > -( *X ) )
				{
					( *X ) = range * ( *X ) / ( *Y );
					( *Y ) = range;
				}
				else
				{
					( *Y ) = -range * ( *Y ) / ( *X );
					( *X ) = -range;
				}
			}
			else
			{
				if ( ( *Y ) > -( *X ) )
				{
					( *Y ) = range * ( *Y ) / ( *X );
					( *X ) = range;
				}
				else
				{
					( *X ) = -range * ( *X ) / ( *Y );
					( *Y ) = -range;
				}
			}
		}
	}

	void RotatePoint( SDK::FVector2D* Screen , SDK::FVector Origin , SDK::FVector CameraLocation , SDK::FRotator CameraRotation , SDK::FVector2D Position , SDK::FVector2D Size )
	{
		auto Yaw = CameraRotation.Yaw * 3.1415927 / 180;

		double dx = Origin.X - CameraLocation.X;
		double dy = Origin.Y - CameraLocation.Y;

		double fsin_yaw = SDK::MathLibrary->sin( Yaw );
		double fminus_cos_yaw = -SDK::MathLibrary->cos( Yaw );

		double X = -( dy * fminus_cos_yaw + dx * fsin_yaw );
		double Y = dx * fminus_cos_yaw - dy * fsin_yaw;

		double range_value = 30 * 1000;
		Range( &X , &Y , range_value );

		int rad_x = ( int ) Position.X;
		int rad_y = ( int ) Position.Y;

		double r_siz_x = Size.X;
		double r_siz_y = Size.Y;

		int x_max = ( int ) r_siz_x + rad_x - 5;
		int y_max = ( int ) r_siz_y + rad_y - 5;

		double out_screen_x = rad_x + ( ( int ) r_siz_x / 2 + int( X / range_value * r_siz_x ) );
		double out_screen_y = rad_y + ( ( int ) r_siz_y / 2 + int( Y / range_value * r_siz_y ) );

		if ( out_screen_x > x_max )
			out_screen_x = x_max;

		if ( out_screen_x < rad_x )
			out_screen_x = rad_x;

		if ( out_screen_y > y_max )
			out_screen_y = y_max;

		if ( out_screen_y < rad_y )
			out_screen_y = rad_y;

		*Screen = SDK::FVector2D( out_screen_x , out_screen_y );
	}

	void DrawRect( SDK::FVector2D ScreenPosition , SDK::FVector2D Size , SDK::FLinearColor RenderColor , float Thickness )
	{
		Implementation::Canvas->K2_DrawLine( SDK::FVector2D( ScreenPosition.X , ScreenPosition.Y ) , SDK::FVector2D( ScreenPosition.X + Size.X , ScreenPosition.Y ) , Thickness , RenderColor );
		Implementation::Canvas->K2_DrawLine( SDK::FVector2D( ScreenPosition.X + Size.X , ScreenPosition.Y ) , SDK::FVector2D( ScreenPosition.X + Size.X , ScreenPosition.Y + Size.Y ) , Thickness , RenderColor );
		Implementation::Canvas->K2_DrawLine( SDK::FVector2D( ScreenPosition.X + Size.X , ScreenPosition.Y + Size.Y ) , SDK::FVector2D( ScreenPosition.X , ScreenPosition.Y + Size.Y ) , Thickness , RenderColor );
		Implementation::Canvas->K2_DrawLine( SDK::FVector2D( ScreenPosition.X , ScreenPosition.Y + Size.Y ) , SDK::FVector2D( ScreenPosition.X , ScreenPosition.Y ) , Thickness , RenderColor );
	}

	void DrawRectFilled( SDK::FVector2D ScreenPosition , SDK::FVector2D Size , SDK::FLinearColor RenderColor , float Thickness )
	{
		for ( double i = 0; i < Size.Y; i++ )
		{
			Implementation::Canvas->K2_DrawLine( SDK::FVector2D( ScreenPosition.X , ScreenPosition.Y + i ) , SDK::FVector2D( ScreenPosition.X + Size.X , ScreenPosition.Y + i ) , 1.f , RenderColor );
		}
	}

	void Setup( SDK::FVector2D RadarPos , SDK::FVector2D RadarSize )
	{
		SDK::UTexture2D* DefaultTexture = Implementation::Canvas->DefaultTexture( );
		Implementation::Canvas->K2_DrawTexture( DefaultTexture , RadarPos , RadarSize , SDK::FVector2D( ) , SDK::FVector2D( 1.0 , 1.0 ) , SDK::FLinearColor( 1.0f , 1.0f , 1.0f , 0.20f ) , SDK::EBlendMode::BLEND_Translucent , 0.f , SDK::FVector2D( ) );
		DrawRect( RadarPos , RadarSize , SDK::FLinearColor( 1.f , 1.f , 1.f , 1.f ) , 1.f );

		Implementation::Canvas->K2_DrawLine( SDK::FVector2D( RadarPos.X + RadarSize.X / 2 , RadarPos.Y + RadarSize.Y ) , SDK::FVector2D( RadarPos.X + RadarSize.X / 2 , RadarPos.Y + RadarSize.Y / 2 ) , 1.f , SDK::FLinearColor( 1.f , 1.f , 1.f , 1.f ) );
		Implementation::Canvas->K2_DrawLine( SDK::FVector2D( RadarPos.X + RadarSize.X / 2 , RadarPos.Y + RadarSize.Y / 2 ) , SDK::FVector2D( RadarPos.X , RadarPos.Y ) , 1.f , SDK::FLinearColor( 1.f , 1.f , 1.f , 1.f ) );
		Implementation::Canvas->K2_DrawLine( SDK::FVector2D( RadarPos.X + RadarSize.X / 2 , RadarPos.Y + RadarSize.Y / 2 ) , SDK::FVector2D( RadarPos.X + RadarSize.X , RadarPos.Y ) , 1.f , SDK::FLinearColor( 1.f , 1.f , 1.f , 1.f ) );
	}

	void Add( SDK::FVector WorldLocation , SDK::FLinearColor Color , SDK::FVector CameraLocation , SDK::FRotator CameraRotation, SDK::FVector2D RadarPos , SDK::FVector2D RadarSize )
	{
		SDK::FVector2D Projected = SDK::FVector2D( );
		RotatePoint( &Projected , WorldLocation , CameraLocation , CameraRotation, RadarPos, RadarSize );
		Wrapper::Circle( Projected , Color , 4.0 , 138.0 , true );
	}
}