#pragma once

namespace Framework
{
	class Render
	{
	public:
		void FilledRect( double x , double y , double width , double height , SDK::FLinearColor color )
		{
			for ( int a = y; a < y + height; a++ )
			{
				this->Canvas->K2_DrawLine( SDK::FVector2D( x , a ) , SDK::FVector2D( x + width , a ) , 1 , color );
			}
		}

		void DrawRect( SDK::FVector2D ScreenPosition , SDK::FVector2D Size , SDK::FLinearColor RenderColor , float Thickness )
		{
			this->Canvas->K2_DrawLine( SDK::FVector2D( ScreenPosition.X , ScreenPosition.Y ) , SDK::FVector2D( ScreenPosition.X + Size.X , ScreenPosition.Y ) , Thickness , RenderColor );
			this->Canvas->K2_DrawLine( SDK::FVector2D( ScreenPosition.X + Size.X , ScreenPosition.Y ) , SDK::FVector2D( ScreenPosition.X + Size.X , ScreenPosition.Y + Size.Y ) , Thickness , RenderColor );
			this->Canvas->K2_DrawLine( SDK::FVector2D( ScreenPosition.X + Size.X , ScreenPosition.Y + Size.Y ) , SDK::FVector2D( ScreenPosition.X , ScreenPosition.Y + Size.Y ) , Thickness , RenderColor );
			this->Canvas->K2_DrawLine( SDK::FVector2D( ScreenPosition.X , ScreenPosition.Y + Size.Y ) , SDK::FVector2D( ScreenPosition.X , ScreenPosition.Y ) , Thickness , RenderColor );
		}

		void ResetY( )
		{
			this->Offset.Y = 10.0;
		}

		void Setup( SDK::UCanvas* Canvas , SDK::APlayerController* PlayerController , SDK::UFont* Font )
		{
			this->Canvas = Canvas;
			this->PlayerController = PlayerController;
			this->Font = Font;
		}

		bool CheckHovered( SDK::FVector2D pos , SDK::FVector2D Size )
		{
			if ( this->MousePosition.X > pos.X && this->MousePosition.Y > pos.Y )
				if ( this->MousePosition.X < pos.X + Size.X && this->MousePosition.Y < pos.Y + Size.Y )
					return true;

			return false;
		}

