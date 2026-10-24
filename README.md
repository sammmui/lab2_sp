# lab2_sp
компіляція 
g++ -O0 -g Source.cpp -o Source_O0
g++ -O3 -march=native -g Source.cpp -o Source_O3

FlameGraph
sudo perf record -F 99 -g -o /tmp/perf.data ./Source_O0
sudo perf script -i /tmp/perf.data > out.perf
./FlameGraph/stackcollapse-perf.pl out.perf > out.folded
./FlameGraph/flamegraph.pl out.folded > flamegraph_O0.svg

Статистика виконання
/usr/bin/time --verbose ./Source_O0
sudo perf stat -d ./Source_O0
sudo perf report -i /tmp/perf.data

Енерговитрати
sudo perf stat -e power/energy-pkg/,power/energy-cores/ ./Source_O0