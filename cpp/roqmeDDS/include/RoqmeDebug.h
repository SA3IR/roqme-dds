/*
 * This file belongs to the RoQME toolchain.
 * Copyright (C) 2019  University of Extremadura, University of Málaga, Biometric Vox.

 * RoQME is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * any later version.

 * RoQME is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * GNU GPLv3 link: http://www.gnu.org/licenses/gpl-3.0.html
 * 
 */

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
