#include "RoqmeDebug.h"

namespace Roqme {

RoqmeDebug::RoqmeDebug(const DebugMode& mode):mode(mode)
{
	
}

RoqmeDebug::~RoqmeDebug()
{
	if(ofile.is_open())
		ofile.close();
	
}

void RoqmeDebug::start()
{
	if(!ofile.is_open() && (mode == DebugMode::FILE || mode == DebugMode::ALL))
		ofile.open(getCurrentTimeStamp());
		//ofile.open("/home/zotac/QosLog.txt");
}

void RoqmeDebug::stop()
{
	if(ofile.is_open() && (mode ==  DebugMode::FILE || mode == DebugMode::ALL))
		ofile.close();
}

void RoqmeDebug::roqmeDebug(RoqmeDebug::ContextType type, const std::string& name, const std::string& value)
{
	if(type == RoqmeDebug::ContextType::INT)
		roqmeDebug("INT", name, value);
	else if(type == RoqmeDebug::ContextType::UINT)
		roqmeDebug("UINT", name, value);
	else if(type == RoqmeDebug::ContextType::BOOLEAN)
		roqmeDebug("BOOLEAN", name, value);
	else if(type == RoqmeDebug::ContextType::DOUBLE)
		roqmeDebug("DOUBLE", name, value);
	else if(type == RoqmeDebug::ContextType::EVENT)
		roqmeDebug("EVENT", name, value);
	else if(type == RoqmeDebug::ContextType::ENUM)
		roqmeDebug("ENUM", name, value);
}

void RoqmeDebug::roqmeDebug(const std::string& type, const std::string& name, const std::string& value)
{
	std::stringstream sstream;
	sstream << "[ " << getCurrentTimeStamp(true) << " ]: " << type << " " << name << " " << value << "\n";	

	if(mode == DebugMode::FILE || mode == DebugMode::ALL)
		ofile << sstream.str();
	if (mode == DebugMode::STANDARD_OUTPUT || mode == DebugMode::ALL)
		std::cout << sstream.str();
		
}

std::string RoqmeDebug::getCurrentTimeStamp(bool withSinceEpoch)
{
	using std::chrono::system_clock;
	std::stringstream ss;
	auto currentTime = std::chrono::system_clock::now();
	char buffer[80];
	long currentSinceEpoch = currentTime.time_since_epoch().count();
	auto transformed = currentSinceEpoch / 1000000;
	auto millis = transformed % 1000;
	std::time_t tt = system_clock::to_time_t(currentTime);
	auto timeinfo = localtime(&tt);

	strftime (buffer, 80, "%F %H:%M:%S", timeinfo);
	
	if(withSinceEpoch)
	{
		ss << currentSinceEpoch;
		sprintf(buffer, "%s:%03d %s", buffer, static_cast<int>(millis), ss.str().c_str());
	}
	else
	{
		sprintf(buffer, "%s:%03d", buffer, static_cast<int>(millis));
	}

	return std::string(buffer);
}

}
