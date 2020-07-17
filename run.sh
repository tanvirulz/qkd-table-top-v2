#!/bin/bash

mkdir -p $3 

./rrswabian $1 $2 $3

./crt $3 alice 1000 2000 4500 3000
rm $3/alice.out

./crt $3 bob 0 0 0 3000
rm $3/bob.out

#printf  "input_filename, alice_singles, bob_singles, coincidence_window(ps), coincidence_count, sifted_key_length, num_error, QBER, hv_count,ad_count,alice_efficiency(%%), bob_effeciency(%%)\n" >> ./$3/log.txt

printf "$2," >> $3/$4

./cm $3 1500 >> $3/$4


#./sift $3 alice 
#./sift $3 bob 

rm $3/alice_corrected.out
rm $3/bob_corrected.out
rm $3/alice_coin.out
rm $3/bob_coin.out
rm $3/basis_match_bitmask.out


