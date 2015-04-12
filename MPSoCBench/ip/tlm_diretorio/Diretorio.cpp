#include "Diretorio.h"
Diretorio::Diretorio()
{
	//ctor
	totalOfCaches=0;
	log.open("dirLog.txt", fstream::out);
	//cacheMemVector = new cacheMem*;
	cout << "construtor dir" << endl;

}

Diretorio::~Diretorio()
{
	//dtor
	log.close();
	//for(int i=0; i<totalOfCaches; i++)
	//	delete cacheMemVector[i];
	//delete cacheMemVector;
	cout << "destrutor dir" << endl;
}



/** @brief validate
  *
  * @todo: document this function
  */
bool Diretorio::validate(int numberCache, uint32_t address, int cacheAddress)
{
	//cout << "validade number nWay" << nWay <<endl;
	checkNumberCache(numberCache);
	for(int  i=1; i<totalOfCaches;i++){

		if(cacheMemVector[i].numberCache == numberCache){

			//cout << "cacheMem acess" <<endl;
			cacheMemVector[i].validate(address, cacheAddress);
			//cout << "cacheMem acess" <<endl;

				//log << "validou-se numberCacheessador " << numberCache << " cacheAddress: " << cacheAddress << " endereço: " << address << endl;
			return true;
		}
	}
	//cout << "qntas vezes?" << nWay <<endl;
	//add(numberCache);
	//cout << "erro 1" <<endl;
	//cacheMemVector[totalOfCaches-1].validate(address, cacheAddress);


		//log << "validou-se numberCacheessador " << numberCache << " endereço: " << address << endl;
	return true;
}

/** @brief checkValidation
  *
  * @todo: document this function
  */
bool Diretorio::checkValidation(int numberCache, uint32_t address)
{
	checkNumberCache(numberCache);
	for(int i=1; i<totalOfCaches;i++)
		if(cacheMemVector[i].numberCache == numberCache)
			if(cacheMemVector[i].checkValidation(address))
			{

				//log << "Checagem do numberCacheessador: " << i << " endereço: " << address << " é Valido" <<endl;
				return true;
			}
		//log << "Checagem do numberCacheessador: " << numberCache << " endereço: " << address << " é Invalido" <<endl;
	return false;
}
void Diretorio::unvalidate(int numberCache, uint32_t address)
{
	checkNumberCache(numberCache);
	for(int i=0; i<totalOfCaches;i++)
		if(cacheMemVector[i].numberCache != numberCache)
		{
			//	cout << "nCache: " << numberCache;
			cacheMemVector[i].invalidate(address);

				//log << "posicao vetor invalidado da cache: " << i << " endereço: " << address << endl;
		}
}

/** @brief remove
  *
  * @todo: document this function
  */
void Diretorio::checkNumberCache(int numberCache)
{
	for(int i=0; i<totalOfCaches;i++)
	{
		//cout << "numberCache " << numberCache << " cacheMemVector numbercache: "<< cacheMemVector[i].numberCache << endl;
		if(numberCache == cacheMemVector[i].numberCache)
			return;
	}
	cout << "dir validou sem problemas " << numberCache<<endl;
	add(numberCache);
}

/** @brief add
  *
  * @todo: document this function
  */
void Diretorio::add(int numberCache)
{
	//cout << "add total " << totalOfCaches<< " numbercache " << numberCache<<endl;
	cacheMemVector[totalOfCaches].numberCache = numberCache;
	totalOfCaches++;
	return;
}

