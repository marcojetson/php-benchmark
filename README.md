# Functions

    float bm (callable $callable [, int $n = 100000] )
Runs $callable $n times and returns elapsed time

    float bm_write (callable $callable [, int $n = 100000] )
Runs $callable $n times and outputs elapsed time

    float bm_writeln (callable $callable [, int $n = 100000] )
Runs $callable $n times and outputs elapsed time appending a new line

# Build

phpize
./configure --enable-benchmark
make