#pragma once

#include "SerialAPI.h"
#include "Stopwatch.h"
#include <string>

class NectisCellularBG96;

class AtSerial
{
private:
	SerialAPI* _Serial;
	NectisCellularBG96* _BG96;
	unsigned long _EchoOn;

	bool ReadResponseInternal(const char* pattern, unsigned long timeout, std::string* response, int responseMaxLength);

public:
	AtSerial(SerialAPI* serial, NectisCellularBG96* bg96);

	void SetEcho(bool on);

	bool WaitForAvailable(Stopwatch* sw, unsigned long timeout) const;

	void WriteBinary(const byte* data, int dataSize);
	bool ReadBinary(byte* data, int dataSize, unsigned long timeout);

	void WriteCommand(const char* command);
	bool ReadResponse(const char* pattern, unsigned long timeout, std::string* capture);
	bool WriteCommandAndReadResponse(const char* command, const char* pattern, unsigned long timeout, std::string* capture);

	bool ReadResponseQHTTPREAD(char* data, int dataSize, unsigned long timeout);

};