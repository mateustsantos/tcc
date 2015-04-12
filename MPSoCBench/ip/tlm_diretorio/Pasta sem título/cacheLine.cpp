#include "cacheLine.h"
#include "common.h"
/** @brief cacheLine
  *
  * @todo: document this function
  */
 cacheLine::cacheLine(uint32_t addr)
{
	address= addr;
	previous = 0;
	next=0;
}


void cacheLine::setAddress(uint32_t addr){
	address=addr;

}
uint32_t cacheLine::getAddress()
{
	return address;
}

 cacheLine::~cacheLine()
{

}
