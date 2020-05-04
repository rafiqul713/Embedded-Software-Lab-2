#pragma once

#include<string.h>
#include<stdlib.h>

struct Frame{
    char preamble[9];
    char crc[33];
    char payloadSize[9];
    char payload[9];
};

struct Frame senderFrame;
char recvCRC[33], recvPayloadSize[9],recvPayload[9];
char recvPrem[9];
char transferBuffer[57];
char receiverBuffer[57];
char predefined_preamble[9];
char predefined_crc[33];

