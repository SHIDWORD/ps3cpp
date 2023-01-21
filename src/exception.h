#ifndef PS3LIB_EXCEPTION_H
#define PS3LIB_EXCEPTION_H

#include <exception>
#include <stdexcept>
#include <cstdio>

#define EX_HANDLER_BEGIN try { 
#define EX_HANDLER_END } catch ( std::exception& e ) { printf ( "[PS3LIB] [THROW] %s (0x%08X) at %s:%d in %s ()\r \n" , e.what ( ) , e.what ( ) , __FILE__ , __LINE__ , __FUNCTION__ ) ; return 0 ; } catch ( ... ) { printf ( "Unknown exception at %s:%d in %s ()\r \n" , __FILE__ , __LINE__ , __FUNCTION__ ) ; return 0 ; }
#define EX_HANDLER_END_NORET } catch ( std::exception& e ) { printf ( "[PS3LIB] [THROW] %s (0x%08X) at %s:%d in %s ()\r \n" , e.what ( ) , e.what ( ) , __FILE__ , __LINE__ , __FUNCTION__ ) ; return ; } catch ( ... ) { printf ( "Unknown exception at %s:%d in %s ()\r \n" , __FILE__ , __LINE__ , __FUNCTION__ ); return }

#endif // !PS3LIB_EXCEPTION_H