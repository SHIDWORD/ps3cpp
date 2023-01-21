#include "ps3lib.h"

int ps3lib::initialize ( ) {
    using namespace ccapi;

    EX_HANDLER_BEGIN

    HMODULE ccapi_mod = LoadLibraryA ( "CCAPI.dll" );

    // initialize our dlls needed for our library
    if ( ccapi_mod == NULL ) {
        throw std::runtime_error ( "Failed to load runtime library \"CCAPI.dll\"" );
        return PS3LIB_ERROR;
    }

    auto status = PS3LIB_ERROR;

    // load our exports.
    if ( status = ccapi_exports::load ( ccapi_mod ) != PS3LIB_OK ) {
        throw std::runtime_error ( "Failed to load exports." );
        return PS3LIB_ERROR;
    }

    ccapi::init_status = status;

    EX_HANDLER_END

    return PS3LIB_OK;
}

int ps3lib::get_temperature ( int* cpu, int* rsx ) {
    using namespace ccapi;

    EX_HANDLER_BEGIN

    if ( connection_type == e_connection_type::type_ccapi ) {
        const auto status = ccapi_exports::CCAPIGetTemperature ( cpu, rsx );

        if ( status != PS3LIB_OK ) {
            throw std::runtime_error ( "Failed to get temperature." );
            return PS3LIB_ERROR;
        }
    }

    else if ( connection_type == e_connection_type::type_ps3mapi ) {
        const auto status = ps3mapi::PS3MAPIGetTemperature ( cpu, rsx );

        if ( status != PS3LIB_OK ) {
            throw std::runtime_error ( "Failed to get temperature." );
            return PS3LIB_ERROR;
        }
    }

    EX_HANDLER_END

    return PS3LIB_OK;
}

const char* ps3lib::get_temperature ( ) {
    int cpu = 0, rsx = 0;
    ps3lib::get_temperature ( &cpu, &rsx );

    static char buffer [ 256 ] = { 0 };
    sprintf ( buffer, "CPU: %d | RSX: %d", cpu, rsx );

    return buffer;
}

int ps3lib::set_console_ids ( const e_console_id_type& type, const char* id ) {
    using namespace ccapi;

    EX_HANDLER_BEGIN

    console_id bytes = { 0 };
    size_t len = strlen ( id ); 
    std::memcpy ( bytes, id, len );

    if ( connection_type == e_connection_type::type_ccapi ) {
        const auto status = ccapi_exports::CCAPISetConsoleIds ( type, &bytes );

        if ( status != PS3LIB_OK ) {
            throw std::runtime_error ( "Failed to set console ids." );
            return PS3LIB_ERROR;
        }
    }

    else if ( connection_type == e_connection_type::type_ps3mapi ) {
        const auto status = ps3mapi::PS3MAPISetConsoleIds ( type, &bytes );

        if ( status != PS3LIB_OK ) {
            throw std::runtime_error ( "Failed to set console ids." );
            return PS3LIB_ERROR;
        }
    }

    EX_HANDLER_END

    return PS3LIB_OK;
}

int ps3lib::set_boot_console_ids ( const e_console_id_type& type, bool enabled, const char* id ) {
    using namespace ccapi;

    EX_HANDLER_BEGIN

    console_id bytes = { 0 };
    size_t len = strlen ( id );
    std::memcpy ( bytes, id, len );

    if ( connection_type == e_connection_type::type_ccapi ) {
        const auto status = ccapi_exports::CCAPISetBootConsoleIds ( type, enabled, &bytes );

        if ( status != PS3LIB_OK ) {
            throw std::runtime_error ( "Failed to set boot console ids." );
            return PS3LIB_ERROR;
        }
    }

    else if ( connection_type == e_connection_type::type_ps3mapi ) {
        const auto status = ps3mapi::PS3MAPISetBootConsoleIds ( type, enabled, &bytes );

        if ( status != PS3LIB_OK ) {
            throw std::runtime_error ( "Failed to set boot console ids." );
            return PS3LIB_ERROR;
        }
    }

    EX_HANDLER_END

    return PS3LIB_OK;
}

int ps3lib::ring_buzzer ( const ps3lib::e_ring_buzzer_action& action ) {
    using namespace ccapi;

    EX_HANDLER_BEGIN

    if ( connection_type == e_connection_type::type_ccapi ) {
        const auto status = ccapi_exports::CCAPIRingBuzzer ( static_cast < int > ( action ) );

        if ( status != PS3LIB_OK ) {
            throw std::runtime_error ( "Failed to ring buzzer." );
            return PS3LIB_ERROR;
        }
    }

    else if ( connection_type == e_connection_type::type_ps3mapi ) {
        const auto status = ps3mapi::PS3MAPIRingBuzzer ( static_cast < int > ( action ) );

        if ( status != PS3LIB_OK ) {
            throw std::runtime_error ( "Failed to ring buzzer." );
            return PS3LIB_ERROR;
        }
    }

    EX_HANDLER_END

    return PS3LIB_OK;
}

