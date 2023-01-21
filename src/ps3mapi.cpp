#include "ps3mapi.h"

int ps3mapi::PS3MAPIConnect ( const char* ip ) {
    inet.connect_client ( ip, 80 );

    while ( !inet.is_connected ( ) ) {
        return PS3MAPI_ERROR;
    }

    return PS3MAPI_OK;
}

int ps3mapi::PS3MAPIDisconnect ( ) {
    inet.disconnect_client ( );
    return PS3MAPI_OK;
}

int ps3mapi::PS3MAPIGetConnectionStatus ( int* status ) {
    return PS3MAPI_OK;
}

int ps3mapi::PS3MAPISetConsoleIds ( e_console_id_type type, const console_id* id ) {
    return PS3MAPI_OK;
}

int ps3mapi::PS3MAPISetBootConsoleIds ( e_console_id_type type, int on, const console_id* id ) {
    return PS3MAPI_OK;
}

int ps3mapi::PS3MAPIGetMemory ( u32 pid, u64 address, u32 size, void* data ) {
    return PS3MAPI_OK;
}

int ps3mapi::PS3MAPISetMemory ( u32 pid, u64 address, u32 size, const void* data ) {
    return PS3MAPI_OK;
}

int ps3mapi::PS3MAPIGetProcessList ( u32* npid, u32* pids ) {
    return PS3MAPI_OK;
}

int ps3mapi::PS3MAPIGetProcessName ( u32 pid, process_name* name ) {
    return PS3MAPI_OK;
}

int ps3mapi::PS3MAPIGetTemperature ( int* cell, int* rsx ) {
    return PS3MAPI_OK;
}

int ps3mapi::PS3MAPIShutdown ( int mode ) {
    return PS3MAPI_OK;
}

int ps3mapi::PS3MAPIRingBuzzer ( int type ) {
    char buffer [ 512 ] = { 0 };
    sprintf ( buffer, "/buzzer.ps3mapi?snd=%d", type );
    return send_ps3mapi_command ( buffer );
}

int ps3mapi::PS3MAPISetConsoleLed ( int color, int status ) {
    char buffer [ 512 ] = { 0 };
    sprintf ( buffer, "/led.ps3mapi?color=%d&mode=%d" , color, status );
    return send_ps3mapi_command ( buffer );
}

int ps3mapi::PS3MAPIGetFirmwareInfo ( u32* firmware, int* cType ) {
    return PS3MAPI_OK;
}

int ps3mapi::PS3MAPIVshNotify ( int icon, const char* msg ) {
    char buffer [ 512 ] = { 0 };
    sprintf ( buffer, "/notify.ps3mapi?msg=%s&icon=%d&snd=", msg, icon );
    return send_ps3mapi_command ( buffer );
}

void ps3mapi::PS3MAPIGetConsoleInfo ( int index, char* name, char* ip ) {
}