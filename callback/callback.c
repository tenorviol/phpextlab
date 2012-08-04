
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_callback.h"

/* If you declare any globals in php_callback.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(callback)
*/

/* True global resources - no need for thread safety here */
static int le_callback;

/* Every user visible function must have an entry in callback_functions[].
 */
const zend_function_entry callback_functions[] = {
	PHP_FE(confirm_callback_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in callback_functions[] */
};

zend_module_entry callback_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"callback",
	callback_functions,
	PHP_MINIT(callback),
	PHP_MSHUTDOWN(callback),
	NULL,
	NULL,
	PHP_MINFO(callback),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* version */
#endif
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_CALLBACK
ZEND_GET_MODULE(callback)
#endif

/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("callback.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_callback_globals, callback_globals)
    STD_PHP_INI_ENTRY("callback.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_callback_globals, callback_globals)
PHP_INI_END()
*/

/* Uncomment this function if you have INI entries
static void php_callback_init_globals(zend_callback_globals *callback_globals)
{
	callback_globals->global_value = 0;
	callback_globals->global_string = NULL;
}
*/

PHP_MINIT_FUNCTION(callback)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(callback)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}

PHP_MINFO_FUNCTION(callback)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "callback support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}


/* Remove the following function when you have succesfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* proto string confirm_callback_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_callback_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "callback", arg);
	RETURN_STRINGL(strg, len, 0);
}
