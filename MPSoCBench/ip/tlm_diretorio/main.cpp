//#include "Diretorio.h"
#include "common.h"
#include "Diretorio.h"


int main()
{
	Diretorio *dir;
	dir = new Diretorio();
//	uint32_t aux = 3;
	//Diretorio vetorr[10];
	//vetorr[0].checkValidation(0, 0);
	int x=0;
	// for(aux=0;aux<100000;aux++)
	dir->validate(0, 3, 0);
	dir->validate(1, 3, 0);
	dir->validate(2, 3, 0);
	dir->validate(3, 3, 0);
	dir->validate(4, 3, 0);
	dir->validate(7, 3, 0);
	dir->validate(5, 3, 0);
	dir->validate(6, 3, 0);
	dir->validate(8, 3, 0);
	dir->validate(10, 3, 0);
	dir->validate(9, 7, 1);
	//dir->validate(x, 71, 502);
	//dir->validate(x, 1001, 607);
	cout << "validates passes"<<endl;
	dir->unvalidate(x+1, 7);
	dir->unvalidate(x+1, 71);
	cout << "unvalidate passes"<<endl;
	cout << dir->checkValidation(0, 3) << endl;
	cout << dir->checkValidation(0, 7) << endl;
	cout << dir->checkValidation(0, 71) << endl;
	cout << dir->checkValidation(0, 1001) << endl;
	//dir->checkValidation(x, aux);


	/*
	int ** teste = new int*;
	int *a = new int;
	int *b = new int;
	int *c = new int;
	*a = 3;
	*b = 5;
	*c = 7;
	teste[0] = a;
	teste[1] = b;
	cout << "teste\n" << *teste[1] << endl;
	*/
//	int nProc=0;
//	int state=-1;
//	int memHeader=0;
//	int proc=0;
/*
	unsigned char buffer[64];
	//unsigned char *st;
	//buffer = "oi\n";
	strcpy((char*)buffer, "oi\n");
	lol lala;
	lala.get_buffer();
	cout << lala.y<<endl;
	lol lalala;
	cout << lalala.y<<endl;


//	strcpy((char *)buffer, (lala.get_buffer());
	cout << "Digite numero de Processadores" <<endl;
//	cin >> nProc;
	Diretorio dir(nProc, "2");
	string opt= "K";

	while(opt != "sair")
	{
		cout << "Digite add, checkvalidation, validate, unvalidate ou sair"<<endl;
		cin >> opt;
		if(opt == "add")
			state=0;
		else if(opt == "checkvalidation")
			state=1;
		else if(opt == "validate")
			state=2;
		else if(opt == "unvalidate")
			state=3;
		else if(opt == "sair")
			state=4;


		switch(state)
		{
			case 0:
				//cout << "add"<<endl;
				cout << "Digite processador" <<endl;
				cin >> proc;
				cout << "Digite endereço de memoria" <<endl;
				cin >> memHeader;
				dir.add(proc, memHeader);
			break;

			case 1:
				//cout << "checkvalidation"<<endl;
				cout << "Digite processador" <<endl;
				cin >> proc;
				cout << "Digite endereço de memoria" <<endl;
				cin >> memHeader;
				if(dir.checkValidation(proc, memHeader))
					cout << "valido" <<endl;
				else
					cout << "NAO valido" <<endl;
			break;

			case 2:
				//cout << "validate"<<endl;
				cout << "Digite processador" <<endl;
				cin >> proc;
				cout << "Digite endereço de memoria" <<endl;
				cin >> memHeader;
				dir.validate(proc, memHeader);
			break;

			case 3:
				//cout << "unvalidate"<<endl;
				cout << "Digite processador" <<endl;
				cin >> proc;
				cout << "Digite endereço de memoria" <<endl;
				cin >> memHeader;
				dir.unvalidate(proc, memHeader);
			break;

			case 4:
				//cout << "sair"<<endl;
			break;

			default:
			break;
		}
	}

*/

	delete dir;
	return 0;
}