		bool Begin( SDK::FString Title )
		{
			static bool Initialized = false;
			if ( !Initialized )
			{
				this->Position = SDK::FVector2D( 200.0 , 200.0 );
				this->Size = SDK::FVector2D( 623.0 , 420.0 );

				Initialized = true;
			}

			this->Offset = SDK::FVector2D( 0.0 , 0.0 );

			this->MousePosition = this->PlayerController->GetMousePosition( );
			this->LeftMouseDown = Implementation::PlayerController->IsInputKeyDown( Implementation::LeftMouseButton );

			static SDK::FVector2D ClickPosition = SDK::FVector2D( 0.0 , 0.0 );
			this->WindowHovered = this->CheckHovered( SDK::FVector2D( this->Position.X , this->Position.Y - 5.0 ) , SDK::FVector2D( this->Size.X , 35.0 ) );
			this->WindowGrabbed = this->WindowGrabbed ? this->LeftMouseDown : this->WindowHovered && this->LeftMouseDown;
			if ( WindowGrabbed )
			{
				if ( !ClickPosition.X && !ClickPosition.Y )
				{
					ClickPosition = SDK::FVector2D( this->MousePosition.X - this->Position.X , this->MousePosition.Y - this->Position.Y );
				}

				WindowHovered = true;
			}

			if ( ClickPosition.X && ClickPosition.Y )
			{
				this->Position = SDK::FVector2D( this->MousePosition.X - ( this->Size.X / 2.0 ) , this->MousePosition.Y - ( 20.0 / 2.0 ) );
			}

			if ( !this->LeftMouseDown )
			{
				ClickPosition = SDK::FVector2D( );
			}

			FilledRect( this->Position.X , this->Position.Y , this->Size.X , 38.0 , SDK::FromRGB( 12 , 12 , 12 ) );
			FilledRect( this->Position.X + 5.0 , this->Position.Y + 5.0 , this->Size.X - 10.0 , 35.0 - 10.0 , SDK::FromRGB( 23 , 23 , 23 ) );
			DrawRect( SDK::FVector2D( this->Position.X + 5.0 , this->Position.Y + 5.0 ) , SDK::FVector2D( this->Size.X - 10.0 , 35.0 - 10.0 ) , SDK::FromRGB( 46 , 46 , 46 ) , 1.5f );
			Canvas->K2_DrawText( this->Font , Title , SDK::FVector2D( this->Position.X + 10.0 , this->Position.Y + 10.0 ) , SDK::FromRGB( 143 , 143 , 143 ) , false , false , true );
			this->Position.Y += 40.0;

			FilledRect( this->Position.X , this->Position.Y , this->Size.X , this->Size.Y , SDK::FromRGB( 12 , 12 , 12 ) );
			FilledRect( this->Position.X + 5.0 , this->Position.Y + 5.0 , 151.0 , this->Size.Y - 15.0 , SDK::FromRGB( 23 , 23 , 23 ) );
			DrawRect( SDK::FVector2D( this->Position.X + 5.0 , this->Position.Y + 5.0 ) , SDK::FVector2D( 151.0 , this->Size.Y - 15.0 ) , SDK::FromRGB( 46 , 46 , 46 ) , 1.5f );

			FilledRect( this->Position.X + 5.0 + 151.0 + 7.0 , this->Position.Y + 5.0 , 223.0 , this->Size.Y - 15.0 , SDK::FromRGB( 23 , 23 , 23 ) );
			DrawRect( SDK::FVector2D( this->Position.X + 5.0 + 151.0 + 7.0 , this->Position.Y + 5.0 ) , SDK::FVector2D( 223.0 , this->Size.Y - 15.0 ) , SDK::FromRGB( 46 , 46 , 46 ) , 1.5f );

			FilledRect( this->Position.X + 5.0 + 151.0 + 7.0 + 223.0 + 10.0 , this->Position.Y + 5.0 , 223.0 , this->Size.Y - 15.0 , SDK::FromRGB( 23 , 23 , 23 ) );
			DrawRect( SDK::FVector2D( this->Position.X + 5.0 + 151.0 + 7.0 + 223.0 + 10.0 , this->Position.Y + 5.0 ) , SDK::FVector2D( 223.0 , this->Size.Y - 15.0 ) , SDK::FromRGB( 46 , 46 , 46 ) , 1.5f );

			this->Offset.Y += 10.0;

			return true;
		}

		void SwitchForm( )
		{
			this->Position.X += 223.0 + 10.0;
			this->Offset.Y = 10.0;
		}

		void ResetForm( )
		{
			this->Position.X -= 223.0 + 10.0;
		}

		bool Button( SDK::FString Name , bool Active )
		{
			SDK::FVector2D CurrentPosition = SDK::FVector2D( this->Position.X + 5.0 , this->Position.Y + 5.0 );
			CurrentPosition.Y = CurrentPosition.Y + this->Offset.Y;

			bool Hovered = this->CheckHovered( CurrentPosition , SDK::FVector2D( 41.0 , 23.0 ) );
			bool Clicked = Implementation::PlayerController->WasInputKeyJustPressed( Implementation::LeftMouseButton ) && Hovered;

			SDK::FLinearColor RenderColor = SDK::FromRGB( 143 , 143 , 143 );
			if ( Clicked || Hovered || Active )
				RenderColor = SDK::FromRGB( 237 , 32 , 118 );

			FilledRect( CurrentPosition.X + 6.0 , CurrentPosition.Y + 6.0 , 4.0 , 19.0 , RenderColor );
			DrawRect( SDK::FVector2D( CurrentPosition.X + 6.0 , CurrentPosition.Y + 6.0 ) , SDK::FVector2D( 4.0 , 19.0 ) , SDK::FromRGB( 46 , 46 , 46 ) , 1.5f );

			Canvas->K2_DrawText( this->Font , Name , SDK::FVector2D( CurrentPosition.X + 6.0 + 9.0 , CurrentPosition.Y + 8.0 ) , RenderColor , false , false , true );

			this->Offset.Y += 41.0;

			return Clicked;
		}

