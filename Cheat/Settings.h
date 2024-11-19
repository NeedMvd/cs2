#pragma once
namespace Aimbot
{
	inline bool Enable = false;
	inline float Fov;
	inline float Smooth;

	inline float RCS_X;
	inline float RCS_Y;
	inline int hitbox;


}

namespace Visuals
{
	inline bool Enable = false;
	inline float ESP_Box_Color[4] = { 171 / 255.0f, 48 / 255.0f, 201 / 255.0f, 255 / 255.0f };
}