/* phiz extension for PHP */

#ifndef PHP_PHIZ_H
# define PHP_PHIZ_H

extern zend_module_entry phiz_module_entry;
# define phpext_phiz_ptr &phiz_module_entry

# define PHP_PHIZ_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_PHIZ)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_PHIZ_H */