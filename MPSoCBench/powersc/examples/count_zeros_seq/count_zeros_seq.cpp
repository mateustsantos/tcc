#include "count_zeros_seq.h"

/*
 *  SC_METHOD: comb_logic()
 *    finds a singular run of zeros and counts them
 */
void count_zeros_seq::comb_logic() 
{
  set_defaults();
  
	if (read.read()) {
		if (seenTrailing.read() && (data.read() == 0)) {
			new_is_legal.write( sc_bit(false) );
			new_zeros.write( 0 );
			new_data_ready.write( sc_bit(true) );
		} else if (seenZero.read() && (data.read() == 1)) {
			new_seenTrailing.write( sc_bit(true) );
		} else if (data.read() == 0) {
			new_seenZero.write( sc_bit(true) );
			new_zeros.write( zeros_s.read() + 1 );
		}
  
		if (bits_seen.read() == MAX_BIT_READ) {
			new_data_ready.write( sc_bit(true) );
		} else {
			new_bits_seen.write( bits_seen.read() + 1 );
		}
	} 
}

/*
 *  SC_METHOD: seq_logic()
 *    All registers have asynchronous resets
 */
void count_zeros_seq::seq_logic() 
{
	if (reset.read()) {
		zeros_s.write( 0 );
		bits_seen.write( 0 );
		seenZero.write( sc_bit(false) );
		seenTrailing.write( sc_bit(false) );
		is_legal_s.write( sc_bit(true) );
		data_ready_s.write( sc_bit(false) );
	} else {
		zeros_s = new_zeros;
		bits_seen = new_bits_seen;
		seenZero = new_seenZero;
		seenTrailing = new_seenTrailing;
		is_legal_s = new_is_legal;
		data_ready_s = new_data_ready;
	}
}

/*
 *  SC_METHOD: assign_outputs()
 *  Zero time assignments of signals to their associated outputs
 */
void count_zeros_seq::assign_outputs() 
{
	zeros = zeros_s;
	is_legal = is_legal_s;
	data_ready = data_ready_s;
}

/*
 *   method: set_defaults()
 *     sets the default values of the new_* signals for the comb_logic
 *     process.
 */
void count_zeros_seq::set_defaults() 
{
	new_is_legal = is_legal_s;
	new_seenZero = seenZero;
	new_seenTrailing = seenTrailing;
	new_zeros = zeros_s;
	new_bits_seen = bits_seen;
	new_data_ready = data_ready_s;
}
