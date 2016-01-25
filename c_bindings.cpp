/*
 * c_bindings.cpp
 *
 *  Created on: Jan 23, 2016
 *      Author: stardica
 */

#include "DRAMSim.h"
#include <stdio.h>
#include <string>
#include <stdlib.h>

using namespace::std;
using namespace::DRAMSim;



#ifdef __cplusplus
extern "C" {
#endif


void call_print_me(void){

	printf("print from DRAMSim_1\n");

	return;

}

	/*char dramsim_ddr_config_path[250] = "/home/stardica/Dropbox/CDA7919DoctoralResearch/Simulators/DRAMSim2/ini/DDR2_micron_16M_8b_x8_sg3E.ini";
	char dramsim_system_config_path[250] = "/home/stardica/Dropbox/CDA7919DoctoralResearch/Simulators/DRAMSim2/system.ini";
	char dramsim_vis_config_path[250] = "/home/stardica/Dropbox/CDA7919DoctoralResearch/Simulators/DRAMSim2/results";*/

extern "C" void *call_get_memory_system_instance(char *dev, char *sys, char *pwd,  char *trc, unsigned int megsOfMemory, char *visfilename){

	printf("print from DRAMSim_2 %s %s size %u\n", dev, sys, megsOfMemory);

	std::string str_dev(dev);
	std::string str_sys(sys);
	std::string str_pwd(pwd);
	std::string str_trc(trc);
	std::string str_visfilename(visfilename);

	MultiChannelMemorySystem *mem = getMemorySystemInstance(str_dev, str_sys, str_pwd, str_trc, megsOfMemory, &str_visfilename);

	return mem;// mem;
}

extern "C" void call_set_CPU_clock_speed(struct dram_system_handler_t *mem, unsigned int cpuClkFreqHz){

		/*MultiChannelMemorySystem *mem_1 = mem;*/

		printf("setting clock freq %u\n", cpuClkFreqHz);

		mem->setCPUClockSpeed((uint64_t)cpuClkFreqHz);

	return;
}

/*struct dram_system_handler_t* call_get_memory_system_instance(const string &dev, const string &sys, const string &pwd, const string &trc, unsigned megsOfMemory, std::string *visfilename=NULL){

	struct dram_system_handler_t *mem = NULL;

	mem = getMemorySystemInstance(dev, sys, pwd, trc, megsOfMemory, visfilename);

	printf("print from DRAMSim_2\n");

	return mem;
}*/


#ifdef __cplusplus
}
#endif


/*extern "C" void call_print_me_2(void){

	MultiChannelMemorySystem *mem_system = new MultiChannelMemorySystem;

	return mem_system->print_me_2();

}*/

/*extern "C" MultiChannelMemorySystem *call_get_memory_system_instance(const string &dev, const string &sys, const string &pwd, const string &trc, unsigned megsOfMemory, std::string *visfilename=NULL){

	MultiChannelMemorySystem *new_mem = NULL;

	new_mem = getMemorySystemInstance(dev, sys, pwd, trc, megsOfMemory, visfilename);

	return new_mem;

}*/
