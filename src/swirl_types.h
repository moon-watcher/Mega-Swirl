#ifndef SWIRLTYPES
#define SWIRLTYPES

#include <types.h>

// A snowflake is an object representing a swirl on the titlescreen that will rain down from top to bottom
typedef struct {
	u32 startedAt;
	u32 startDelay;
	u8 fallRate;
	u8 swirltype;
} snowflake;

#endif
