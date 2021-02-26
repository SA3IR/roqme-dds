#ifndef ROQMEDEBUG_H
#define ROQMEDEBUG_H

#include <iostream>
#include <sstream>
#include <chrono>
#include <fstream>
#include <sstream>

namespace Roqme 
{

class RoqmeDebug 
{
public:
	enum DebugMode { FILE, STANDARD_OUTPUT, ALL };
	enum ContextType { INT, UINT, DOUBLE, BOOLEAN, EVENT, ENUM };

	RoqmeDebug(const DebugMode& mode = DebugMode::ALL);
	~RoqmeDebug();

	void start();
	void stop();
	void roqmeDebug(const std::string& type, const std::string& name, const std::string& value);
	void roqmeDebug(ContextType type, const std::string& name, const std::string& value);


private:
	std::ofstream ofile;
	RoqmeDebug::DebugMode mode;
	std::string getCurrentTimeStamp(bool withSinceEpoch = false);
};

}

#endif
