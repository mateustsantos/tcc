#include "cacheMem.h"
#include "cacheBlock.h"

cacheMem::cacheMem(int nCache)
{
	//ctor
	//blocks = new cacheBlock*;
	//for(int i=0; i<MAXBLOCKS; i++)
	//{
	//	blocks[i] = new cacheBlock();
	//	cout << "alocado pos i: " << i<<endl;
	//}

	numberCache = nCache;
	//cout << "construtor cache mem" << endl;

}

cacheMem::~cacheMem()
{
	//cout << "destrutor cache mem" << endl;
	//for(int i=0; i<MAXBLOCKS; i++)
		//delete blocks[i];
	//delete blocks;
	cout << "destrutor cache mem" << endl;
}
/** @brief ~cacheMem
  *
  * @todo: document this function
  */


/** @brief unvalidate
  *
  * @todo: document this function
  */



/** @brief checkValidation
  *
  * @todo: document this function
  */

bool cacheMem::validate(uint32_t address, int index)
{
	if(index>MAXBLOCKS)
		return false;
	blocks[index].validate(address);
	return true;
}
bool cacheMem::checkValidation(uint32_t address)
{
	for(int i =0;i<MAXBLOCKS;i++)
		if(blocks[i].address == address)
			return blocks[i].checkValidation(address);
	return false;
}
void cacheMem::invalidate(uint32_t address)
{
	for(int i=0 ; i<MAXBLOCKS;i++)
	{

		//cout << "i: "<< i <<endl;
		//cout << blocks[4].address <<endl;
		if(blocks[i].address == address){
			//cout <<"really??" <<endl;
			blocks[i].invalidate();
			i=MAXBLOCKS;
		}
		//cout << "i: "<< i <<endl;
	}
}

/** @brief remove
  *
  * @todo: document this function
  */


/** @brief add
  *
  * @todo: document this function
  */


/** @brief cacheMem
  *
  * @todo: document this function
  */


