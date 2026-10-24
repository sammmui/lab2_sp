# Лабораторна робота 2
###Системне програмування  
###Виконала студентка групи ТТА-31 Балєєва Марія

## 1. Компіляція програми
Програма була скомпільована у двох варіантах — базовому (без оптимізацій) та оптимізованому (з векторизацією):

# Базова версія (-O0)
g++ -O0 -g Source.cpp -o Source_O0
# Оптимізована версія (-O3 з SIMD)
g++ -O3 -march=native -g Source.cpp -o Source_O3

##2. Побудова FlameGrap1. Побудова FlameGraph
sudo perf record -F 99 -g -o /tmp/perf.data ./Source_O0
sudo perf script -i /tmp/perf.data > out.perf
./FlameGraph/stackcollapse-perf.pl out.perf > out.folded
./FlameGraph/flamegraph.pl out.folded > flamegraph_O0.svg

##3.Статистика виконання
/usr/bin/time --verbose ./Source_O0
sudo perf stat -d ./Source_O0
sudo perf report -i /tmp/perf.data

##4.Енерговитрати (Power Consumption)
sudo perf stat -e power/energy-pkg/,power/energy-cores/ ./Source_O0

##5.Аналіз асемблеру та SIMD-інструкції (Godbolt)
-Без оптимізації (-O0): Процесор використовує базові скалярні інструкції (наприклад, mulss, addss), обробляючи лише одне число float за такт.
-Після оптимізації (-O3 -march=native): Компілятор застосував авто-векторизацію. Використовуються векторні SIMD-інструкції розширення AVX (наприклад, vmulps - Vector Multiply Packed Single, vaddps). Це дозволяє запакувати відразу кілька чисел типу float в один регістр і виконати математичну операцію над масивом даних за один апаратний такт.
