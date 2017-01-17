/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_queue.h"
#include "list.h"

/* If you declare any globals in php_queue.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(queue)
*/

/* True global resources - no need for thread safety here */
static int le_queue;

#define RESOURCE_TYPE_NAME "queue resource"

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("queue.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_queue_globals, queue_globals)
    STD_PHP_INI_ENTRY("queue.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_queue_globals, queue_globals)
PHP_INI_END()
*/
/* }}} */

PHP_FUNCTION(queue_new)
{
    zval *res;
    list_t *ls;
    int rsid;

    ls = list_create(); /* Create list resource */
    if (!ls) {
        RETURN_FALSE;
    }

    rsid = ZEND_REGISTER_RESOURCE(res, ls, le_queue);

    RETURN_RESOURCE(rsrc_id);
}

PHP_FUNCTION(queue_push)
{
    zval *res, *data;
    list_t *ls;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rz", &res, &data)
        == FAILURE)
    {
        RETURN_FALSE;
    }

    ZEND_FETCH_RESOURCE(ls, list_t, &res, -1, RESOURCE_TYPE_NAME, le_queue);

    if (list_push(ls, (void *)data) == 0) {
        zval_add_ref(data); /* refcount++ */
        RETURN_TRUE;
    }

    RETURN_FALSE;
}

PHP_FUNCTION(queue_pop)
{
    zval *res, *data;
    list_t *ls;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &res, &data)
        == FAILURE)
    {
        RETURN_FALSE;
    }

    ZEND_FETCH_RESOURCE(ls, list_t, &res, -1, RESOURCE_TYPE_NAME, le_queue);

    if (list_pop(ls, (void **)&data) == 0) {
        RETURN_ZVAL(data, 1, 1);
    }

    RETURN_FALSE;
}


/* {{{ php_queue_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_queue_init_globals(zend_queue_globals *queue_globals)
{
	queue_globals->global_value = 0;
	queue_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */

void list_destructor(zend_rsrc_entry *rsrc TSRMLS_DC)
{
    list_t *ls = (list_t *)rsrc->ptr;
    list_free(ls);
}

PHP_MINIT_FUNCTION(queue)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
    /* Register destructor function */
    le_queue = zend_register_list_destructors_ex(
        &list_destructor, NULL, RESOURCE_TYPE_NAME, module_number);
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(queue)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(queue)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(queue)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(queue)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "queue support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ queue_functions[]
 *
 * Every user visible function must have an entry in queue_functions[].
 */
const zend_function_entry queue_functions[] = {
    PHP_FE(queue_new,  NULL)
    PHP_FE(queue_push, NULL)
    PHP_FE(queue_pop,  NULL)
	PHP_FE_END	/* Must be the last line in queue_functions[] */
};
/* }}} */

/* {{{ queue_module_entry
 */
zend_module_entry queue_module_entry = {
	STANDARD_MODULE_HEADER,
	"queue",
	queue_functions,
	PHP_MINIT(queue),
	PHP_MSHUTDOWN(queue),
	PHP_RINIT(queue),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(queue),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(queue),
	PHP_QUEUE_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_QUEUE
ZEND_GET_MODULE(queue)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
