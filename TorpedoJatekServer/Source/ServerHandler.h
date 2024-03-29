#pragma once

#include "../../CommonSource/ConnectionHandler.h"
#include "../../CommonSource/CommonGlobals.hpp"

//Szerverhez köthető kapcsolat függvények
class ServerHandler : public ConnectionHandler {
public:
	static void Init_SDL();
	static TCPsocket TCP_Accept(TCPsocket& server_socket);
	static MessageType ReceiveMessageType(TCPsocket& socket);

private:

	static void ReportErrorAndExit(char function_name[] = "Undefined", int exit_code = 99);
};