int ps3lib::vsh_notify ( const ps3lib::e_notify_icon& icon , const char* msg ) {
    using namespace ccapi;

    EX_HANDLER_BEGIN

    if ( connection_type == e_connection_type::type_ccapi ) {
        const auto status = ccapi_exports::CCAPIVshNotify ( static_cast < uint8_t > ( icon ), msg );

        if ( status != PS3LIB_OK ) {
            throw std::runtime_error ( "Failed to send notification." );
            return PS3LIB_ERROR;
        }
    }

    else if ( connection_type == e_connection_type::type_ps3mapi ) {
        const auto status = ps3mapi::PS3MAPIVshNotify ( static_cast < uint8_t > ( icon ), msg );

        if ( status != PS3LIB_OK ) {
            throw std::runtime_error ( "Failed to send notification." );
            return PS3LIB_ERROR;
        }
    }

    EX_HANDLER_END

    return PS3LIB_OK;
}

int ps3lib::get_firmware_info_ccapi ( uint32_t* firmware , uint32_t* ccapi , int* type ) {
    using namespace ccapi;

    EX_HANDLER_BEGIN

    const auto status = ccapi_exports::CCAPIGetFirmwareInfo ( firmware, ccapi, type );

    if ( status != PS3LIB_OK ) {
        throw std::runtime_error ( "Failed to get firmware info." );
        return PS3LIB_ERROR;
    }   

    EX_HANDLER_END

    return PS3LIB_OK;
}

int ps3lib::get_firmware_info_ps3mapi ( uint32_t* firmware , int* type ) {
    using namespace ccapi;

    EX_HANDLER_BEGIN

    const auto status = ps3mapi::PS3MAPIGetFirmwareInfo ( firmware, type );

    if ( status != PS3LIB_OK ) {
        throw std::runtime_error ( "Failed to get firmware info." );
        return PS3LIB_ERROR;
    }   

    EX_HANDLER_END

    return PS3LIB_OK;
}

const char* ps3lib::get_firmware_info ( ) {
    auto data = ps3lib::get_firmware_info_data ( );

    static char buffer [ 256 ] = { 0 };
    sprintf ( buffer, "Firmware: %.2f | CCAPI: %.2f | Type: %s", data.firmware_version, data.ccapi_version, data.console_type );

    return buffer;
}

ps3lib::firmware_info_t ps3lib::get_firmware_info_data ( ) {
    ps3lib::firmware_info_t info;
    uint32_t firmware = 0, ccapi = 0;
    int type = 0;

    if ( connection_type == e_connection_type::type_ccapi ) {
        if ( ps3lib::get_firmware_info_ccapi ( &firmware, &ccapi, &type ) != PS3LIB_OK )
            return { };

        info.firmware_version = ps3lib::get_firmware_version ( firmware );
        info.ccapi_version = ps3lib::get_ccapi_version ( ccapi );
        info.console_type = ps3lib::get_console_type ( static_cast < e_console_type > ( type ) );
    }

    else if ( connection_type == e_connection_type::type_ps3mapi ) {
        if ( ps3lib::get_firmware_info_ps3mapi ( &firmware, &type ) != PS3LIB_OK )
            return { };

        info.ccapi_version = 0.0f;
        info.firmware_version = ps3lib::get_firmware_version ( firmware );
        info.console_type = ps3lib::get_console_type ( static_cast < e_console_type > ( type ) );
    }

    return info;
} 

int ps3lib::set_console_led ( const ps3lib::e_led_action& action , const ps3lib::e_led_color& color ) {
    using namespace ccapi;

    EX_HANDLER_BEGIN

    if ( connection_type == e_connection_type::type_ccapi ) {
        const auto status = ccapi_exports::CCAPISetConsoleLed ( static_cast < int > ( color ) , static_cast < int > ( action ) );

        if ( status != PS3LIB_OK ) {
            throw std::runtime_error ( "Failed to set console led." );
            return PS3LIB_ERROR;
        }
    }

    else if ( connection_type == e_connection_type::type_ps3mapi ) {
        const auto status = ps3mapi::PS3MAPISetConsoleLed ( static_cast < int > ( color ) , static_cast < int > ( action ) );

        if ( status != PS3LIB_OK ) {
            throw std::runtime_error ( "Failed to set console led." );
            return PS3LIB_ERROR;
        }
    }

    EX_HANDLER_END

    return PS3LIB_OK;
}

