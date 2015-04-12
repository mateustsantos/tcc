#ifndef _AC_CACHE_H_INCLUDED_
#define _AC_CACHE_H_INCLUDED_

#include "ac_cache_bhv.H"
#include "ac_cache_trace.H"



struct write_back_state {
	bool valid;
	bool dirty;
	write_back_state() : valid(false), dirty(false) {}
	bool is_invalid() {
		return (!valid);
	}
	bool is_dirty() {
		return (valid && dirty);
	}
	void set_valid() {
		valid = true;
		dirty = false;
	}
	void set_dirty() {
		dirty = true;
	}
	void print(std::ostream &fsout) {
		if (valid) fsout << 'V';
		else fsout << 'I';
		if (dirty) fsout << 'D';
		else fsout << 'C';
	}
};

struct write_through_state {
	bool valid;
	write_through_state() : valid(false) {}
	bool is_invalid() {
		return (!valid);
	}
	void set_valid() {
		valid = true;
	}
	void print(std::ostream &fsout) {
		if (valid) fsout << 'V';
		else fsout << 'I';
	}
};

struct cache_statistics {
	unsigned long long read_hit;
	unsigned long long read_miss;
	unsigned long long write_hit;
	unsigned long long write_miss;
	unsigned long long evictions;
};

template <
	unsigned index_size,
	unsigned block_size,
	unsigned associativity,
	typename cpu_word,
	typename backing_store,
	typename replacement_policy,
	typename address = unsigned
>
class ac_write_back_cache {
	cache_bhv<index_size, block_size, associativity, cpu_word, address, 
	          write_back_state, replacement_policy> cache;
	backing_store &memory;
	ac_cache_trace *cache_trace;
	bool trace_active;
	int idCache;
	 void setId (int id)
    {
   		idCache = id;
    }
	int getId ()
    {
   		return idCache;
    }
	
	address byte_to_word(address a) {
		return a/sizeof(cpu_word);
	}
	address word_to_byte(address a) {
		return a*sizeof(cpu_word);
	}
	
	ac_write_back_cache(const ac_write_back_cache &, int id);
	
	public:
	ac_write_back_cache(backing_store &memory_, int id) : memory(memory_), trace_active(false) {
	}
	
	~ac_write_back_cache() {
		if (trace_active) delete cache_trace;
	}
	
	void set_trace(std::ostream &o) {
		if (trace_active) delete cache_trace;
		cache_trace = new ac_cache_trace(o);
		trace_active = true;
	}
	

	  const cpu_word *read(address a, unsigned length) {

		//printf("\nAC_CACHE WB::read -> address=%x  length=%d", a, length);

		address b = byte_to_word(a);
		
		if(a >= 536870912){
			a = a/block_size*block_size;
			const cpu_word *d = memory.read_block(a, sizeof(cpu_word));
			return d;
		}
		
		if (!cache.get_block_for_read(b)) {
			cache.get_available_block();
			if (cache.block_status().is_dirty()) {
				memory.write_block(word_to_byte(cache.block_address()),
									     cache.read_block(), block_size);
			}
			a = a/block_size*block_size;
			const cpu_word *d = memory.read_block(a, block_size);
			cache.write_block(d);
			cache.block_status().set_valid();
		}
		if (trace_active) cache_trace->add(trace_read, word_to_byte(b), length);
		return cache.read_block_single();
	}





	  void write(address a, const cpu_word *d, unsigned length) {

		  //printf("\nAC_CACHE WB::write -> address=%x  length=%d", a, length);


		address b = byte_to_word(a);
		
		if(a >= 0x20000000){
			a = a/block_size*block_size;
			memory.write_block(a, d, sizeof(cpu_word));
			return;	
		}
		
		if (!cache.get_block_for_write(b)) {
			cache.get_available_block();
			if (cache.block_status().is_dirty()) {
				memory.write_block(word_to_byte(cache.block_address()),
					     cache.read_block(), block_size);
			}
			a = a/block_size*block_size;
			const cpu_word *d = memory.read_block(a, block_size);
			cache.write_block(d);
			cache.block_status().set_valid();
		}
		if (trace_active) cache_trace->add(trace_write, word_to_byte(b), length);
		cache.write_block_single(d, length);
		cache.block_status().set_dirty();
	}



	uint32_t get_size() {
		return memory.get_size();
	}
	
	void get_statistics(cache_statistics *statistics) {
		statistics->read_hit = cache.number_read_hit();
		statistics->read_miss = cache.number_read_miss();
		statistics->write_hit = cache.number_write_hit();
		statistics->write_miss = cache.number_write_miss();
		statistics->evictions = cache.number_block_eviction();
	}
	
	void print(std::ostream &fsout) {
		fsout << cache;
	}
	
	void print_statistics(ostream &out) {
		cache.print_statistic(out);
	}
};

template <
	unsigned index_size,
	unsigned block_size,
	unsigned associativity,
	typename cpu_word,
	typename backing_store,
	typename replacement_policy,
	typename address = unsigned
>
class ac_write_through_cache {
	cache_bhv<index_size, block_size, associativity, cpu_word, address,
	          write_through_state, replacement_policy> cache;
	backing_store &memory;
	ac_cache_trace *cache_trace;
	bool trace_active;
	int idCache;
	 void setId (int id)
    {
	    cout << "ID SET: " << id <<endl;
   		idCache = id;
    }
	int getId ()
    {
   		return idCache;
    }
	address byte_to_word(address a) {
		return a/sizeof(cpu_word);
	}
	address word_to_byte(address a) {
		return a*sizeof(cpu_word);
	}
	
