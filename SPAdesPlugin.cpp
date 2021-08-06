#include "PluginManager.h"
#include <stdio.h>
#include <stdlib.h>
#include "SPAdesPlugin.h"

void SPAdesPlugin::input(std::string file) {
 inputfile = file;
 std::ifstream ifile(inputfile.c_str(), std::ios::in);
 while (!ifile.eof()) {
   std::string filename;
   ifile >> filename;
   if (filename.length() != 0)
   fastqFiles.push_back(filename);
 }
}

void SPAdesPlugin::run() {
   
}

void SPAdesPlugin::output(std::string file) {
 // spades.py -o 02_SPAdes -1 $1 -2 $2 --careful
 // spades.py -o hyb_spades -1 $1 -2 $2 --nanopore $3
	std::string command;
 if (fastqFiles.size() == 2) {
   command = "spades.py -o "+file+" -1 "+std::string(PluginManager::prefix())+"/"+fastqFiles[0]+" -2 "+std::string(PluginManager::prefix())+"/"+fastqFiles[1]+" --careful";
 }
 else {
   command = "spades.py -o "+file+" -1 "+std::string(PluginManager::prefix())+"/"+fastqFiles[0]+" -2 "+std::string(PluginManager::prefix())+"/"+fastqFiles[1]+" --nanopore "+std::string(PluginManager::prefix())+"/"+fastqFiles[2];
 }
 std::cout << command << std::endl;

 system(command.c_str());

std::string copyCommand = "cp "+file+"/assembly_graph_with_scaffolds.gfa "+std::string(PluginManager::prefix());
 std::cout << copyCommand << std::endl;
 system(copyCommand.c_str());
}

PluginProxy<SPAdesPlugin> SPAdesPluginProxy = PluginProxy<SPAdesPlugin>("SPAdes", PluginManager::getInstance());
