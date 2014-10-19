#include <custrand.h>
#include <vdp.h>

void srand(u16 seed) {
	randbase = 11073 * seed + 11;
}

u16 custrand() {
	//this is the same random function but uses a different randbase
	//custrand() + srand() provides slightly more enthropy than the function alone
	#ifdef USE_XORSHIFT
		static u32 x = 123456789;
		static u32 y = 362436069;
		static u32 z = 521288629;
		static u32 w = 88675123;
		u32 t;
	 
		t = x ^ (x << 11);
		x = y; y = z; z = w;
		w = w ^ (w >> 19) ^ (t ^ (t >> 8));
		return w;
	#else
		randbase ^= (randbase >> 1) ^ GET_HVCOUNTER;
		randbase ^= (randbase << 1);
		return randbase >> 3;
	#endif
}
