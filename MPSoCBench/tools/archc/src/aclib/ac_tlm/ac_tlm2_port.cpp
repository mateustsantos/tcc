/**
 * @file      ac_tlm2_port.cpp
 * @author    Liana Duenha
 *
 * @author    The ArchC Team
 *            http://www.archc.org/
 *
 *            Computer Systems Laboratory (LSC)
 *            IC-UNICAMP
 *            http://www.lsc.ic.unicamp.br/
 * 
 * @date      22, October, 2012
 * @brief     Defines the ArchC TLM 2.0  port.

 *
 * @attention Copyright (C) 2002-2012 --- The ArchC Team
 *
 */

//////////////////////////////////////////////////////////////////////////////


// Standard includes

// SystemC includes

// ArchC includes
#include "ac_tlm2_port.H"
#include "ac_tlm2_payload.H"
#define	DIR_ADDRESS		   0x30000000

// If you want to debug TLM 2.0, please uncomment the next line

//#define debugTLM2

// Constructors

ac_tlm2_port::ac_tlm2_port(char const* nm, uint32_t sz) : name(nm), size(sz) {

 payload = new ac_tlm2_payload();
 payloadExt = new tlm_payload_dir_extension();
 }

//////////////////////////////////////////////////////////////////////////////
/** 
 * Reads a single word.
 * 
 * 
 */
void ac_tlm2_port::read(ac_ptr buf, uint32_t address, int wordsize,sc_core::sc_time& time_info)
{
  	//sc_core::sc_time time_info;



	unsigned char buffer[64];

	payload->set_command(tlm::TLM_READ_COMMAND);
	payload->set_address((sc_dt::uint64)address);
	payload->set_data_ptr(buffer);
	
	if (wordsize==8)	payload->set_data_length(sizeof(uint8_t));
	else if (wordsize==16)	payload->set_data_length(sizeof(uint16_t));
	else if (wordsize==32)	payload->set_data_length(sizeof(uint32_t));
	else 
	{	
		printf("*** AC_TLM2_PORT READ: wordsize-->%d not supported ****", wordsize);
		exit(0);
	}

	#ifdef debugTLM2 
	printf("\n\nAC_TLM2_PORT READ: command-->%d address-->%ld",tlm::TLM_READ_COMMAND, address);
	#endif

	(*this)->b_transport(*payload, time_info);

	uint8_t data8;
	uint16_t data16;
	uint32_t data32;

  	if (payload->is_response_ok()) 
	{
	   switch (wordsize) 
	   {
	      case 8:
	       	data8 = *((uint8_t*)payload->get_data_ptr());
		*(buf.ptr8) = ((uint8_t*)&data8)[0];
	    #ifdef debugTLM2
		printf("\nAC_TLM2_PORT READ: wordsize-->%d  data-->%d",wordsize,*(buf.ptr8));
		#endif



        	break;
	      case 16:
	      
		data16 = *((uint16_t*)payload->get_data_ptr());


		*(buf.ptr16) = ((uint16_t*)&data16)[0];

		//buf.ptr8= (uint8_t*)buf.ptr16;


	  	#ifdef debugTLM2 
                printf("\nAC_TLM2_PORT READ: wordsize-->%d  data-->%d",wordsize,*(buf.ptr16));
		#endif



                break;
	      case 32:
	       
		data32 = *((uint32_t*)payload->get_data_ptr());
		*(buf.ptr32) = ((uint32_t*)&data32)[0];


		//buf.ptr8 = (uint8_t*)buf.ptr32;

        #ifdef debugTLM2
		printf("\nAC_TLM2_PORT READ: wordsize-->%d  data-->%d",wordsize,*(buf.ptr32));
		#endif





        	break;
	      case 64:
	      default:
        	printf("*** AC_TLM2_PORT READ: wordsize-->%d not supported ****", wordsize);
		exit(0);
	        break;
	   }
  	}
	else 
	{
		printf("\nAC_TLM2_PORT READ ERROR");
		exit(0);
	}
}

/* read n_words */

