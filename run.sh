#!/bin/bash

mkdir -p $3 
#echo $1/$2
./rrswabian $1 $2 $3

./crt $3 alice 1000 2000 4500 3000
rm $3/alice.out

./crt $3 bob 0 0 0 3000
rm $3/bob.out

./cm $3 1500 

./sift $3 alice 
./sift $3 bob 

rm $3/alice_corrected.out
rm $3/bob_corrected.out
rm $3/alice_coin.out
rm $3/bob_coin.out

