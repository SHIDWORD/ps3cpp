#include "internet.h"
#include "exception.h"

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>

#pragma comment ( lib, "mswsock.lib" )
#pragma comment ( lib, "advapi32.lib" )
#pragma comment ( lib, "ws2_32.lib" )

SOCKET connect_socket = ~0;

int internet_wrapper::connect_client ( const char* ip, int port ) {
    WSADATA wsa_data;
    int ret_result;

    this->ip = ip;
    this->port = port;

    struct addrinfo *result = NULL, *ptr = NULL, hints;

    if ( ret_result = WSAStartup ( MAKEWORD( 2 , 2 ), &wsa_data ) != 0 ) {
        printf ( "WSAStartup failed with error: %d\n", ret_result );
        return INTERNET_ERROR;
    }

    memset ( &hints, 0, sizeof ( hints ) );
    
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if ( ret_result = getaddrinfo ( ip, std::to_string ( port ).c_str ( ), &hints, &result ) != 0 ) {
        printf ( "getaddrinfo failed with error: %d \n", ret_result );
        WSACleanup ( );
        return INTERNET_ERROR;
    }

   // printf ( "Connecting to %s:%d\n", ip, port );

    EX_HANDLER_BEGIN

    for ( ptr = result; ptr != 0; ptr = ptr->ai_next ) {
        connect_socket = socket ( ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol );

        if ( connect_socket == INVALID_SOCKET ) {
            throw std::exception ( "Socket failed with error: %d", WSAGetLastError ( ) );
            WSACleanup ( );
            this->connected = false;
            return INTERNET_ERROR;
        }

        ret_result = connect ( connect_socket, ptr->ai_addr, ( int ) ptr->ai_addrlen );

        if ( ret_result == SOCKET_ERROR ) {
            closesocket ( connect_socket );
            connect_socket = INVALID_SOCKET;
            this->connected = false;
            continue;
        }

        break;
    }

    freeaddrinfo ( result );

    EX_HANDLER_END

    this->connected = true;

    return INTERNET_OK;
}

int internet_wrapper::send_data ( const char* data ) {
    send ( connect_socket , data , strlen ( data ) , 0 );
    return INTERNET_OK;
}

void internet_wrapper::disconnect_client ( ) {
    this->ip = 0;
    this->port = 0;

    WSACleanup ( );
}