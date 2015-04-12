/********************************************************************************
	MPSoCBench Benchmark Suite
	Authors: Liana Duenha
	Supervisor: Rodolfo Azevedo
	Date: July-2012
	www.archc.org/benchs/mpsocbench

	Computer Systems Laboratory (LSC)
	IC-UNICAMP
	http://www.lsc.ic.unicamp.br/


	This source code is part of the MPSoCBench Benchmark Suite, which is a free
	source-code benchmark for evaluation of Electronic Systemc Level designs.
	This benchmark is distributed with hope that it will be useful, but
	without any warranty.

*********************************************************************************/

/**
 * @file      tlm_memory.cpp
 * @author    Bruno de Carvalho Albertini
 *            Liana Duenha
 * 
 * @author    The ArchC Team
 *            http://www.archc.org/
 *
 *            Computer Systems Laboratory (LSC)
 *            IC-UNICAMP
 *            http://www.lsc.ic.unicamp.br/
 * 
 * @version   0.1
 * @date      Sun, 02 Apr 2006 08:07:46 -0200
 * @brief     Implements a ac_tlm memory.
 *
 * @date      Wed, 30 Oct 2012 
 * @brief     Implements a TLM 2.0 memory.
 
 * @attention Copyright (C) 2002-2005 --- The ArchC Team
 * 
 *   This library is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU Lesser General Public
 *   License as published by the Free Software Foundation; either
 *   version 2.1 of the License, or (at your option) any later version.
 * 
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   Lesser General Public License for more details.
 * 
 * 
 */

//////////////////////////////////////////////////////////////////////////////
// Standard includes
// SystemC includes
// ArchC includes


#include "tlm_diretorio.h"
#include "tlm_payload_dir_extension.h"
using user::tlm_payload_dir_extension;


// If you don't want to measure dir access, modify measures_dir to 0
#define measures 1

long  unsigned int count_dir = 0;
FILE *local_dir_file;
FILE *global_dir_file;

using user::tlm_diretorio;
using tlm::tlm_command;
using tlm::TLM_READ_COMMAND;
using tlm::TLM_WRITE_COMMAND;

tlm_diretorio::tlm_diretorio(sc_module_name module_name) :
  sc_module( module_name ),
  target_export("iport")
{
    /// Binds target_export to the memory
    target_export( *this );
    value = 0;
	dir = new Diretorio();
	local_dir_file = fopen ("dir_acess.txt","a");
    
}

/// Destructor
tlm_diretorio::~tlm_diretorio() {
  
 if (measures) 
  {
     global_dir_file = fopen (GLOBAL_FILE_MEASURES_NAME,"a");
     
     fprintf(global_dir_file, "\nLock Access:\t%ld", count_dir);
     fclose (local_dir_file);
     fclose (global_dir_file);
  }
 delete dir;
}

bool tlm_diretorio::read_dir()
{
	return true;
}
bool tlm_diretorio::write_dir()
{
	return true;
}
uint32_t tlm_diretorio::readm(uint32_t &d )
{
        if(d != 0x0)
		return 0x1;

	else
		return d;

}

void tlm_diretorio::b_transport( ac_tlm2_payload &payload, sc_core::sc_time &time_info ) {
	//cout << "DIR IN" <<endl;
	tlm_payload_dir_extension *payloadExt;
   time_info = time_info + sc_core::sc_time(1,SC_NS);
   int nCache=-1;
   bool validation=false;
   count_dir++;
   payload.get_extension(payloadExt);
   //payload.release_extension(payloadExt);
   if(payloadExt != 0)
   {
	    nCache = payloadExt->getnumberCache();
		uint32_t printAddress =-1;
		printAddress= payloadExt->getAddress();
		int cacheIndex = payloadExt->getCacheIndex();
		int regra = payloadExt->getRule();
		
		//cout << "DIR cacheIndex " << cacheIndex<<endl;
		//cout << endl << "ADDRESS:" << payloadExt->getAddress() <<endl;
		if(count_dir<2000)
			fprintf(local_dir_file, "\nDir Access:\t%ld : nCache %i Address: %lu", count_dir, nCache, (unsigned long) printAddress);
		
		if(regra == 1)
		{
			//cout << "regra 1" << endl;
			//cout << "read: cacheIndex " << cacheIndex << " printAddress: " << printAddress <<endl;
			dir->validate(nCache, printAddress, cacheIndex);
			//validation=true;
			//payloadExt->setValidation(validation);
		}
		if(regra==2)
		{
			//cout << "regra 2" << endl;
			//cout << "write: cacheIndex " << cacheIndex << " printAddress: " << printAddress <<endl;
			//dir->validate(nCache, printAddress, cacheIndex);
			dir->unvalidate(nCache, printAddress);
			fprintf(local_dir_file, "WRITE, Validated target and UNvalidated the rest");
		}
		if(regra == 3)
		{
			//cout << "regra 3" << endl;
			validation = dir->checkValidation(nCache, printAddress);
			payloadExt->setValidation(validation);
		}
		//dir->validate(nCache, printAddress);
		//cout << "FUNC: " << regra << " nCache: " << nCache << " printAddress: " << printAddress << " cacheIndex: " << cacheIndex << " Validation: " << validation<<endl;
   }
  //cout << "DIR Validation: " << validation << endl;
   //cout << "diretorio validation: " << payloadExt->getValidation()<<endl;
   tlm_command command = payload.get_command();
   uint32_t addr = (uint32_t) payload.get_address();
   /*
   if(addr == 0x30000000)
   {
	   cout << "Caminhou pela rede com sucesso! chegou ao b_transport do tlm_diretorio!" <<endl;
   }
	* */
   unsigned char* data_pointer = payload.get_data_ptr();
  
   unsigned int len = payload.get_data_length();
   
   unsigned int resp;

   payload.set_response_status(tlm::TLM_OK_RESPONSE);    
   
   switch(command) {

	case TLM_READ_COMMAND :     // Packet is a READ one
	
		// CORRETO !
		if (readm(value)!=0) resp = 1;
		else resp = 0;

		//*((uint32_t*)data_pointer) = resp;

		//*((uint32_t*)data_pointer) = 0;

		//*((uint32_t*)data_pointer) = value;
		

		value = 0x1;
		if (LOCK_DEBUG)
		printf("\nTLM LOCK B_TRANSPORT: read response--> %d value-->%d",resp,value);

                break; 

	case TLM_WRITE_COMMAND:     // Packet is a WRITE
	        
		/*if (len == 1) value = *((uint8_t*)data_pointer);
		else if (len == 2) value = *((uint16_t*)data_pointer); 			
		else if (len == 4) value = *((uint32_t*)data_pointer);
		else if (len == 8) value = *((uint64_t*)data_pointer);
		*/


		if (*((uint32_t*)data_pointer)==0 ) 
			value = 0;
		else 
			value = 1;

		
		if (LOCK_DEBUG)
		printf("\nTLM LOCK B_TRANSPORT: write %d in value, *data_pointer-->%d",value,*((uint32_t*)data_pointer));

	
    		break;
    default:

    	printf("LOCK TRANSPORT --> COMMAND %d IS NOT IMPLEMENTED", command);

    	break;
    }
   // cout << "DIR OUT" <<endl;
   return;
    
  }





