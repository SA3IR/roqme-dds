#include "RoqmePlayer.h"

namespace Roqme {

void RoqmePlayer::load(const std::string& fileName) {
	long elapsed;
	std::string gb1, gb2, gb3, gb4, type, name, value;
	std::ifstream ifile;

	ifile.open(fileName);	
	if (ifile.good()) {
		ContextInfo contextInfo;
		context_v.clear();
		while(ifile >> gb1 >> gb2 >> gb3 >> elapsed >> gb4 >> type >> name >> value) {	
			contextInfo.timestamp = elapsed;
			contextInfo.name = name;
			contextInfo.type = type;
			contextInfo.value = value;
			context_v.push_back(contextInfo);
		}
 		ifile.close();	
		int cont = context_v.size()-1;
		for(auto iter = context_v.rbegin(); iter!=context_v.rend(); ++iter ){
			if (cont == 0) 
				context_v[0].timestamp = 0;	
			else 
				context_v[cont].timestamp-=context_v[cont-1].timestamp;
			cont--;
		}
	}
	else 
		throw RoqmeDDSException("Error opening file.");
	
}

void RoqmePlayer::play() {
	unsigned int i = 1;
	unsigned int length = context_v.size();
	for (auto iter: context_v) {
#ifdef TESTING
		std::cout << "[" << i << "/" << length << "] Esperando " << 5000 << " ms " << std::endl;
#else
		std::cout << "[" << i << "/" << length << "] Esperando " << iter.timestamp / 1000000 << " ms " << std::endl;
#endif
		if ( iter.type == "INT")
			sendInt(iter);
		else if (iter.type == "UINT")
			sendUInt(iter);
		else if (iter.type == "DOUBLE")
			sendDouble(iter);
		else if (iter.type == "BOOLEAN")
			sendBoolMiron(iter);
		else if (iter.type == "EVENT")
			sendEvent(iter);
		else if (iter.type == "ENUM")
			sendEnum(iter);
		else if (iter.type == "OBSERVATION")
			sendObservation(iter);
		if(iter.type != "OBSERVATION")
			std::cout << "[" << i << "/" << length << "] Contexto: (" << iter.type << ", " << iter.name << ", " << iter.value << ") enviado" << std::endl << std::endl;
		else
			std::cout << "[" << i << "/" << length << "] Contexto: (" << iter.type << ", " << iter.name << ") enviado" << std::endl << std::endl;
		i++;
	}	
}

void RoqmePlayer::wait(const long& timestamp) {
#ifdef TESTING
	std::this_thread::sleep_for (std::chrono::seconds(5));
#else
	std::this_thread::sleep_for (std::chrono::nanoseconds(timestamp));
#endif
}

void RoqmePlayer::sendInt(const ContextInfo& context) {	
	RoqmeDDSTopics::RoqmeIntContext intContext;
	intContext.name(context.name);
	intContext.value().push_back(stoi(context.value));
	wait(context.timestamp);
	intWr.write(intContext);
}

void RoqmePlayer::sendUInt(const ContextInfo& context) {
	RoqmeDDSTopics::RoqmeUIntContext uintContext;
	uintContext.name(context.name);
	uintContext.value().push_back(stoul(context.value));
	wait(context.timestamp);
	uintWr.write(uintContext);
}

void RoqmePlayer::sendBool(const ContextInfo& context) {
	RoqmeDDSTopics::RoqmeBoolContext boolContext;
	boolContext.name(context.name);
	bool value = false;
	if(context.value == "true")
		value = true;
	boolContext.value().push_back(value);
	wait(context.timestamp);
	boolWr.write(boolContext);
}

void RoqmePlayer::sendDouble(const ContextInfo& context) {
	RoqmeDDSTopics::RoqmeDoubleContext doubleContext;
	doubleContext.name(context.name);
	doubleContext.value().push_back(stod(context.value));
	wait(context.timestamp);
	doubleWr.write(doubleContext);
}

void RoqmePlayer::sendEvent(const ContextInfo& context) {
	RoqmeDDSTopics::RoqmeEventContext eventContext;
	eventContext.name(context.name);
	eventContext.value().push_back(context.value);
	wait(context.timestamp);
	eventWr.write(eventContext);
}

void RoqmePlayer::sendEnum(const ContextInfo& context) {
	RoqmeDDSTopics::RoqmeEnumContext enumContext;
	enumContext.name(context.name);
	enumContext.value().push_back(context.value);
	wait(context.timestamp);
	enumWr.write(enumContext);
}

void RoqmePlayer::sendObservation(const ContextInfo& context) {
	RoqmeDDSTopics::RoqmeObservation obs;
	obs.name(context.name);
	wait(context.timestamp);
	observationWr.write(obs);
}



void RoqmePlayer::loadMiron(const std::string& fileName) {
	long elapsed;
	std::string gb1, gb2, name, value;
	std::ifstream ifile;

	ifile.open(fileName);	
	if (ifile.good()) {
		ContextInfo contextInfo;
		context_v.clear();
		while(ifile >> elapsed >> gb1 >> name >> gb2 >> value) {
			std::cout << elapsed << " " << name << " " << value << std::endl;	
			contextInfo.timestamp = elapsed;
			contextInfo.name = name;
			contextInfo.value = value;
			context_v.push_back(contextInfo);
		}
 		ifile.close();	
		int cont = context_v.size()-1;
		for(auto iter = context_v.rbegin(); iter!=context_v.rend(); ++iter ){
			if (cont == 0) 
				context_v[0].timestamp = 0;	
			else 
				context_v[cont].timestamp-=context_v[cont-1].timestamp;
			cont--;
		}
	}
	else 
		throw RoqmeDDSException("Error opening file.");
	
}

void RoqmePlayer::playMiron() {
	unsigned int i = 1;
	unsigned int length = context_v.size();
	for (auto iter: context_v) {
#ifdef TESTING
		std::cout << "[" << i << "/" << length << "] Esperando " << 5000 << " ms " << std::endl;
#else
		std::cout << "[" << i << "/" << length << "] Esperando " << iter.timestamp << " ms " << std::endl;
#endif
		if ( iter.name == "BatteryLevel")
			sendDoubleMiron(iter);
		else if (iter.name == "ObjectBump"){}
			//			
		else
			sendBoolMiron(iter);
		std::cout << "[" << i << "/" << length << "] Contexto: (" << iter.type << ", " << iter.name << ", " << iter.value << ") enviado" << std::endl << std::endl;
		i++;
	}	

}

void RoqmePlayer::sendBoolMiron(const ContextInfo& context) {
	RoqmeDDSTopics::RoqmeBoolContext boolContext;
	boolContext.name(context.name);
	bool value = false;
	if(context.value == "1")
		value = true;
	boolContext.value().push_back(value);
	wait(context.timestamp * 1000000);
	boolWr.write(boolContext);
}

void RoqmePlayer::sendDoubleMiron(const ContextInfo& context) {
	double val = stoul(context.value);
	if(val>=100)
	{
		RoqmeDDSTopics::RoqmeDoubleContext doubleContext;
		doubleContext.name(context.name);
		doubleContext.value().push_back(stoul(context.value)%100);
		wait(context.timestamp * 1000000);
		doubleWr.write(doubleContext);
	}
}


}
