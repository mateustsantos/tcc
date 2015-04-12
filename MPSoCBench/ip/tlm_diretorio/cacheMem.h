#ifndef CACHEMEMORYLIST_H
#define CACHEMEMORYLIST_H
#include "cacheBlock.h"
#define MAXBLOCKS 1024
class cacheMem
{
	public:
		int numberCache;
		cacheMem(int);
		cacheMem(){;};
		cacheBlock blocks[MAXBLOCKS];
		//cacheBlock** blocks;
		bool validate(uint32_t, int);
		bool checkValidation(uint32_t);
		void invalidate(uint32_t);


		virtual ~cacheMem();
	protected:
	private:
};

#endif // CACHEMEMORYLIST_H
