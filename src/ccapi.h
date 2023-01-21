#ifndef PS3LIB_CCAPI_H
#define PS3LIB_CCAPI_H

#include <cstdint>
#include "ps3lib.h"
#include "types.h"

namespace ccapi {
    inline int init_status = PS3LIB_ERROR;

    // export prototypes.
    using CCAPIConnectFn = int ( __cdecl * ) ( const char* ip );
    using CCAPIDisconnectFn = int ( __cdecl * ) ( );
    using CCAPIGetConnectionStatusFn = int ( __cdecl * ) ( int* status );
    using CCAPISetConsoleIdsFn = int ( __cdecl * ) ( e_console_id_type type, const console_id* id );
    using CCAPISetBootConsoleIdsFn = int ( __cdecl * ) ( e_console_id_type type, int on, const console_id* id );
    using CCAPIGetMemoryFn = int ( __cdecl * ) ( u32 pid, u64 address, u32 size, void* data );
    using CCAPISetMemoryFn = int ( __cdecl * ) ( u32 pid, u64 address, u32 size, const void* data );
    using CCAPIGetProcessListFn = int ( __cdecl * ) ( u32* npid, u32* pids );
    using CCAPIGetProcessNameFn = int ( __cdecl * ) ( u32 pid, process_name* name );
    using CCAPIGetTemperatureFn = int ( __cdecl * ) ( int* cell, int* rsx );
    using CCAPIShutdownFn = int ( __cdecl * ) ( int mode );
    using CCAPIRingBuzzerFn = int ( __cdecl * ) ( int type );
    using CCAPISetConsoleLedFn = int ( __cdecl * ) ( int color, int status );
    using CCAPIGetFirmwareInfoFn = int ( __cdecl * ) ( u32* firmware, u32* ccapi, int* cType );
    using CCAPIVshNotifyFn = int ( __cdecl * ) ( int icon, const char* msg );
    using CCAPIGetNumberOfConsolesFn = int ( __cdecl * ) ( );
    using CCAPIGetConsoleInfoFn = void ( __cdecl * ) ( int index, char* name, char* ip );
    using CCAPIGetDllVersionFn = int ( __cdecl * ) ( );

    namespace ccapi_exports {
        inline CCAPIConnectFn CCAPIConnect = nullptr;
        inline CCAPIDisconnectFn CCAPIDisconnect = nullptr;
        inline CCAPIGetConnectionStatusFn CCAPIGetConnectionStatus = nullptr;
        inline CCAPISetConsoleIdsFn CCAPISetConsoleIds = nullptr;
        inline CCAPISetBootConsoleIdsFn CCAPISetBootConsoleIds = nullptr;
        inline CCAPIGetMemoryFn CCAPIGetMemory = nullptr;
        inline CCAPISetMemoryFn CCAPISetMemory = nullptr;
        inline CCAPIGetProcessListFn CCAPIGetProcessList = nullptr;
        inline CCAPIGetProcessNameFn CCAPIGetProcessName = nullptr;
        inline CCAPIGetTemperatureFn CCAPIGetTemperature = nullptr;
        inline CCAPIShutdownFn CCAPIShutdown = nullptr;
        inline CCAPIRingBuzzerFn CCAPIRingBuzzer = nullptr;
        inline CCAPISetConsoleLedFn CCAPISetConsoleLed = nullptr;
        inline CCAPIGetFirmwareInfoFn CCAPIGetFirmwareInfo = nullptr;
        inline CCAPIVshNotifyFn CCAPIVshNotify = nullptr;
        inline CCAPIGetNumberOfConsolesFn CCAPIGetNumberOfConsoles = nullptr;
        inline CCAPIGetConsoleInfoFn CCAPIGetConsoleInfo = nullptr;
        inline CCAPIGetDllVersionFn CCAPIGetDllVersion = nullptr;

        // load exports.
        __forceinline int load ( HMODULE mod ) {
            CCAPIConnect = reinterpret_cast< CCAPIConnectFn > ( GetProcAddress ( mod, "CCAPIConnectConsole" ) );
            CCAPIDisconnect = reinterpret_cast< CCAPIDisconnectFn > ( GetProcAddress ( mod, "CCAPIDisconnectConsole" ) );
            CCAPIGetConnectionStatus = reinterpret_cast< CCAPIGetConnectionStatusFn > ( GetProcAddress ( mod, "CCAPIGetConnectionStatus" ) );
            CCAPISetConsoleIds = reinterpret_cast< CCAPISetConsoleIdsFn > ( GetProcAddress ( mod, "CCAPISetConsoleIds" ) );
            CCAPISetBootConsoleIds = reinterpret_cast< CCAPISetBootConsoleIdsFn > ( GetProcAddress ( mod, "CCAPISetBootConsoleIds" ) );
            CCAPIGetMemory = reinterpret_cast< CCAPIGetMemoryFn > ( GetProcAddress ( mod, "CCAPIGetMemory" ) );
            CCAPISetMemory = reinterpret_cast< CCAPISetMemoryFn > ( GetProcAddress ( mod, "CCAPISetMemory" ) );
            CCAPIGetProcessList = reinterpret_cast< CCAPIGetProcessListFn > ( GetProcAddress ( mod, "CCAPIGetProcessList" ) );
            CCAPIGetProcessName = reinterpret_cast< CCAPIGetProcessNameFn > ( GetProcAddress ( mod, "CCAPIGetProcessName" ) );
            CCAPIGetTemperature = reinterpret_cast< CCAPIGetTemperatureFn > ( GetProcAddress ( mod, "CCAPIGetTemperature" ) );
            CCAPIShutdown = reinterpret_cast< CCAPIShutdownFn > ( GetProcAddress ( mod, "CCAPIShutdown" ) );
            CCAPIRingBuzzer = reinterpret_cast< CCAPIRingBuzzerFn > ( GetProcAddress ( mod, "CCAPIRingBuzzer" ) );
            CCAPISetConsoleLed = reinterpret_cast< CCAPISetConsoleLedFn > ( GetProcAddress ( mod, "CCAPISetConsoleLed" ) );
            CCAPIGetFirmwareInfo = reinterpret_cast< CCAPIGetFirmwareInfoFn > ( GetProcAddress ( mod, "CCAPIGetFirmwareInfo" ) );
            CCAPIVshNotify = reinterpret_cast< CCAPIVshNotifyFn > ( GetProcAddress ( mod, "CCAPIVshNotify" ) );
            CCAPIGetNumberOfConsoles = reinterpret_cast< CCAPIGetNumberOfConsolesFn > ( GetProcAddress ( mod, "CCAPIGetNumberOfConsoles" ) );
            CCAPIGetConsoleInfo = reinterpret_cast< CCAPIGetConsoleInfoFn > ( GetProcAddress ( mod, "CCAPIGetConsoleInfo" ) );
            CCAPIGetDllVersion = reinterpret_cast< CCAPIGetDllVersionFn > ( GetProcAddress ( mod, "CCAPIGetDllVersion" ) );

            return PS3LIB_OK;
        }
    }
}

#endif // !PS3LIB_CCAPI_H