void ac_tlm2_port::read(ac_ptr buf, uint32_t address,
                         int wordsize, int n_words,sc_core::sc_time &time_info) {


	//sc_core::sc_time time_info = sc_core::sc_time(0, SC_NS);
	payload->set_command(tlm::TLM_READ_COMMAND);
	

	unsigned char p[64];
	unsigned int i;
	
	#ifdef debugTLM2 
	printf("\n\nAC_TLM2_PORT READ N_WORDS: wordsize--> %d command-->%d address-->%ld",wordsize,tlm::TLM_READ_COMMAND, address);
	#endif

	switch (wordsize) 
	{
	    case 8:

   	    for( i=0; i<n_words; i++)
  		{	
			payload->set_address(address +i);
			payload->set_data_length(sizeof(uint8_t));
			payload->set_data_ptr(p);

			(*this)->b_transport(*payload, time_info); 
			
			for (int j = 0; (i < n_words) && (j < 4); j++, i++) {
				(buf.ptr8)[i] = ((uint8_t*)p)[j];
			}
			i--;

   		}
		break;
   
 	  case 16:



		for( i=0; i<n_words; i++)
  		{
			payload->set_address(address + (i * sizeof(uint16_t)));
			payload->set_data_length(sizeof(uint16_t));
			payload->set_data_ptr(p);

			(*this)->b_transport(*payload, time_info); 
			
			for (int j = 0; (i < n_words) && (j < 2); j++, i++) {
				buf.ptr16[i] = ((uint16_t*)p)[j];

			}
			i--;


		}
       		break;
              
	  case 32:
              
                         
		for( i=0; i<n_words; i++)
  		{	

			payload->set_address(address + (i * sizeof(uint32_t)));
			payload->set_data_length(sizeof(uint32_t));
		    payload->set_data_ptr(p);

			(*this)->b_transport(*payload, time_info);  	

            buf.ptr32[i]= *((uint32_t*)p);


   		}
        break;
  	  case 64:
  		printf("*** AC_TLM2_PORT READ: wordsize-->%d not supported ****", wordsize);
	  default:
		break;
        }
}

///*

bool ac_tlm2_port::read_dir(uint32_t address, int cacheIndex, int nCache, sc_core::sc_time& time_info)
{
	int rule=1;
	//usa o read como base
	//unsigned char buffer[64];
	//tlm_payload_dir_extension *payloadExt;
	//cout << "AC TLM2 IN1" <<endl;
	payloadExt->setNumberCache(nCache);
	//cout << "TLM2 read cacheIndex "<< cacheIndex<<endl;
	//cout << "AC TLM2 IN2" <<endl;
	payloadExt->setAddress(address);
	//cout << "AC TLM2 IN3" <<endl;
	payloadExt->setCacheIndex(cacheIndex);
	//cout << "AC TLM2 IN4" <<endl;
	payloadExt->setRule(rule);
	//cout << "AC TLM2 IN5" <<endl;
	
	payload->set_extension(payloadExt);
	//cout << "AC TLM2 IN6" <<endl;
	//cout << "get read cacheIndex da tlm2 " << payloadExt->getCacheIndex() <<endl;
    payload->set_command(tlm::TLM_READ_COMMAND);
    //cout << "AC TLM2 IN7" <<endl;
    payload->set_address((sc_dt::uint64)DIR_ADDRESS);
    //cout << "AC TLM2 IN8" <<endl;
	
	//return true;
    //payload->set_data_ptr(buffer);
	payload->set_data_length(sizeof(uint32_t));
	//cout << "AC TLM2 IN9" <<endl;
	(*this)->b_transport(*payload, time_info);
	//cout << "AC TLM2 IN10" <<endl;
	//payload.release_extension(payloadExt);
	//cout << "get read validation " << payloadExt->getValidation() << endl; 
	if (payload->is_response_ok())
	{
		//cout << "AC TLM2 OUT" <<endl;
		//cout << "tlm2PORT validation: " << payloadExt->getValidation()<<endl;
		return payloadExt->getValidation();
	}
	//cout << "AC TLM2 OUT" <<endl;
	
	return false;
}
bool ac_tlm2_port::write_dir(uint32_t address, int cacheIndex, int nCache, sc_core::sc_time& time_info)
{
	int rule=2;
	payloadExt->setNumberCache(nCache);
	//cout << "TLM2 write cacheIndex "<< cacheIndex<<endl;
	payloadExt->setAddress(address);
	payloadExt->setCacheIndex(cacheIndex);
	payloadExt->setRule(rule);
	payload->set_extension(payloadExt);
	
	//cout << "get write cacheIndex da tlm2 " << payloadExt->getCacheIndex() <<endl; 
	
    payload->set_command(tlm::TLM_READ_COMMAND);
    payload->set_address((sc_dt::uint64)DIR_ADDRESS);
	
	//return true;
    //payload->set_data_ptr(buffer);
	payload->set_data_length(sizeof(uint32_t));
	(*this)->b_transport(*payload, time_info);
	//payload.release_extension(payloadExt);
	//cout << "get write validation " << payloadExt->getValidation() << endl;
	if (payload->is_response_ok())
	{
		//cout << "AC TLM2 OUT" <<endl;
		//cout << "tlm2PORT validation: " << payloadExt->getValidation()<<endl;
		return payloadExt->getValidation();
	}
	//cout << "AC TLM2 OUT" <<endl;
	return true;
}
bool ac_tlm2_port::check_dir(uint32_t address,  int nCache, sc_core::sc_time& time_info)
{
	int rule=3;
	//usa o read como base
	//unsigned char buffer[64];
	//tlm_payload_dir_extension *payloadExt;
	//cout << "AC TLM2 IN" <<endl;
	payloadExt->setNumberCache(nCache);
	payloadExt->setAddress(address);
	payloadExt->setRule(rule);
	
	payload->set_extension(payloadExt);
	
    payload->set_command(tlm::TLM_READ_COMMAND);
    payload->set_address((sc_dt::uint64)DIR_ADDRESS);
	
	//return true;
    //payload->set_data_ptr(buffer);
	payload->set_data_length(sizeof(uint32_t));
	(*this)->b_transport(*payload, time_info);
	//payload.release_extension(payloadExt);

	if (payload->is_response_ok())
	{
		//cout << "AC TLM2 OUT" <<endl;
		//cout << "tlm2PORT validation: " << payloadExt->getValidation()<<endl;
		return payloadExt->getValidation();
	}
	//cout << "AC TLM2 OUT" <<endl;
	return payloadExt->getValidation();
	//return false;
}
//*/
/** 
 * Writes a single word.
 * 
  */
