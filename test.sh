#!/bin/bash

#build
make

#tests:
echo "benchmark I: Oxford Dictionary word counting."
./b1 data/oxfordDict.txt | tee result1.txt

echo "benchmark II: random int counting."
for ((i = 1024; i < 1000*1000; i *= 2))
do
	./b2 $i | tee -a result2.txt
done

for ((i = 10000; i < 100*10000; i += 10000))
do
	./b2 $i | tee -a result22.txt
done

echo "benchmark III: random insert and random find."
for ((i = 10000; i < 100*10000; i += 10000))
do
	./b3 $i | tee -a result3.txt
done
