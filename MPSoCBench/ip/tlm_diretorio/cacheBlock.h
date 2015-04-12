
#ifndef CACHEBLOCK_H
#define CACHEBLOCK_H
#include "common.h"


class cacheBlock
{
	public:

		uint32_t address;
		bool validated;
		void validate(uint32_t);
		void invalidate();
		bool checkValidation(uint32_t);
		cacheBlock();
	protected:
	private:
};

#endif // CACHEBLOCK_H
