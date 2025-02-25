#pragma once

enum EFFECTTYPE {
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