#!/bin/bash

echo 'Start testing'
echo 'Compiling ex3a'

g++ -Wall ex3a.cc -o ex3a

echo 'testing ex3a'
echo 'test 00'
./ex3a < tests/ex-b-3a_test00.in > out.out
./sol/ex3a < tests/ex-b-3a_test00.in > out1.out

diff out.out out1.out

echo 'test 01'
./ex3a < tests/ex-b-3a_test01.in > out.out
./sol/ex3a < tests/ex-b-3a_test01.in > out1.out

diff out.out out1.out

echo 'test 02'
./ex3a < tests/ex-b-3a_test02.in > out.out
./sol/ex3a < tests/ex-b-3a_test02.in > out1.out

diff out.out out1.out


echo 'Compiling ex3b'

g++ -Wall ex3b.cc -o ex3b

echo 'testing ex3b'
echo 'test 00'
./ex3b < tests/ex3b_test00.in > out.out
./sol/ex3b < tests/ex3b_test00.in > out1.out

diff out.out out1.out

echo 'test 01'
./ex3b < tests/ex3b_test01.in > out.out
./sol/ex3b < tests/ex3b_test01.in > out1.out

diff out.out out1.out

echo 'test 02'
./ex3b < tests/ex3b_test02.in > out.out
./sol/ex3b < tests/ex3b_test02.in > out1.out

diff out.out out1.out

echo 'test 03'
./ex3b < tests/ex3b_test03.in > out.out
./sol/ex3b < tests/ex3b_test03.in > out1.out

diff out.out out1.out


echo 'Compiling ex3c'

g++ -Wall ex3c.cc -o ex3c

echo 'testing ex3c'
echo 'test 00'
./ex3c < tests/ex-b-3c_test00.in > out.out
./sol/ex3c < tests/ex-b-3c_test00.in > out1.out

diff out.out out1.out

echo 'test 01'
./ex3c < tests/ex-b-3c_test01.in > out.out
./sol/ex3c < tests/ex-b-3c_test01.in > out1.out

diff out.out out1.out

echo 'test 02'
./ex3c < tests/ex-b-3c_test02.in > out.out
./sol/ex3c < tests/ex-b-3c_test02.in > out1.out

diff out.out out1.out

echo 'test 03'
./ex3c < tests/ex-b-3c_test03.in > out.out
./sol/ex3c < tests/ex-b-3c_test03.in > out1.out

diff out.out out1.out

echo 'test 04'
./ex3c < tests/ex-b-3c_test04.in > out.out
./sol/ex3c < tests/ex-b-3c_test04.in > out1.out

diff out.out out1.out

echo 'test 05'
./ex3c < tests/ex-b-3c_test05.in > out.out
./sol/ex3c < tests/ex-b-3c_test05.in > out1.out

diff out.out out1.out