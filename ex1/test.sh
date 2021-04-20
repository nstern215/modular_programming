#!/bin/bash

echo 'Start testing'
echo 'compliling ex1a'
g++ -Wall ex1a.cc -o ex1a

echo 'testing ex1a'
echo 'test 0'
./ex1a < tests/ex1a_test00.in > o.out
./sol/ex1a < tests/ex1a_test00.in > o1.out
diff o.out o1.out

echo 'test 1'
./ex1a < tests/ex1a_test01.in > o.out
./sol/ex1a < tests/ex1a_test01.in > o1.out
diff o.out o1.out

echo 'test 2'
./ex1a < tests/ex1a_test02.in > o.out
./sol/ex1a < tests/ex1a_test02.in > o1.out
diff o.out o1.out



echo 'compliling ex1b'
g++ -Wall ex1b.cc -o ex1b

echo 'testing ex1b'
echo 'test 0'
./ex1b < tests/ex1b_test00.in > o.out
./sol/ex1b < tests/ex1b_test00.in > o1.out
diff o.out o1.out

echo 'test 1'
./ex1b < tests/ex1b_test01.in > o.out
./sol/ex1b < tests/ex1b_test01.in > o1.out
diff o.out o1.out

echo 'test 2'
./ex1b < tests/ex1b_test02.in > o.out
./sol/ex1b < tests/ex1b_test02.in > o1.out
diff o.out o1.out

echo 'test 4'
./ex1b < tests/ex1b_test04.in > o.out
./sol/ex1b < tests/ex1b_test04.in > o1.out
diff o.out o1.out


echo 'compliling ex1c'
g++ -Wall ex1c.cc -o ex1c

echo 'testing ex1c'
echo 'test 0'
./ex1c < tests/ex1c_test00.in > o.out
./sol/ex1c < tests/ex1c_test00.in > o1.out
diff o.out o1.out

echo 'test 1'
./ex1c < tests/ex1c_test01.in > o.out
./sol/ex1c < tests/ex1c_test01.in > o1.out
diff o.out o1.out

echo 'test 2'
./ex1c < tests/ex1c_test02.in > o.out
./sol/ex1c < tests/ex1c_test02.in > o1.out
diff o.out o1.out

echo 'test 3'
./ex1c < tests/ex1c_test03.in > o.out
./sol/ex1c < tests/ex1c_test03.in > o1.out
diff o.out o1.out

echo 'test 4'
./ex1c < tests/ex1c_test04.in > o.out
./sol/ex1c < tests/ex1c_test04.in > o1.out
diff o.out o1.out

echo 'test 5'
./ex1c < tests/ex1c_test05.in > o.out
./sol/ex1c < tests/ex1c_test05.in > o1.out
diff o.out o1.out