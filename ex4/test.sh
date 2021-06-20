#!/bin/bash

echo 'Start testing'
echo 'Compiling ex4a'

g++ -Wall ex4a.cc -o ex4a

echo 'testing'
echo 'test00'
./ex4a < test/ex4a_test00.in > out.out
./sol/ex4a < test/ex4a_test00.in > out1.out

diff out.out out1.out

echo 'test01'
./ex4a < test/ex4a_test01.in > out.out
./sol/ex4a < test/ex4a_test01.in > out1.out

diff out.out out1.out

echo 'test02'
./ex4a < test/ex4a_test02.in > out.out
./sol/ex4a < test/ex4a_test02.in > out1.out

diff out.out out1.out

echo 'test03'
./ex4a < test/ex4a_test03.in > out.out
./sol/ex4a < test/ex4a_test03.in > out1.out

diff out.out out1.out

echo 'test04'
./ex4a < test/ex4a_test04.in > out.out
./sol/ex4a < test/ex4a_test04.in > out1.out

diff out.out out1.out


echo 'compiling ex4b'

g++ -Wall ex4b.cc -o ex4b

echo 'test00'
./ex4b < test/ex4b_test00.in > out.out
./sol/ex4b < test/ex4b_test00.in > out1.out

diff out.out out1.out

echo 'test01'
./ex4b < test/ex4b_test01.in > out.out
./sol/ex4b < test/ex4b_test01.in > out1.out

diff out.out out1.out

echo 'test02'
./ex4b < test/ex4b_test02.in > out.out
./sol/ex4b < test/ex4b_test02.in > out1.out

diff out.out out1.out

echo 'test03'
./ex4b < test/ex4b_test03.in > out.out
./sol/ex4b < test/ex4b_test03.in > out1.out

diff out.out out1.out

echo 'test04'
./ex4b < test/ex4b_test04.in > out.out
./sol/ex4b < test/ex4b_test04.in > out1.out

diff out.out out1.out


echo 'compiling ex4b'
g++ -Wall ex4c.cc ex4c_given.cc -o ex4c

echo 'test00'
./ex4c < test/ex4c_test00.in > out.out
./sol/ex4c < test/ex4c_test00.in > out1.out

diff out.out out1.out

echo 'test01'
./ex4c < test/ex4c_test01.in > out.out
./sol/ex4c < test/ex4c_test01.in > out1.out

diff out.out out1.out

echo 'test02'
./ex4c < test/ex4c_test02.in > out.out
./sol/ex4c < test/ex4c_test02.in > out1.out

diff out.out out1.out

echo 'test03'
./ex4c < test/ex4c_test03.in > out.out
./sol/ex4c < test/ex4c_test03.in > out1.out

diff out.out out1.out