		void Checkbox( SDK::FString Name , bool* Toggle )
		{
			SDK::FVector2D CurrentPosition = SDK::FVector2D( this->Position.X + 5.0 + 151.0 + 7.0 + 5.0 , this->Position.Y + 5.0 );
			CurrentPosition.Y = CurrentPosition.Y + this->Offset.Y;

			SDK::FVector2D CurrentSize = SDK::FVector2D( 16.0 , 16.0 );

			bool Hovered = this->CheckHovered( CurrentPosition , CurrentSize );
			bool Clicked = Implementation::PlayerController->WasInputKeyJustPressed( Implementation::LeftMouseButton ) && Hovered;

			SDK::FLinearColor RenderColor = SDK::FromRGB( 46 , 46 , 46 );
			if ( *Toggle )
				RenderColor = SDK::FromRGB( 237 , 32 , 118 );
			if ( Clicked ) *Toggle = !*Toggle;

			FilledRect( CurrentPosition.X , CurrentPosition.Y , CurrentSize.X , CurrentSize.Y , RenderColor );
			DrawRect( CurrentPosition , CurrentSize , SDK::FromRGB( 46 , 46 , 46 ) , 1.5f );

			Canvas->K2_DrawText( this->Font , Name , SDK::FVector2D( CurrentPosition.X + CurrentSize.X + 5.0 , CurrentPosition.Y ), SDK::FromRGB( 143 , 143 , 143 ) , false , false , true );

			this->Offset.Y += 25.0;
		}

		void Slider( SDK::FString Name , double Min , double Max , double* Value )
		{
			SDK::FVector2D CurrentPosition = SDK::FVector2D( this->Position.X + 5.0 + 151.0 + 7.0 + 5.0 , this->Position.Y + 5.0 );
			CurrentPosition.Y = CurrentPosition.Y + this->Offset.Y;

			SDK::FVector2D CurrentSize = SDK::FVector2D( 155.0 , 9.0 ); // 8.0 , 144.0
			Canvas->K2_DrawText( this->Font , Name , CurrentPosition , SDK::FromRGB( 143 , 143 , 143 ) , false , false , true );
			CurrentPosition.Y += 20.0;

			FilledRect( CurrentPosition.X , CurrentPosition.Y , CurrentSize.X , CurrentSize.Y , SDK::FromRGB( 19 , 19 , 19 ) );
			FilledRect( CurrentPosition.X , CurrentPosition.Y , *Value * ( CurrentSize.X / Max ) , CurrentSize.Y + 1.0 , SDK::FromRGB( 237 , 32 , 118 ) );
			DrawRect( CurrentPosition , CurrentSize , SDK::FromRGB( 46 , 46 , 46 ) , 1.5f );

			Canvas->K2_DrawText( this->Font , SDK::StringLibrary->Conv_IntToString( static_cast< int >( *Value ) ) , SDK::FVector2D( CurrentPosition.X + CurrentSize.X + 9.0 , ( CurrentPosition.Y + ( CurrentSize.Y / 2.0 ) ) ) , SDK::FromRGB( 143 , 143 , 143 ) , false , true , true );

			//SDK::FLinearColor RenderColor = SDK::FromRGB( 46 , 46 , 46 );
			//if ( *Toggle )
			//	RenderColor = SDK::FromRGB( 237 , 32 , 118 );
			//if ( Clicked ) *Toggle = !*Toggle;

			if ( this->MousePosition.X > CurrentPosition.X && this->MousePosition.Y > CurrentPosition.Y && this->MousePosition.X < CurrentPosition.X + CurrentSize.X && this->MousePosition.Y < CurrentPosition.Y + CurrentSize.Y && this->LeftMouseDown )
			{
				//(this->Position.X + Position.X) + (*pscalar * ((slider_width - 8) / max))
				if ( this->MousePosition.X < CurrentPosition.X + 4.0 )
				{
					*Value = Min;
				}
				else if ( this->MousePosition.X > CurrentPosition.X + CurrentSize.X )
				{
					*Value = Max;
				}
				else
				{
					*Value = ( this->MousePosition.X - ( CurrentPosition.X ) ) * ( Max / CurrentSize.X );
				}
			}

			this->Offset.Y += 35.0;

		}

