#ifndef PHP_BENCHMARK_H
#define PHP_BENCHMARK_H 1
#define PHP_BENCHMARK_VERSION "1.0"
#define PHP_BENCHMARK_EXTNAME "benchmark"

PHP_FUNCTION(bm);
PHP_FUNCTION(bm_write);
PHP_FUNCTION(bm_writeln);

extern zend_module_entry benchmark_module_entry;
#define phpext_benchmark_ptr &benchmark_module_entry

#endif