#pragma once

enum EFFECTTYPE {
	NONE,
	SPEED,
	POINT,
	TRANSPARENT
};

struct Effect
{
	EFFECTTYPE type;
	float duration;
	float potency;
	Effect(EFFECTTYPE type, float duration, float potency): type(type), duration(duration), potency(potency){}
};