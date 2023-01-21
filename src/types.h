#ifndef PS3LIB_TYPES_H
#define PS3LIB_TYPES_H

#include <cstdint>

// firmwares.
#define FW466 0x4066000
#define FW475 0x4075000
#define FW476 0x4076000 
#define FW478 0x4078000
#define FW480 0x4080000
#define FW481 0x4081000
#define FW482 0x4082000 
#define FH482 0x4082000
#define FW483 0x4083000
#define FW484 0x4084000
#define FW485 0x4085000
#define FW486 0x4086000
#define FW487 0x4087000
#define FW488 0x4088000

// it's the same for ps3mapi and ccapi i think lol.
enum class e_console_id_type : uint8_t  {
   idps = 0,
   psid = 1
};

using u32 = unsigned int;
using u64 = unsigned long long;
using console_id = uint8_t [ 16 ];
using process_name = char [ 512 ];

#endif // !PS3LIB_TYPES_H