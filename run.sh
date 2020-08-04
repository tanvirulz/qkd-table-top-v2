#!/bin/bash

mkdir -p $3 

./rrswabian $1 $2 $3

#correction for Aaice 
./crt $3 alice 0 -500 0 -1000


rm $3/alice.out

#correction for Bob
./crt $3 bob 0 500 -2500 500

rm $3/bob.out

if [ -z "$5" ]
    then
        printf  "input_filename, alice_singles_rate, bob_singles_rate, coincidence_window(ps), coincidence_count_rate, sifted_key_length, num_error, QBER, hv_count,ad_count,alice_efficiency(%%), bob_effeciency(%%),duration(s)\n" > ./$3/$4
fi 


printf "$2," >> $3/$4

# ./cm [workDirectory] [coincidenceWindow] [matchingShift]
./cm $3 2000 -5500 >> $3/$4


#./sift $3 alice 
#./sift $3 bob 

rm $3/alice_corrected.out
rm $3/bob_corrected.out
rm $3/alice_coin.out
rm $3/bob_coin.out
rm $3/basis_match_bitmask.out


