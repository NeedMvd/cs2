#include "Run.h"
#include "SDK/Game.h"
#include "SDK/Entity.h"
#include <map>
#include "Settings.h"
#include "AimDeps.h"

inline void aimbot(const CEntity& entity, Vec3 LocalPos, Vec3 Aimpos)
{

	if (Aimbot::Enable == false)
		return;

	float yaw;
	float pitch;
	Vec3 Pos_Relative;
	float Distance;
	float Norm;

	Pos_Relative = Aimpos - LocalPos;


	Distance = sqrt(pow(Pos_Relative.x, 2) + pow(Pos_Relative.y, 2));

	yaw = atan2f(Pos_Relative.y, Pos_Relative.x) * 57.295779513 - entity.Pawn.ViewAngle.y;
	pitch = -atan(Pos_Relative.z / Distance) * 57.295779513 - entity.Pawn.ViewAngle.x;
	Norm = sqrt(pow(yaw, 2) + pow(pitch, 2));
	if (Norm > Aimbot::Fov)
	{
		return;
	}
		

	yaw = yaw * (1 - Aimbot::Smooth) + entity.Pawn.ViewAngle.y;
	pitch = pitch * (1 - Aimbot::Smooth) + entity.Pawn.ViewAngle.x;


	if (entity.Pawn.ShotsFired > 0)
	{
		Vec2 PunchAngle;
		if (entity.Pawn.AimPunchCache.Count > 0 && entity.Pawn.AimPunchCache.Count <= 0xFFFF)
		{
			if (ProcessMgr.ReadMemory<Vec2>(entity.Pawn.AimPunchCache.Data + (entity.Pawn.AimPunchCache.Count - 1) * sizeof(Vec3), PunchAngle))
			{
				yaw -= PunchAngle.y * Aimbot::RCS_X;
				pitch -= PunchAngle.x * Aimbot::RCS_Y;
			}
		}
	}

	gGame.SetViewAngle(yaw, pitch);


}

void Rectangle(Vec2 Pos, Vec2 Size, ImColor Color, float Thickness, float Rounding)
{
	ImGui::GetBackgroundDrawList()->AddRect(Pos.ToImVec2(), { Pos.x + Size.x,Pos.y + Size.y }, Color, Rounding, 0, Thickness);
}

ImVec4 GetBox(const CEntity& entity)
{
	BoneJointPos Head = entity.GetBone().BonePosList[BONEINDEX::head];

	Vec2 Size, Pos;

	Size.y = (entity.Pawn.ScreenPos.y - Head.ScreenPos.y) * 1.09;
	Size.x = Size.y * 0.6;

	Pos = ImVec2(entity.Pawn.ScreenPos.x - Size.x / 2, Head.ScreenPos.y - Size.y * 0.08);

	return ImVec4(Pos.x, Pos.y, Size.x, Size.y);
}


inline ImColor FloatArrayToImColor(float floatArray[4]) {
	// Certifique-se de que os valores estejam no intervalo [0.0f, 1.0f]
	float clampedValues[4];
	for (int i = 0; i < 4; ++i) {
		clampedValues[i] = ImClamp(floatArray[i], 0.0f, 1.0f);
	}

	// Crie um objeto ImColor usando os valores float
	return ImColor(clampedValues[0], clampedValues[1], clampedValues[2], clampedValues[3]);
}

void Cheats::Run()
{
	if (!ProcessMgr.ReadMemory(gGame.GetMatrixAddress(), gGame.View.Matrix, 64))
		return;

	gGame.UpdateEntityListEntry();

	DWORD64 LocalControllerAddress = 0;
	DWORD64 LocalPawnAddress = 0;

	if (!ProcessMgr.ReadMemory(gGame.GetLocalControllerAddress(), LocalControllerAddress))
		return;
	if (!ProcessMgr.ReadMemory(gGame.GetLocalPawnAddress(), LocalPawnAddress))
		return;

	CEntity LocalEntity;
	static int LocalPlayerControllerIndex = 1;
	if (!LocalEntity.UpdateController(LocalControllerAddress))
		return;
	if (!LocalEntity.UpdatePawn(LocalPawnAddress))
		return;

	float DistanceToSight = 0;
	float MaxAimDistance = 100000;
	Vec3  HeadPos{ 0,0,0 };
	Vec3  AimPos{ 0,0,0 };

	for (int i = 0; i < 64; i++)
	{
		CEntity Entity;
		DWORD64 EntityAddress = 0;
		if (!ProcessMgr.ReadMemory<DWORD64>(gGame.GetEntityListEntry() + (i + 1) * 0x78, EntityAddress))
			continue;

		if (EntityAddress == LocalEntity.Controller.Address)
		{
			LocalPlayerControllerIndex = i;
			continue;
		}

		if (!Entity.UpdateController(EntityAddress))
			continue;

		if (!Entity.UpdatePawn(Entity.Pawn.Address))
			continue;

		if (Entity.Controller.TeamID == LocalEntity.Controller.TeamID)
			continue;

		if (!Entity.IsAlive())
			continue;

		if (!Entity.IsInScreen())
			continue;

		ImVec4 Vec = GetBox(Entity);

		ImColor colorbox = FloatArrayToImColor(Visuals::ESP_Box_Color);

		Rectangle({ Vec.x, Vec.y }, { Vec.z, Vec.w }, colorbox, 1.4, 0.5);

		switch (Aimbot::hitbox)
		{
		case 0:
			Aimbot_Enum::AimPositionIndex = BONEINDEX::head;
			break;
		case 1:
			Aimbot_Enum::AimPositionIndex = BONEINDEX::neck_0;
			break;
		case 2:
			Aimbot_Enum::AimPositionIndex = BONEINDEX::spine_1;
			break;
		case 3:
			Aimbot_Enum::AimPositionIndex = BONEINDEX::leg_lower_L;
			break;
		case 4:
			Aimbot_Enum::AimPositionIndex = BONEINDEX::leg_lower_R;
			break;
		default:
			break;
		}

		DistanceToSight = Entity.GetBone().BonePosList[BONEINDEX::head].ScreenPos.DistanceTo({ ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2 });

		if (DistanceToSight < MaxAimDistance)
		{
			if (Entity.Pawn.bSpottedByMask & (DWORD64(1) << (LocalPlayerControllerIndex)) || LocalEntity.Pawn.bSpottedByMask & (DWORD64(1) << (i)))
			{
				AimPos = Entity.GetBone().BonePosList[Aimbot_Enum::AimPositionIndex].Pos;
				if (Aimbot_Enum::AimPositionIndex == BONEINDEX::head)
				{
					AimPos.z -= 1.f;
				}
			}
		}

		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			if (AimPos != Vec3(0, 0, 0))
			{
				aimbot(LocalEntity, LocalEntity.Pawn.CameraPos, AimPos);
			}
		}

	}
}
