/*
 * main.cpp
 *
 *  Created on: 04.05.2013
 *      Author: pavel
 */

#include <iostream>

#include <boost/program_options.hpp>

#include "OGRETestApp.h"

int main( int argc, char* argv[] ){
	namespace po = boost::program_options;

	const char* usage = "Usage: \n"
			"./ogre_test -p <path to plugin config> -r <path to resource config>\n";

	po::options_description desc("OGRE test general description");
	desc.add_options()
			("plugins,p",   po::value<std::string>(), "path to plugins.cfg")
			("resources,r", po::value<std::string>(), "path to resources.cfg")
			;

	po::variables_map vm;

	try{
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);
	}catch(...){
		desc.print(std::cerr);
	}

	if(!vm.count("plugins")){
		desc.print(std::cerr);
		std::cerr << usage << std::endl;
		return 1;
	}
	if(!vm.count("resources")){
		desc.print(std::cerr);
		std::cerr << usage << std::endl;
		return 1;
	}

	ogre_test::OGRETestApp app(vm["plugins"].as<std::string>().c_str(), vm["resources"].as<std::string>().c_str());
	app.run();

	return 0;
}