		void Combobox( SDK::FString Name , int* Value , SDK::FString Arguments[ ] , int NumArguments, bool* Active )
		{
			this->Offset.Y += 5.0;

			SDK::FVector2D CurrentPosition = SDK::FVector2D( this->Position.X + 5.0 + 151.0 + 7.0 + 5.0 , this->Position.Y + 5.0 );
			CurrentPosition.Y = CurrentPosition.Y + this->Offset.Y;

			SDK::FVector2D CurrentSize = SDK::FVector2D( 180.0 , 20.0 );

			bool Hovered = this->CheckHovered( CurrentPosition , CurrentSize );
			bool Clicked = Implementation::PlayerController->WasInputKeyJustPressed( Implementation::LeftMouseButton ) && Hovered;
			bool AnyHovered = Hovered;
			if ( Clicked ) *Active = !*Active;

			SDK::FLinearColor RenderColor = SDK::FromRGB( 19 , 19 , 19 );

			FilledRect( CurrentPosition.X , CurrentPosition.Y , CurrentSize.X , CurrentSize.Y , RenderColor );
			DrawRect( CurrentPosition , CurrentSize , SDK::FromRGB( 46 , 46 , 46 ) , 1.5f );

			Canvas->K2_DrawText( this->Font , Name , SDK::FVector2D( CurrentPosition.X + 6.0 , CurrentPosition.Y + ( CurrentSize.Y / 2.0 ) ) , SDK::FromRGB( 143 , 143 , 143 ) , false , true , true );
			Canvas->K2_DrawText( this->Font , SDK::FString( L"<" ) , SDK::FVector2D( ( CurrentPosition.X + CurrentSize.X - 10.0 ) , CurrentPosition.Y + ( CurrentSize.Y / 2.0 ) ) , SDK::FromRGB( 237 , 32 , 118 ) , false , true , true );

			if ( *Active )
			{
				this->PopupOpen += 1;

				SDK::FVector2D SelectionStart = SDK::FVector2D( CurrentPosition.X , CurrentPosition.Y + CurrentSize.Y );

				for ( int i = 0; i < NumArguments; i++ )
				{
					CurrentPosition.Y += CurrentSize.Y;

					bool ItemHovered = this->CheckHovered( CurrentPosition , CurrentSize );
					bool ItemClicked = ItemHovered && Implementation::PlayerController->WasInputKeyJustPressed( Implementation::LeftMouseButton );
					SDK::FLinearColor ItemColor = SDK::FromRGB( 19 , 19 , 19 );

					if ( ItemHovered && !AnyHovered )
						AnyHovered = true;

					if ( ItemClicked )
						*Value = i;

					if ( *Value == i )
						ItemColor = SDK::FromRGB( 49 , 49 , 49 );

					FilledRect( CurrentPosition.X , CurrentPosition.Y , CurrentSize.X , CurrentSize.Y , ItemColor );
					DrawRect( CurrentPosition , CurrentSize , SDK::FromRGB( 46 , 46 , 46 ) , 1.5f );

					Canvas->K2_DrawText( this->Font , Arguments[ i ] , SDK::FVector2D( CurrentPosition.X + ( CurrentSize.X / 2 ) , CurrentPosition.Y + 2 ) , SDK::FromRGB( 143 , 143 , 143 ), true , false , true );
				}
			}

			//if ( Implementation::PlayerController->WasInputKeyJustPressed( Implementation::LeftMouseButton ) && !Hovered && *Active )
			//{
			//	*Active = false;
			//	this->PopupOpen -= 1;
			//}

			this->Offset.Y += 25.0;

		}

		void EndRender( )
		{
			this->Position.Y -= 40.0;

			FilledRect( this->MousePosition.X , this->MousePosition.Y , 4.0 , 4.0 , SDK::FromRGB( 237 , 32 , 118 ) );
			//DrawRect( this->MousePosition , SDK::FVector2D( 4.0 , 4.0 ) , SDK::FromRGB( 46 , 46 , 46 ) , 1.5f );
		}

	private:
		bool WindowHovered = false; bool WindowGrabbed = false;
		bool LeftMouseDown = false;
		SDK::UCanvas* Canvas = nullptr;
		SDK::APlayerController* PlayerController = nullptr;
		SDK::FVector2D Position = SDK::FVector2D( );
		SDK::FVector2D Size = SDK::FVector2D( );
		SDK::FVector2D Offset = SDK::FVector2D( );
		SDK::FVector2D MousePosition = SDK::FVector2D( );
		SDK::UFont* Font = nullptr;
		int PopupOpen = 0;
	};
}