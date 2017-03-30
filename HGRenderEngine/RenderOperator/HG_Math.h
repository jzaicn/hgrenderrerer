#pragma once

template <typename T>
inline T clamp(T x, T lo, T hi)
{
	return (x < lo) ? lo : ((x > hi) ? hi : x);
}

class HG_Math
{
public:
	HG_Math(void);
	~HG_Math(void);
};

