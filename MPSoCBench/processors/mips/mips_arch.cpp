/******************************************************
 * ArchC Resources Implementation file.               *
 * This file is automatically generated by ArchC      *
 * WITHOUT WARRANTY OF ANY KIND, either express       *
 * or implied.                                        *
 * For more information on ArchC, please visit:       *
 * http://www.archc.org                               *
 *                                                    *
 * The ArchC Team                                     *
 * Computer Systems Laboratory (LSC)                  *
 * IC-UNICAMP                                         *
 * http://www.lsc.ic.unicamp.br                       *
 ******************************************************/
 

#include "mips_arch.H"
#include "ac_cache_if.H"

mips_arch::mips_arch() :
  ac_arch_dec_if<mips_parms::ac_word, mips_parms::ac_Hword>(mips_parms::AC_MAX_BUFFER),
  ac_pc("ac_pc", 0),
  MEM_port("MEM_port", 536870912U),
  MEM(*this, MEM_port),
  IC(MEM,globalId),
  IC_if(IC),
  IC_port(*this, IC_if),
  DC(MEM,globalId),
  DC_if(DC),
  DC_port(*this, DC_if),
  RB("RB"),
  npc("npc", 0),
  hi("hi", 0),
  lo("lo", 0),
  id("id", 0) {

  ac_mt_endian = mips_parms::AC_MATCH_ENDIAN;
  ac_tgt_endian = mips_parms::AC_PROC_ENDIAN;

  IM = &IC_port;
  APP_MEM = &MEM;

}

int mips_arch::globalId = 0;