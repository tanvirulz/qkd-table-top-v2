#!/bin/bash

mkdir -p $3 

./rrswabian $1 $2 $3

#correction for Aaice 
./crt $3 alice 500 1500 1500 0
rm $3/alice.out

#correction for Bob
./crt $3 bob 2500 2500 0 3000

rm $3/bob.out

if [ -z "$5" ]
    then
        printf  "input_filename, alice_singles_rate, bob_singles_rate, coincidence_window(ps), coincidence_count_rate, sifted_key_length, num_error, QBER, hv_count,ad_count,alice_efficiency(%%), bob_effeciency(%%),duration(s)\n" >> ./$3/$4
fi 


printf "$2," >> $3/$4

./cm $3 1500 -6500 >> $3/$4


#./sift $3 alice 
#./sift $3 bob 

rm $3/alice_corrected.out
rm $3/bob_corrected.out
rm $3/alice_coin.out
rm $3/bob_coin.out
rm $3/basis_match_bitmask.out


