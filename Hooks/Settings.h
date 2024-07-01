#pragma once

namespace Settings
{
	// Aimbot
	bool Aimbot = true;
	bool Crosshair = true;
	bool AimPrediction = true;
	bool TargetLine = true;
	bool TriggerBot = true;
	bool OnlyShotgun = false;
	bool VisibleOnly = false;
	bool FOVCircle = true;
	bool IgnoreBots = false;
	bool BerziersCurve = true;
	int Bone = 0;
	int Bind = 0;
	int Smooth = 0;
	double Smoothing = 10.0;
	double ShakeSpeed = 2.0;
	double FieldOfView = 80.0;
	double JitterAmount = 0.0;
	double AimbotDistance = 250.0;
	double WorldDistance = 250.0;

	// Visuals
	bool Visuals = true;
	bool Radar = true;
	bool Line = true;
	int Boxes = 2;
	bool Skeleton = true;
	bool HeadDot = true;
	bool Fill = true;
	bool Username = true;
	bool Distance = true;
	bool ActiveWeapon = true;
	
	// World
	bool WorldESP = true;
	bool PickupESP = true;
	bool ContainerESP = true;
	bool SupplyDropESP = true;
	bool LeProxy = false;
	bool VehcileESP = true;
	bool WeakspotAimbot = true;
	bool Building = true;
	bool VehicleESP = true;
	double PickupDistance = 20.0;

	//Exploits
	bool SilentAim = false;
	bool Chams = false;
	bool Wireframe = false;
	bool Wallhacks = false;
	bool KillAll = false;
	bool BulletTP = false;
	bool InstantSearch = false;
	bool NoSpread = false;
}