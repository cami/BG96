#include "NectisCellularConfig.h"
#include "NectisCellularClient.h"

#define RECEIVE_MAX_LENGTH    (1500)

#define CONNECT_SUCCESS                 (1)
#define CONNECT_TIMED_OUT               (-1)
#define CONNECT_INVALID_SERVER          (-2)
#define CONNECT_TRUNCATED               (-3)
#define CONNECT_INVALID_RESPONSE        (-4)

NectisCellularClient::NectisCellularClient(NectisCellularBG96* BG96)
{
	_BG96 = BG96;
	_ConnectId = -1;
	_ReceiveBuffer = new byte[RECEIVE_MAX_LENGTH];
}

NectisCellularClient::~NectisCellularClient()
{
	delete [] _ReceiveBuffer;
}

int NectisCellularClient::connect(IPAddress ip, uint16_t port)
{
	if (connected()) return CONNECT_INVALID_RESPONSE;	// Already connected.

	String ipStr = String(ip[0]);
	ipStr += ".";
	ipStr += String(ip[1]);
	ipStr += ".";
	ipStr += String(ip[2]);
	ipStr += ".";
	ipStr += String(ip[3]);
	int connectId = _BG96->SocketOpen(ipStr.c_str(), port, NectisCellularBG96::SOCKET_TCP);
	if (connectId < 0) return CONNECT_INVALID_SERVER;
	_ConnectId = connectId;

	return CONNECT_SUCCESS;
}

int NectisCellularClient::connect(const char* host, uint16_t port)
{
	if (connected()) return CONNECT_INVALID_RESPONSE;	// Already connected.

	int connectId = _BG96->SocketOpen(host, port, NectisCellularBG96::SOCKET_TCP);
	if (connectId < 0) return CONNECT_INVALID_SERVER;
	_ConnectId = connectId;

	return CONNECT_SUCCESS;
}

size_t NectisCellularClient::write(uint8_t data)
{
	if (!connected()) return 0;

	if (!_BG96->SocketSend(_ConnectId, &data, 1)) return 0;

	return 1;
}

size_t NectisCellularClient::write(const uint8_t* buf, size_t size)
{
	if (!connected()) return 0;

	if (!_BG96->SocketSend(_ConnectId, buf, size)) return 0;

	return size;
}

int NectisCellularClient::available()
{
	if (!connected()) return 0;

	int receiveSize = _BG96->SocketReceive(_ConnectId, _ReceiveBuffer, RECEIVE_MAX_LENGTH);
	for (int i = 0; i < receiveSize; i++) _ReceiveQueue.push(_ReceiveBuffer[i]);

	return _ReceiveQueue.size();
}

int NectisCellularClient::read()
{
	if (!connected()) return -1;

	int actualSize = available();
	if (actualSize <= 0) return -1;	// None is available.

	byte data = _ReceiveQueue.front();
	_ReceiveQueue.pop();

	return data;
}

int NectisCellularClient::read(uint8_t* buf, size_t size)
{
	if (!connected()) return 0;

	int actualSize = available();
	if (actualSize <= 0) return 0;	// None is available.

	int popSize = actualSize <= (int)size ? actualSize : size;
	for (int i = 0; i < popSize; i++) {
		buf[i] = _ReceiveQueue.front();
		_ReceiveQueue.pop();
	}

	return popSize;
}

int NectisCellularClient::peek()
{
	if (!connected()) return 0;

	int actualSize = available();
	if (actualSize <= 0) return -1;	// None is available.

	return _ReceiveQueue.front();
}

void NectisCellularClient::flush()
{
	// Nothing to do.
}

void NectisCellularClient::stop()
{
	if (!connected()) return;

	_BG96->SocketClose(_ConnectId);
	_ConnectId = -1;
	while (!_ReceiveQueue.empty()) _ReceiveQueue.pop();
}

uint8_t NectisCellularClient::connected()
{
	return _ConnectId >= 0 ? true : false;
}

NectisCellularClient::operator bool()
{
	return _ConnectId >= 0 ? true : false;
}
