#ifndef DIRETORIO_H
#define DIRETORIO_H
#include "cacheMem.h"
//#include "common.h"

class Diretorio
{
	public:
		fstream log;
		int totalOfCaches;
		cacheMem cacheMemVector[64];
		Diretorio();
		virtual ~Diretorio();
		void add(int);
		bool checkValidation(int, uint32_t);
		void checkNumberCache(int);
		bool validate(int, uint32_t, int);
		void unvalidate(int, uint32_t);

	protected:
	private:
};

#endif // DIRETORIO_H