void ac_tlm2_port::write(ac_ptr buf, uint32_t address, int wordsize,sc_core::sc_time &time_info) {

  //sc_core::sc_time time_info = sc_core::sc_time(0, SC_NS);

  unsigned char p[64];
  unsigned int i;


  
  #ifdef debugTLM2 
  printf("\n\nAC_TLM2_PORT WRITE: wordsize--> %d command-->%d address-->%ld",wordsize,tlm::TLM_WRITE_COMMAND, address);
  #endif


  switch (wordsize) {
  case 8:
    payload->set_command(tlm::TLM_READ_COMMAND);
    payload->set_address((uint64_t)address);
    payload->set_data_length(sizeof(uint8_t));
    payload->set_data_ptr(p);
    
    (*this)->b_transport(*payload, time_info); 
    
    payload->set_command(tlm::TLM_WRITE_COMMAND);
    

    ((uint8_t*)p)[0] = *(buf.ptr8);

    


    (*this)->b_transport(*payload, time_info);  
    
    break;
  case 16:
    payload->set_command(tlm::TLM_READ_COMMAND);
    payload->set_address((uint64_t)address);
    payload->set_data_length(sizeof(uint16_t));
    payload->set_data_ptr(p);

    (*this)->b_transport(*payload, time_info); 

     payload->set_command(tlm::TLM_WRITE_COMMAND);
    

     //((uint16_t*)p)[0] = *((uint16_t*)buf.ptr8);

     ((uint16_t*)p)[0] = *(buf.ptr16);


    (*this)->b_transport(*payload, time_info);  
    break;
 
 case 32:
    payload->set_address((uint64_t)address);
    payload->set_command(tlm::TLM_WRITE_COMMAND);
    payload->set_data_ptr(p);
    payload->set_data_length(sizeof(uint32_t));



    //((uint32_t*)p)[0]= *((uint32_t*)buf.ptr8);


    ((uint32_t*)p)[0]=*(buf.ptr32);



    payload->set_data_ptr(p);    
    (*this)->b_transport(*payload, time_info);  
    break;

  case 64:
  default:
	printf("\n\nAC_TLM2_PORT WRITE: wordsize not implemented");
    break;
  }
}

/** 
 * Writes multiple words.
 * 
 
 */
void ac_tlm2_port::write(ac_ptr buf, uint32_t address,
                         int wordsize, int n_words,sc_core::sc_time &time_info) {




  //sc_core::sc_time time_info = sc_core::sc_time(0, SC_NS);
  payload->set_command(tlm::TLM_WRITE_COMMAND);

  unsigned char p[64];
  unsigned int i;


  #ifdef debugTLM2 
  printf("\n\nAC_TLM2_PORT WRITE N_WORDS: command-->%d address-->%ld",tlm::TLM_WRITE_COMMAND, address);
  #endif



		for( i=0; i<n_words; i++)
  		{	

			payload->set_data_length(sizeof(uint32_t));
			payload->set_address(address + (i * sizeof(uint32_t)));
		    payload->set_data_ptr(p);

			*((uint32_t*)p) = buf.ptr32[i];


		  	#ifdef debugTLM2
			printf("\nAC_TLM2_PORT WRITE: n_words--> %d  wordsize-->%d  i--> %d command-->  data-->%d",n_words, wordsize,i, payload->get_command(), *((uint32_t*)p));
			#endif

			(*this)->b_transport(*payload, time_info);  
   		}

}



string ac_tlm2_port::get_name() const {
  return name;
}

uint32_t ac_tlm2_port::get_size() const {
  return size;
}

/** 
 * Locks the device.
 * 
 */
void ac_tlm2_port::lock()
{
	printf("\nAC_TLM2_PORT::LOCK ERROR --> NOT IMPLEMENTED\n");  
	exit(0);
	
}

/** 
 * Unlocks the device.
 * 
 */
void ac_tlm2_port::unlock()
{

	printf("\nAC_TLM2_PORT::UNLOCK ERROR --> NOT IMPLEMENTED\n");  
	exit(0);
}

//////////////////////////////////////////////////////////////////////////////

// Destructors

/**
 * Default (virtual) destructor.
 * @return Nothing.
 */
ac_tlm2_port::~ac_tlm2_port() {

 delete payload;
}


