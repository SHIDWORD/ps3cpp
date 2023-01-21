#include "includes.h"
#include <iostream>

int main ( ) {
    if ( ps3lib::initialize ( ) != PS3LIB_OK ) {
        printf ( "Failed to initialize ps3lib!\n" );
        return 1;
    }

    if ( ps3lib::connect ( "192.168.1.71", ps3lib::e_connection_type::type_ccapi, "awesome ps3" ) != PS3LIB_OK ) {
        return 1;
    }

    std::cout << ps3lib::get_firmware_info ( ) << std::endl;
    std::cout << ps3lib::get_temperature ( ) << std::endl;

    auto info = ps3lib::get_process_info ( );

    for ( int i = 0; i < info.size ( ); i++ ) {
        std::cout << info [ i ].id << " - " << info [ i ].name << std::endl;
    }

    ps3lib::set_console_led ( ps3lib::e_led_action::led_action_on , ps3lib::e_led_color::led_green );

    return 0;
}