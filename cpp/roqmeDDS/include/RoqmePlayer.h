#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <thread>
#include <vector>
#include "RoqmeDDSException.h"
#include "RoqmeWriterImpl.h"

namespace Roqme {

class RoqmePlayer {

public:
	void load(const std::string& fileName);
	void play();

	void playMiron();
	void loadMiron(const std::string& fileName);
private:

	typedef struct RoqmeContextInfo {
		long timestamp;
		std::string name;
		std::string type;
		std::string value;		
	}ContextInfo;
	std::vector<ContextInfo> context_v;

	Roqme::RoqmeEventWriter eventWr;
	Roqme::RoqmeEnumWriter enumWr;
	Roqme::RoqmeBoolWriter boolWr;
	Roqme::RoqmeIntWriter intWr;
	Roqme::RoqmeUIntWriter uintWr;
	Roqme::RoqmeDoubleWriter doubleWr;
	Roqme::RoqmeObservationWriter observationWr;

	void sendInt(const ContextInfo& context);
	void sendUInt(const ContextInfo& context);	
	void sendDouble(const ContextInfo& context);	
	void sendEvent(const ContextInfo& context);	
	void sendEnum(const ContextInfo& context);
	void sendBool(const ContextInfo& context);	
	void sendObservation(const ContextInfo& context);	

	void sendBoolMiron(const ContextInfo& context);
	void sendDoubleMiron(const ContextInfo& context);

	void wait(const long& timestamp);
	
};

}
