#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#include "php_benchmark.h"
#include <time.h>

#define DEFAULT_N 100000

static zend_function_entry benchmark_functions[] = {
    PHP_FE(bm, NULL)
    PHP_FE(bm_cmp, NULL)
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
    int n = DEFAULT_N;
    zval *callable;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|l", &callable, &n) == SUCCESS) {
        RETURN_DOUBLE(run_bm(callable, n));
    }
}

PHP_FUNCTION(bm_cmp)
{
    float bm1, bm2;
    int n = DEFAULT_N, ret;
    zval *callable1, *callable2;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz|l", &callable1, &callable2, &n) == SUCCESS) {
        bm1 = run_bm(callable1, n);
        bm2 = run_bm(callable2, n);

        if (bm1 > bm2) {
            ret = 1;
        } else if (bm1 < bm2) {
            ret = -1;
        } else {
            ret = 0;
        }

        RETURN_LONG(ret);
    }
}

PHP_FUNCTION(bm_write)
{
    int n = DEFAULT_N;
    zval *callable;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|l", &callable, &n) == SUCCESS) {
        php_printf("bm took %f seconds", run_bm(callable, n));
    }
}

PHP_FUNCTION(bm_writeln)
{
    int n = DEFAULT_N;
    zval *callable;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|l", &callable, &n) == SUCCESS) {
        php_printf("bm took %f seconds\n", run_bm(callable, n));
    }
}
