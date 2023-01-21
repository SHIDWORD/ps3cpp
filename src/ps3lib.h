#ifndef PS3LIB_PS3LIB_H
#define PS3LIB_PS3LIB_H

#include <windows.h>
#include <cstdio>
#include <inttypes.h>
#include <deque>
#include <mutex>

#define PS3LIB_VERSION "0.1.0"
#define PS3LIB_OK 0
#define PS3LIB_ERROR -1

#include "exception.h"
#include "internet.h"
#include "ccapi.h"
#include "ps3mapi.h"
#include "types.h"

namespace ps3lib {
    inline std::mutex g_mutex;

    enum class e_connection_type : int {
        type_none = 0,
        type_ccapi,
        type_ps3mapi
    };

    inline e_connection_type connection_type = e_connection_type::type_none;
    inline const char* connection_name = "ps3lib";

    enum class e_console_type : int {
        type_cex = 1,
        type_dex,
        type_deh
    };

    struct firmware_info_t {
        float firmware_version;
        float ccapi_version;
        const char* console_type;
    };

    struct process_info_t {
        process_name name;
        uint32_t id;
    };

    __forceinline float get_ccapi_version ( uint32_t version ) {
        return ( float ) ( version / 100 ) + ( ( float ) ( version % 100 ) / 100.0f );
    }

    __forceinline float get_firmware_version ( uint32_t version ) {
        // UGHHHHHHHHHH, its so ugly...
        switch ( version ) {
            case FW466:
                return 4.66f;
            case FW475:
                return 4.75f;
            case FW476:
                return 4.76f;
            case FW478:
                return 4.78f;
            case FW480:
                return 4.80f;
            case FW481:
                return 4.81f;
            case FW482:
                return 4.82f;
            case FW483:
                return 4.83f;
            case FW484:
                return 4.84f;
            case FW485:
                return 4.85f;
            case FW486:
                return 4.86f;
            case FW487:
                return 4.87f;
            case FW488:
                return 4.88f;
            default:
                return 0.0f;
        }
    }

    __forceinline const char* get_console_type ( e_console_type type ) {
        // lol.
        switch ( type ) {
            case e_console_type::type_cex:
                return "CEX";
            case e_console_type::type_dex:
                return "DEX";
            case e_console_type::type_deh:
                return "DEH";
            default:
                return "UNKNOWN";
        }

        return "UNKNOWN";
    }

    enum class e_shutdown_mode : int {
       action_shutdown = 1,
       action_soft_reboot = 2,
       action_hard_reboot = 3
    };

    enum class e_led_color : uint8_t {
        led_red = 0,
        led_green = 1,
        led_yellow = ( led_red | led_green )
    };

    enum class e_led_action : uint8_t {
        led_action_off,
        led_action_on,
        led_action_blink
    };

    enum class e_ring_buzzer_action : uint16_t {
        ring_buzzer_continuous = 0,
        ring_buzzer_single = 1,
        ring_buzzer_double = 2,
        ring_buzzer_triple = 3
    };

    enum e_notify_icon : uint8_t {
       notify_info = 0,
       notify_caution = 1,
       notify_friend = 2,
       notify_slider = 3,
       notify_wrongway = 4,
       notify_dialog = 5,
       notify_dalogshadow = 6,
       notify_text = 7,
       notify_pointer = 8,
       notify_grab = 9,
       notify_hand = 10,
       notify_pen = 11,
       notify_finger = 12,
       notify_arrow = 13,
       notify_arrowright = 14,
       notify_progress = 15, 
       notify_trophy1 = 16,
       notify_trophy2 = 17,
       notify_trophy3 = 18,
       notify_trophy4 = 19
    };

    int initialize ( );
    int connect ( const char* ip , const ps3lib::e_connection_type type , const char* name = "console" );
    int vsh_notify ( const ps3lib::e_notify_icon& icon , const char* msg );
    int ring_buzzer ( const ps3lib::e_ring_buzzer_action& action );
    int set_console_led ( const ps3lib::e_led_action& action , const ps3lib::e_led_color& color );
    int get_firmware_info_ccapi ( uint32_t* firmware , uint32_t* ccapi , int* type );
    int get_firmware_info_ps3mapi ( uint32_t* firmware , int* type );
    int send_console_action ( const ps3lib::e_shutdown_mode& action );
    std::deque < ps3lib::process_info_t > get_process_info ( );
    int set_console_ids ( const e_console_id_type& type, const char* id );
    int set_boot_console_ids ( const e_console_id_type& type, bool enabled, const char* id );
    firmware_info_t get_firmware_info_data ( );
    int get_temperature ( int* cpu, int* rsx );
    const char* get_temperature ( );
    const char* get_firmware_info ( );
    const char* get_host_address ( );
    int disconnect ( );
}

#endif // !PS3LIB_PS3LIB_H