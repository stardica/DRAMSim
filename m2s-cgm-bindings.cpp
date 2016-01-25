/*
 * m2s-cgm-bindings.cpp
 *
 *  Created on: Jan 23, 2016
 *      Author: stardica
 */

#include "DRAMSim.h"
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <fstream>

extern "C" {
#include "m2s-cgm-bindings.h"
}

using std::string;
using std::ostringstream;
using namespace::DRAMSim;

class call_back_container_t
{
	public:
		void read_complete(unsigned, uint64_t, uint64_t);
		void write_complete(unsigned, uint64_t, uint64_t);
}call_backs;

/* callback functors */
void call_back_container_t::read_complete(unsigned id, uint64_t address, uint64_t clock_cycle)
{
	printf("[Callback] read complete: %d 0x%016x cycle=%lu\n", id, address, clock_cycle);

	//calls function from C side here
	read_done_cpp(id, (long long unsigned) address, (long long unsigned) clock_cycle);

	return;
}

void call_back_container_t::write_complete(unsigned id, uint64_t address, uint64_t clock_cycle)
{
	printf("[Callback] write complete: %d 0x%016x cycle=%lu\n", id, address, clock_cycle);

	//calls function from C side here
	write_done_cpp(id, (long long unsigned) address, (long long unsigned) clock_cycle);

	return;
}

void power_callback(double a, double b, double c, double d)
{
	//printf("[Callback] power_callback\n");

	//calls function from C side here
	//power_done_cpp(a, b, c, d);

	return;
}


/*The following fucntions bind the C++ DRAMSim code with m2s-cgm's C code.*/
#ifdef __cplusplus
extern "C" {
#endif

void call_register_call_backs(struct dram_system_handler_t *mem, void (*read_done)(unsigned int, long long unsigned , long long unsigned),
			void (*write_done)(unsigned int, long long unsigned, long long unsigned), void (*report_power)(double bgpower, double burstpower, double refreshpower, double actprepower)){

	read_done_cpp = read_done;
	write_done_cpp = write_done;
	power_done_cpp = report_power;

	TransactionCompleteCB *read_cb = new Callback<call_back_container_t, void, unsigned, uint64_t, uint64_t> (&call_backs, &call_back_container_t::read_complete);
	TransactionCompleteCB *write_cb = new Callback<call_back_container_t, void, unsigned, uint64_t, uint64_t> (&call_backs, &call_back_container_t::write_complete);

	mem->RegisterCallbacks(read_cb, write_cb, power_callback);

	printf("cpp mem->RegisterCallbacks(read_cb, write_cb, power_callback);\n");
	return;
}


/*small test fucntion*/
void call_print_me(void){
	printf("print from DRAMSim_1\n");
	return;
}

/*sets up and returns pointer to new MultiChannelMemorySystem object*/
void *call_get_memory_system_instance(const char *dev, const char *sys, const char *pwd, const char *trc, unsigned int megsOfMemory, const char *visfilename){

	printf("getMemorySystemInstance()\n");

	std::string str_dev(dev);
	std::string str_sys(sys);
	std::string str_pwd(pwd);
	std::string str_trc(trc);
	std::string str_visfilename(visfilename);

	MultiChannelMemorySystem *mem = getMemorySystemInstance(str_dev, str_sys, str_pwd, str_trc, megsOfMemory, &str_visfilename);
	fflush(stderr);

	printf("getMemorySystemInstance() size %u\n", megsOfMemory);

	return mem;// mem;
}

int call_add_transaction(struct dram_system_handler_t *mem, int isWrite, unsigned int addr){

	//star todo look at these bools and figure out how to handle these...

	int return_val = 0;

	return_val = mem->addTransaction(isWrite, (uint64_t)addr);

	return return_val;
}

/*sets the cpu clock speed*/
void call_set_CPU_clock_speed(struct dram_system_handler_t *mem, unsigned int cpuClkFreqHz){

		/*MultiChannelMemorySystem *mem_1 = mem;*/
		mem->setCPUClockSpeed((uint64_t)cpuClkFreqHz);

		printf("call_set_CPU_clock_speed(%u)\n", cpuClkFreqHz);

	return;
}

void call_update(struct dram_system_handler_t *mem){

	mem->update();

	return;
}

void call_print_stats(struct dram_system_handler_t *mem, int finalStats){

	/*star todo make a bool?*/

	mem->printStats(finalStats);

	return;
}

void call_will_accept_transaction(struct dram_system_handler_t *mem, unsigned int addr){

	mem->willAcceptTransaction((uint64_t)addr);

	return;
}

void call_write_to_log_file(struct dram_system_handler_t *mem, const char * string){

	mem->getLogFile() << string << std::endl;

	return;
}

#ifdef __cplusplus
}
#endif
