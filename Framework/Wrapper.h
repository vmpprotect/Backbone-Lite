#pragma once

namespace Wrapper
{
	void Circle( SDK::FVector2D ScreenPosition , SDK::FLinearColor color , double radius , double segments , bool filled )
	{
		double Step = M_PI * 2.0 / segments;
		int Count = 0;
		SDK::FVector2D Vectors[ 128 ];

		for ( double Degree = 0; Degree < M_PI * 2.0; Degree += Step )
		{
			double X_1 = radius * SDK::MathLibrary->cos( Degree ) + ScreenPosition.X;
			double Y_1 = radius * SDK::MathLibrary->sin( Degree ) + ScreenPosition.Y;
			double X_2 = radius * SDK::MathLibrary->cos( Degree + Step ) + ScreenPosition.X;
			double Y_2 = radius * SDK::MathLibrary->sin( Degree + Step ) + ScreenPosition.Y;

			Vectors[ Count ].X = X_1;
			Vectors[ Count ].Y = Y_1;
			Vectors[ Count + 1 ].X = X_2;
			Vectors[ Count + 1 ].Y = Y_2;

			if ( filled )
			{
				for ( double X = X_1; X <= X_2; X += 1.0 )
				{
					double Y = ScreenPosition.Y + radius * SDK::MathLibrary->sin( SDK::MathLibrary->acos( ( X - ScreenPosition.X ) / radius ) );
					Implementation::Canvas->K2_DrawLine( SDK::FVector2D( X , Y_1 ) , SDK::FVector2D( X , Y ) , 1.0f, color );
					Implementation::Canvas->K2_DrawLine( SDK::FVector2D( X , Y ) , SDK::FVector2D( X , Y_2 ) , 1.0f, color  );
				}
			}
			else
			{
				Implementation::Canvas->K2_DrawLine( SDK::FVector2D( Vectors[ Count ].X , Vectors[ Count ].Y ) , SDK::FVector2D( X_2 , Y_2 ) , 1.0f, color );
			}
		}
	}
}