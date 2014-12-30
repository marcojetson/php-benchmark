PHP_ARG_ENABLE(benchmark, whether to enable benchmark support, [ --enable-benchmark   Enable benchmark support])

if test "$PHP_BENCHMARK" = "yes"; then
  AC_DEFINE(HAVE_BENCHMARK, 1, [Whether you have benchmark])
  PHP_NEW_EXTENSION(benchmark, benchmark.c, $ext_shared)
fi