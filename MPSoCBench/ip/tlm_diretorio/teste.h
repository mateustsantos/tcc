#ifndef teste_H
#define teste_H
#include "common.h"

class lol
{
	public:
		static int x;
		bool state;
		int get_x()
		{
			x++;
			return x;
		}
		int y;
		unsigned char buffer[64];
		lol()
		{
			y=get_x();
		}


		void get_buffer()
		{
			strcpy((char *)buffer, (char *)this);

		}

	protected:
	private:
};

int lol::x=0;

#endif // CACHEMEMORY_H ??


