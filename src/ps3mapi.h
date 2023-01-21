#ifndef PS3LIB_PS3MAPI_H
#define PS3LIB_PS3MAPI_H

#include <cstdint>
#include <regex>
#include "ps3lib.h"
#include "types.h"

#define PS3MAPI_OK 0
#define PS3MAPI_ERROR -1

namespace ps3mapi {
    inline internet_wrapper inet;

    static int send_ps3mapi_command ( const char* path ) {
        std::regex space( "[[:space:]]" );
        std::string s_input = std::regex_replace ( path, space, "%20" );

        int conn_s = -1;
        conn_s = inet.connect_client ( inet.get_ip_address ( ), inet.get_port ( ) );

        struct timeval tv;
        setsockopt ( conn_s, SOL_SOCKET, SO_SNDTIMEO, ( char* ) &tv, sizeof ( tv ) );
        setsockopt ( conn_s, SOL_SOCKET, SO_RCVTIMEO, ( char* ) &tv, sizeof ( tv ) );

        if ( conn_s >= INTERNET_ERROR ) {
            char wm_cmd [ 1048 ];
            int cmd_len = sprintf ( wm_cmd, "GET %s HTTP/1.0\r\n", s_input.data ( ) );
            
            inet.send_data ( wm_cmd );
            
            return PS3MAPI_OK;
        }
        
        return PS3MAPI_ERROR;
    }

    int PS3MAPIConnect ( const char* ip );
    int PS3MAPIDisconnect ( );
    int PS3MAPIGetConnectionStatus ( int* status );
    int PS3MAPISetConsoleIds ( e_console_id_type type, const console_id* id );
    int PS3MAPISetBootConsoleIds ( e_console_id_type type, int on, const console_id* id );
    int PS3MAPIGetMemory ( u32 pid, u64 address, u32 size, void* data );
    int PS3MAPISetMemory ( u32 pid, u64 address, u32 size, const void* data );
    int PS3MAPIGetProcessList ( u32* npid, u32* pids );
    int PS3MAPIGetProcessName ( u32 pid, process_name* name );
    int PS3MAPIGetTemperature ( int* cell, int* rsx );
    int PS3MAPIShutdown ( int mode );
    int PS3MAPIRingBuzzer ( int type );
    int PS3MAPISetConsoleLed ( int color, int status );
    int PS3MAPIGetFirmwareInfo ( u32* firmware, int* cType );
    int PS3MAPIVshNotify ( int icon, const char* msg );
    void PS3MAPIGetConsoleInfo ( int index, char* name, char* ip );
}

#endif // !PS3LIB_PS3MAPI_H