int ps3lib::connect ( const char* ip , const ps3lib::e_connection_type type , const char* name ) {
    connection_type = type;
    connection_name = name;

    using namespace ccapi;

    EX_HANDLER_BEGIN

    if ( connection_type == e_connection_type::type_ccapi ) {
        const auto status = ccapi_exports::CCAPIConnect ( ip );

        if ( status != PS3LIB_OK ) {
            // throw error to client.
            printf ( "\n[ERROR] Cannot connect to %s.\n1) Verify that your ps3 ip address is correct\n2) Check that your antivirus/firewall doesn't block the communications\n", name );

            return PS3LIB_ERROR;
        }
    }

    else if ( connection_type == e_connection_type::type_ps3mapi ) {
        const auto status = ps3mapi::PS3MAPIConnect ( ip );

        if ( status != PS3LIB_OK ) {
            // throw error to client.
            printf ( "\n[ERROR] Cannot connect to %s.\n1) Verify that your ps3 ip address is correct\n2) Check that your antivirus/firewall doesn't block the communications\n", name );

            return PS3LIB_ERROR;
        }
    }

    printf ( "[PS3LIB] Connected to %s using ", connection_name ); {
        if ( connection_type == e_connection_type::type_ccapi )
            printf ( "CCAPI!\n" );

        else if ( connection_type == e_connection_type::type_ps3mapi )
            printf ( "PS3MAPI!\n" );
    }

    // notify our console.
    static auto current_host_ip = ps3lib::get_host_address ( );
    char buffer [ 256 ];
    sprintf_s ( buffer, "[PS3LIB] client %s connected!", current_host_ip );

    //ps3lib::send_console_action ( ps3lib::e_shutdown_mode::action_hard_reboot );
    ps3lib::vsh_notify ( e_notify_icon::notify_info, buffer );
    ps3lib::ring_buzzer ( e_ring_buzzer_action::ring_buzzer_single );

    EX_HANDLER_END

    return PS3LIB_OK;
}

int ps3lib::disconnect ( ) {
    using namespace ccapi;

    EX_HANDLER_BEGIN

    static auto current_host_ip = ps3lib::get_host_address ( );
    char buffer [ 256 ];
    sprintf_s ( buffer, "[PS3LIB] client %s dropped!", current_host_ip );
    printf ( "[PS3LIB] Disconnected from %s.\n", connection_name );

    // notify our console.
    ps3lib::vsh_notify ( e_notify_icon::notify_info, buffer );

    if ( connection_type == e_connection_type::type_ccapi ) {
        const auto status = ccapi_exports::CCAPIDisconnect ( );

        if ( status != PS3LIB_OK ) {
            throw std::runtime_error ( "Failed to disconnect." );
            return PS3LIB_ERROR;
        }
    }

    else if ( connection_type == e_connection_type::type_ps3mapi ) {
        const auto status = ps3mapi::PS3MAPIDisconnect ( );

        if ( status != PS3LIB_OK ) {
            throw std::runtime_error ( "Failed to disconnect." );
            return PS3LIB_ERROR;
        }
    }

    EX_HANDLER_END

    return PS3LIB_OK;
}

std::deque < ps3lib::process_info_t > ps3lib::get_process_info ( ) {
    std::deque < ps3lib::process_info_t > process_list = { };
    process_list.clear ( );

    using namespace ccapi;

    g_mutex.lock ( );

    if ( connection_type == e_connection_type::type_ccapi ) {
        uint32_t npid;
        process_name name = { };
        ccapi_exports::CCAPIGetProcessList ( &npid, 0 );

        uint32_t* pids = ( uint32_t * ) std::malloc ( npid * sizeof ( uint32_t ) );

        if ( ccapi_exports::CCAPIGetProcessList ( &npid, pids ) == PS3LIB_OK ) {
            process_info_t info = { };

            for ( int i = 0; i < npid; i++ ) {   
                if ( ccapi_exports::CCAPIGetProcessName ( pids [ i ], &info.name ) != PS3LIB_OK )
                    continue;

                info.id = pids [ i ]; 
                process_list.push_back ( info );
            }
        }

        free ( pids );
    }

    g_mutex.unlock ( );

    return process_list;
}

int ps3lib::send_console_action ( const ps3lib::e_shutdown_mode& action ) {
    using namespace ccapi;

    EX_HANDLER_BEGIN

    if ( connection_type == e_connection_type::type_ccapi ) {
        const auto status = ccapi_exports::CCAPIShutdown ( static_cast < int > ( action ) );

        if ( status != PS3LIB_OK ) {
            throw std::runtime_error ( "Failed to shutdown console." );
            return PS3LIB_ERROR;
        }

       // printf ( "[PS3LIB] Console shutdown." );
    }

    else if ( connection_type == e_connection_type::type_ps3mapi ) {
        const auto status = ps3mapi::PS3MAPIShutdown ( static_cast < int > ( action ) );

        if ( status != PS3LIB_OK ) {
            throw std::runtime_error ( "Failed to shutdown console." );
            return PS3LIB_ERROR;
        }

        //printf ( "[PS3LIB] Console shutdown." );
    }

    EX_HANDLER_END

    return PS3LIB_OK;
}

const char* ps3lib::get_host_address ( ) {
    WSAData data;
    if ( WSAStartup ( MAKEWORD ( 2 , 2 ) , &data ) != 0 )
        return 0;

    char hostname [ 128 ]; 
    if ( gethostname ( hostname , sizeof ( hostname ) ) != 0 )
        return 0;

    struct hostent* host = gethostbyname ( hostname );

    if ( host == NULL )
        return 0;

    const char* ret = inet_ntoa ( * ( struct in_addr * ) * host->h_addr_list );

    // no more memory leaks ;)
    WSACleanup ( );

    return ret;
}