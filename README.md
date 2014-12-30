# php-benchmark

## Functions

    float bm (callable $callable [, int $n = 100000] )
Runs $callable $n times and returns elapsed time

    int bm_cmp (callable $callable1, callable $callable2 [, int $n = 100000] )
Compares $callable1 to $callable2 running $n times

    void bm_write (callable $callable [, int $n = 100000] )
Runs $callable $n times and outputs elapsed time

    void bm_writeln (callable $callable [, int $n = 100000] )
Runs $callable $n times and outputs elapsed time appending a new line

## Build

    phpize
    ./configure --enable-benchmark
    make
