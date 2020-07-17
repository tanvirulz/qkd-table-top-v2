// writing on a text file
#include <iostream>
#include <fstream>


#include <stdio.h>
#include <inttypes.h>
//#include <stdlib.h> 

#define BUFFER_SIZE (32*1024)
#define H 1
#define V 2
#define A 4
#define D 8

#define AD_BASIS 3
#define HV_BASIS 12


using namespace std;

int main(){
    char ainBuffer[BUFFER_SIZE];
    char binBuffer[BUFFER_SIZE];
    char aoutBuffer[BUFFER_SIZE];
    char boutBuffer[BUFFER_SIZE];
    char basismatchBuffer[BUFFER_SIZE];

    
    uint64_t a_ts;
    uint64_t b_ts;
    uint64_t a_det;
    uint64_t b_det;
    
    int64_t cwindow;

    int64_t shift;
    int64_t diff;


    uint32_t ia;
    uint32_t ib;


    int coincount;
    int basis_match_count;
    uint8_t basis_match_flag;

    
    ifstream ainfile;
    ifstream binfile;
    ofstream aoutfile;
    ofstream boutfile;
    ofstream basis_match_outfile;


    ainfile.rdbuf()->pubsetbuf(ainBuffer, BUFFER_SIZE);
    binfile.rdbuf()->pubsetbuf(binBuffer, BUFFER_SIZE);
    aoutfile.rdbuf()->pubsetbuf(aoutBuffer, BUFFER_SIZE);
    boutfile.rdbuf()->pubsetbuf(boutBuffer, BUFFER_SIZE);
    basis_match_outfile.rdbuf()->pubsetbuf(basismatchBuffer, BUFFER_SIZE);


    ainfile.open("./testdata/alice_corrected.out", ios::in|ios::binary);
    binfile.open("./testdata/bob_corrected.out", ios::in|ios::binary);

    aoutfile.open("./testdata/alice_coin.out",ios::out|ios::binary|ios::trunc);
    boutfile.open("./testdata/bob_coin.out",ios::out|ios::binary|ios::trunc);
    basis_match_outfile.open("./testdata/basis_match_bitmask.out",ios::out|ios::binary|ios::trunc);
    
    basis_match_flag =  0;
    basis_match_count = 0;
    ia = 0;
    ib = 0;
    shift = -9*500;
    cwindow = 500;
    coincount = 0;

    ainfile.read(reinterpret_cast<char *>(&a_ts),sizeof(a_ts));
    if (ainfile.eof()) exit(0); // EOF can only be detected after the final *failed* read attempt. 
    a_det  = a_ts & uint64_t(0xF);
    a_ts = a_ts>>4;
    

    binfile.read(reinterpret_cast<char *>(&b_ts),sizeof(b_ts));
    if (binfile.eof()) exit(0);
    b_det = b_ts & uint64_t (0xF);
    b_ts = b_ts >>4;

    int debugloopcount = 0;
    int hv_count =0;
    int ad_count =0;
    while( 1 ){
        //if(debugloopcount ==34342903) break;
        //if(debugloopcount%10240 ==0) printf("debugcount at %d, coincidence count = %d\n",debugloopcount,coincount);
        //a_det = a_ts & uint64_t(0xF);
        //b_det = b_ts & uint64_t(0xF);

        
        //printf("a_ts =%" PRIu64 "\n", a_ts);
        //printf("b_ts =%" PRIu64 "\n", b_ts);

        diff = b_ts - a_ts + shift; 
        //printf("diff =%" PRId64 "\n\n", diff);

        if (abs(diff)<=cwindow){
            

            coincount +=1;
            aoutfile.write(reinterpret_cast<char *>(&ia),sizeof(ia));
            boutfile.write(reinterpret_cast<char *>(&ib),sizeof(ib));         
            //check basis match
            if ( (a_det & uint64_t(AD_BASIS)) && (b_det & uint16_t(AD_BASIS) )){
                basis_match_flag = 1;
                basis_match_count ++;
                hv_count ++;
            }
            else if( (a_det & uint64_t(HV_BASIS)) && (b_det & uint16_t(HV_BASIS)) ){
                basis_match_flag = 1;
                basis_match_count ++;
                ad_count ++;
            }
            else {
                basis_match_flag = 0;
            }

            // [ToDO] this is a characterwise bitmap. I should convert it into a bitwise bitmap
            basis_match_outfile.write(reinterpret_cast<char *>(&basis_match_flag),sizeof(basis_match_flag)); 

            //writebasis info



            ia+=1;
            ib+=1;
            
            ainfile.read(reinterpret_cast<char *>(&a_ts),sizeof(a_ts));
            if (ainfile.eof()) exit(0); // EOF can only be detected after the final *failed* read attempt. 
            a_det = a_ts & uint64_t (0xF);
            a_ts = a_ts>>4;
            

            binfile.read(reinterpret_cast<char *>(&b_ts),sizeof(b_ts));
            if (binfile.eof()) exit(0);
            b_det = b_ts & uint64_t (0xF);
            b_ts = b_ts >>4;
            
            

                    
        }
        else if (diff>cwindow){
            //printf("here!\n");
            //printf("cwindow =%" PRId64 "\n\n", cwindow);
            ia+=1;
            ainfile.read(reinterpret_cast<char *>(&a_ts),sizeof(a_ts));
            if (ainfile.eof()) break; // EOF can only be detected after the final *failed* read attempt. 
            a_det = a_ts & uint64_t (0xF);
            a_ts = a_ts>>4;
        }
        else if ( diff < -cwindow){
            ib+=1;
            binfile.read(reinterpret_cast<char *>(&b_ts),sizeof(b_ts));
            if (binfile.eof()) break;
            b_det = b_ts & uint64_t (0xF);
            b_ts = b_ts>>4;
        }
        else{
            printf ("ERROR! I should not be here.\n");

            exit(0);
        }
        //debugloopcount ++;
    }
    basis_match_outfile.close();
    ainfile.close();
    binfile.close();
    aoutfile.close();
    boutfile.close();
    
    printf("Total coincidences found = %d\n\n",coincount);
    
    printf("Total Basis matched coincidence count = %d\n",basis_match_count);
    printf("hv_count = %d\n",hv_count);
    printf("ad_count = %d\n",ad_count);
    printf("hv+ad counts = %d\n\n",hv_count+ad_count);
    printf("Item scanned ia = %d,ib=%d\n",(int)ia,(int)ib );


    return 0;
}