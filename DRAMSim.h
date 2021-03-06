/*********************************************************************************
*  Copyright (c) 2010-2011, Elliott Cooper-Balis
*                             Paul Rosenfeld
*                             Bruce Jacob
*                             University of Maryland 
*                             dramninjas [at] gmail [dot] com
*  All rights reserved.
*  
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions are met:
*  
*     * Redistributions of source code must retain the above copyright notice,
*        this list of conditions and the following disclaimer.
*  
*     * Redistributions in binary form must reproduce the above copyright notice,
*        this list of conditions and the following disclaimer in the documentation
*        and/or other materials provided with the distribution.
*  
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
*  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
*  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
*  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
*  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
*  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*********************************************************************************/


#ifndef DRAMSIM_H
#define DRAMSIM_H
/*
 * This is a public header for DRAMSim including this along with libdramsim.so should
 * provide all necessary functionality to talk to an external simulator
 */
#include "Callback.h"
#include <string>
using std::string;

//star added this
#define dram_system_handler_t MultiChannelMemorySystem

namespace DRAMSim 
{

	class MultiChannelMemorySystem {
		public:
			bool addTransaction(bool isWrite, uint64_t addr);
			void setCPUClockSpeed(uint64_t cpuClkFreqHz);
			void update();
			void printStats(bool finalStats);
			bool willAcceptTransaction(); 
			bool willAcceptTransaction(uint64_t addr); //not needed for m2s because we can give the memory address.
			std::ostream &getLogFile();
			void RegisterCallbacks( TransactionCompleteCB *readDone, TransactionCompleteCB *writeDone,
					void (*reportPower)(double bgpower, double burstpower, double refreshpower, double actprepower));
			int getIniBool(const std::string &field, bool *val);
			int getIniUint(const std::string &field, unsigned int *val);
			int getIniUint64(const std::string &field, uint64_t *val);
			int getIniFloat(const std::string &field, float *val);
	};

	MultiChannelMemorySystem *getMemorySystemInstance(const string &dev, const string &sys, const string &pwd, const string &trc, unsigned megsOfMemory, std::string *visfilename=NULL);

	//star added these
	extern "C" void call_print_me(void);
	extern "C" void *call_get_memory_system_instance(const char *dev, const char *sys, const char *pwd, const char *trc, unsigned int megsOfMemory, const char *visfilename);
	extern "C" int call_add_transaction(struct dram_system_handler_t *mem, int isWrite, unsigned int addr);
	extern "C" void call_set_CPU_clock_speed(struct dram_system_handler_t *mem, unsigned int cpuClkFreqHz);
	extern "C" void call_update(struct dram_system_handler_t *mem);
	extern "C" void call_print_stats(struct dram_system_handler_t *mem, int finalStats);
	extern "C" void call_will_accept_transaction(struct dram_system_handler_t *mem, unsigned int addr);
	extern "C" void call_write_to_log_file(struct dram_system_handler_t *mem, const char * string);
	extern "C" void	call_register_call_backs(struct dram_system_handler_t *mem, void (*read_done)(unsigned int, long long unsigned, long long unsigned),
			void (*write_done)(unsigned int, long long unsigned, long long unsigned), void (*report_power)(double bgpower, double burstpower, double refreshpower, double actprepower));

}

#endif
