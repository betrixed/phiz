/* phiz extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "zend_exceptions.h"
#include "phiz_arginfo.h"
#include "ext/standard/info.h"
#include "php_phiz.h"

ZEND_DECLARE_MODULE_GLOBALS(phiz)
static PHP_GINIT_FUNCTION(phiz);
static PHP_GSHUTDOWN_FUNCTION(phiz);



/* {{{ PHP_INI_BEGIN */
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("phiz.scale", "4", PHP_INI_ALL, OnUpdateLong, scale,
        zend_phiz_globals, phiz_globals)
PHP_INI_END()
/* }}} */


/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(phiz)
{
	REGISTER_INI_ENTRIES();
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION */
PHP_MSHUTDOWN_FUNCTION(phiz)
{
	UNREGISTER_INI_ENTRIES();

	return SUCCESS;
}
/* }}} */




/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(phiz)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "phiz support", "enabled");
	php_info_print_table_end();
	DISPLAY_INI_ENTRIES();
}
/* }}} */


/* {{{ phiz_module_entry */
zend_module_entry phiz_module_entry = {
	STANDARD_MODULE_HEADER,
	"phiz",					/* Extension name */
	ext_functions,					/* zend_function_entry */
	PHP_MINIT(phiz),							/* PHP_MINIT - Module initialization */
	PHP_MSHUTDOWN(phiz),							/* PHP_MSHUTDOWN - Module shutdown */
	NULL,			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(phiz),			/* PHP_MINFO - Module info */
	PHP_PHIZ_VERSION,		/* Version */
	PHP_MODULE_GLOBALS(phiz), /* module globals */
	PHP_GINIT(phiz),		/* globals init */
	PHP_GSHUTDOWN(phiz),					/* PHP_GSHUTODWN for globals */
	NULL,	
	STANDARD_MODULE_PROPERTIES_EX
};
/* }}} */


#ifdef COMPILE_DL_PHIZ
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(phiz)
#endif


/* {{{ ZEND_INI_MH */ 
ZEND_INI_MH(OnUpdateLong)
{
	int *p;
	zend_long tmp;

	tmp = zend_atol(ZSTR_VAL(new_value), ZSTR_LEN(new_value));
	if (tmp < 0 || tmp > INT_MAX) {
		return FAILURE;
	}

	p = (int *) ZEND_INI_GET_ADDR();
	*p = (int) tmp;

	return SUCCESS;
}
/* }}} */





/* {{{ PHP_GINIT_FUNCTION */
static PHP_GINIT_FUNCTION(phiz)
{
#if defined(ZTS) && defined(COMPILE_DL_PHIZ)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	phiz_globals->scale = 4;
}
/* }}} */


/* {{{ PHP_GSHUTDOWN_FUNCTION */
static PHP_GSHUTDOWN_FUNCTION(phiz)
{

}
/* }}} */



/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

/* {{{ void test1() */
PHP_FUNCTION(test1)
{
	ZEND_PARSE_PARAMETERS_NONE();

	php_printf("The extension %s is loaded and working!\r\n", "phiz");
}
/* }}} */


/* {{{ string test2( [ string $var ] ) */
PHP_FUNCTION(test2)
{
	char *var = "World";
	size_t var_len = sizeof("World") - 1;
	zend_string *retval;

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STRING(var, var_len)
	ZEND_PARSE_PARAMETERS_END();

	retval = strpprintf(0, "Hello %s", var);

	RETURN_STR(retval);
}
/* }}}*/

/* {{{ double test_scale( double $x ) */
ZEND_FUNCTION(test_scale)
{
     double x;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_DOUBLE(x)
    ZEND_PARSE_PARAMETERS_END();
    RETURN_DOUBLE( x * PHIZ_G(scale));
}	
/* }}}*/








