#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#include "php_benchmark.h"
#include <time.h>

static zend_function_entry benchmark_functions[] = {
    PHP_FE(bm, NULL)
    PHP_FE(bm_write, NULL)
    PHP_FE(bm_writeln, NULL)
    PHP_FE_END
};

zend_module_entry benchmark_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_BENCHMARK_EXTNAME,
    benchmark_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
#if ZEND_MODULE_API_NO >= 20010901
    PHP_BENCHMARK_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_BENCHMARK
ZEND_GET_MODULE(benchmark)
#endif

float run_bm(zval *callable, int n)
{
    float start, end;
    zval return_ptr;

    start = (float) clock() / CLOCKS_PER_SEC;

    for (int i = 0; i < n; i++) {
        call_user_function(CG(function_table), NULL, callable, &return_ptr, 0, NULL TSRMLS_CC);
    }
    
    end = (float) clock() / CLOCKS_PER_SEC;

    return end - start;
}

PHP_FUNCTION(bm)
{
    int n = 100000;
    zval *callable;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|l", &callable, &n) == FAILURE) {
        RETURN_NULL();
    }

    RETURN_DOUBLE(run_bm(callable, n));
}

PHP_FUNCTION(bm_write)
{
    int n = 100000;
    zval *callable;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|l", &callable, &n) == FAILURE) {
        RETURN_NULL();
    }

    php_printf("Benchmark took %f seconds", run_bm(callable, n));
}

PHP_FUNCTION(bm_writeln)
{
    int n = 100000;
    zval *callable;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|l", &callable, &n) == FAILURE) {
        RETURN_NULL();
    }

    php_printf("Benchmark took %f seconds\n", run_bm(callable, n));
}

/*PHP_FUNCTION(benchmark)
{
    float start, end;
    int n = 100000;
    zval *callable, return_ptr;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|l", &callable, &n) == FAILURE) {
        RETURN_NULL();
    }

    start = (float) clock() / CLOCKS_PER_SEC;

    for (int i = 0; i < n; i++) {
        call_user_function(CG(function_table), NULL, callable, &return_ptr, 0, NULL TSRMLS_CC);
    }
    
    end = (float) clock() / CLOCKS_PER_SEC;

    RETURN_DOUBLE(end - start);
}*/