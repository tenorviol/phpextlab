
#ifndef PHP_CALLBACK_H
#define PHP_CALLBACK_H

extern zend_module_entry callback_module_entry;
#define phpext_callback_ptr &callback_module_entry

#ifdef PHP_WIN32
#	define PHP_CALLBACK_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_CALLBACK_API __attribute__ ((visibility("default")))
#else
#	define PHP_CALLBACK_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(callback);
PHP_MSHUTDOWN_FUNCTION(callback);
PHP_MINFO_FUNCTION(callback);

PHP_FUNCTION(confirm_callback_compiled);	/* For testing, remove later. */

/* In every utility function you add that needs to use variables 
   in php_callback_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as CALLBACK_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define CALLBACK_G(v) TSRMG(callback_globals_id, zend_callback_globals *, v)
#else
#define CALLBACK_G(v) (callback_globals.v)
#endif

#endif	/* PHP_CALLBACK_H */
