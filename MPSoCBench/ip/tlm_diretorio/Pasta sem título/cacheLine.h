#ifndef CACHEMEMORY_H
#define CACHEMEMORY_H
#include "common.h"

class cacheLine
{
	public:
	uint32_t address;
		cacheLine(uint32_t);
		void setAddress(uint32_t);
		uint32_t getAddress();

		cacheLine* previous;
		cacheLine* next;
		virtual ~cacheLine();
	protected:
	private:
};

#endif // CACHEMEMORY_H ??