	ac_write_through_cache(const ac_write_through_cache &, int id)
	{
		cout << "ID: "<< id <<endl;
		setId(id);
	}
	
	public:
	ac_write_through_cache(backing_store &memory_, int id) : memory(memory_), trace_active(false) {
		cout << "ID: "<< id <<endl<<endl<<endl<<endl;
		setId(id);
		//memory.setBlockSize (block_size);
	}
	~ac_write_through_cache() {
		if (trace_active) delete cache_trace;
	}

	void set_trace(std::ostream &o) {
		if (trace_active) delete cache_trace;
		cache_trace = new ac_cache_trace(o);
		trace_active = true;
	}
	
	const cpu_word *read(address a, unsigned length) {

		    //printf("\nAC_CACHE WT::read -> address=%x  length=%d", a, length);
			//cout << "ID: " << getId() <<endl;
			address b = byte_to_word(a);
			//if (!cache.get_block_for_read(b) || !memory.check_dir((uint32_t) a, getId())) {
			
			if(a == 0x20000000){
				a = a/block_size*block_size;
				//cout << "cache read lock..." <<endl;
				const cpu_word *d = memory.read_block(a, length);
				//cout << "READ LOCK: " << *d << " PROC: " << getId()<< endl;
				return d;
			}
			//cout << "READ EM LOOP address: " << a << " length: " << length <<endl;
			a = a/block_size*block_size;
			int cacheIndex=0;
			/*
			bool pepino=false;
			if(a == 56256)
				pepino = true;
			if(a == 56240)
				pepino = true;
				*/
			//if (!cache.get_block_for_read(b)) {
			//if (!memory.check_dir((uint32_t) a, getId())) {
				
				//cout << "predicacao do check_dir:" << memory.check_dir((uint32_t) a, getId())<<endl;
				//memory.check_dir((uint32_t) a, getId());
				//
				//cout << "CHECK_DIR" <<endl;
				bool cdir = (!(memory.check_dir((uint32_t) a, getId())));
				
					if ( !cache.get_block_for_read(b) || cdir) {
					//if (!cache.get_block_for_read(b) || true){
						cacheIndex = cache.get_available_block();
						//cout << "cache read cacheIndex: "<< cacheIndex << endl;
						//cout << "READ_DIR" <<endl;
						memory.read_dir((uint32_t) a, cacheIndex, getId());
						const cpu_word *d = memory.read_block(a, block_size);
						cache.write_block(d);
						cache.block_status().set_valid();
					}
			//}
			
			if (trace_active) cache_trace->add(trace_read, word_to_byte(b), length);
			
			//const cpu_word *d = memory.read_block(a, block_size);
			//const cpu_word *cached = cache.read_block();
			//if(*cached != *d)
			//	cout << "INCORRETO" <<endl;	
			return cache.read_block_single();
		}

		void write(address a, const cpu_word *d, unsigned length) {

			//printf("\nAC_CACHE WT::write -> address=%x  length=%d", a, length);
   		    address b = byte_to_word(a);
   		    
			if(a == 0x20000000){
			a = a/block_size*block_size;
			//cout << "cache write lock..." <<endl;
			//cout << "WRITE LOCK: " << *d << " PROC: " << getId() << endl;
			memory.write_block(a, d, length);
			return;	
			}
			a = a/block_size*block_size;
			int cacheIndex=0;
			/*
			bool pepino=false;
			if(a == 56256)
				pepino = true;
			if(a == 56240)
				pepino = true;	
				*/
			//cout << "cache write cacheIndex: "<< cacheIndex << endl;
			
			//cout << "predicacao do check_dir:" << memory.check_dir((uint32_t) a, getId())<<endl;
			//
			//cout << "CHECK_DIR" <<endl;
			bool cdir;
			cdir = (!(memory.check_dir((uint32_t) a, getId())));
				if (!cache.get_block_for_write(b) || cdir) {
				//if (!cache.get_block_for_write(b) || true){
					cacheIndex = cache.get_available_block();
					//cout << "READ_DIR" <<endl;
					memory.read_dir((uint32_t) a, cacheIndex, getId());
					const cpu_word *tmp_d = memory.read_block(a, block_size);
					cache.write_block(tmp_d);
					cache.block_status().set_valid();
				}
			if (trace_active) cache_trace->add(trace_write, word_to_byte(b), length);
			
			//const cpu_word *dd = memory.read_block(a, block_size);
			//const cpu_word *cached = cache.read_block();
			//if(*cached != *dd)
			//	cout << "INCORRETO" <<endl;
				
			cache.write_block_single(d, length);
            memory.write_block(word_to_byte(cache.block_address()), cache.read_block(),block_size);
            //cout <<"WRITE_DIR" <<endl;
            memory.write_dir((uint32_t) a, cacheIndex, getId());
	}



	
	void get_statistics(cache_statistics *statistics) {
		statistics->read_hit = cache.number_read_hit();
		statistics->read_miss = cache.number_read_miss();
		statistics->write_hit = cache.number_write_hit();
		statistics->write_miss = cache.number_write_miss();
		statistics->evictions = cache.number_block_eviction();
	}
	
	uint32_t get_size() {
		return memory.get_size();
	}

	void print(std::ostream &fsout) {
		fsout << cache;
	}
	
	void print_statistics(ostream &out) {
		cache.print_statistic(out);
	}
};

#endif /* _AC_CACHE_H_INCLUDED_ */

