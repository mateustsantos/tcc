#include "cacheMem.h"
#include "cacheBlock.h"
//#include "common.h"

void cacheBlock::validate(uint32_t m_address)
{
	address = m_address;
	validated = true;
	//cout << "validou-se address: " << address<<endl;
}

bool cacheBlock::checkValidation(uint32_t m_address)
{
	if((m_address == address) && validated){
		return true;
	}
	return false;
}


void cacheBlock::invalidate()
{
	//cout << " invalidou na cacheblock: "<<address <<endl;
	validated = false;
}


cacheBlock::cacheBlock()
{
	address = -1;
	validated = false;
}

