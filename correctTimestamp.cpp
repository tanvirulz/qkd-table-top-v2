// writing on a text file
#include <iostream>
#include <fstream>


#include <stdio.h>
#include <inttypes.h>

#define BUFFER_SIZE (32*1024)
#define H 1
#define V 2
#define A 4
#define D 8

using namespace std;

int main(){
    char inBuffer[BUFFER_SIZE];
    char outBuffer[BUFFER_SIZE];
    uint64_t raw_ts; //rawtimestamp
    uint64_t corrected_ts;
    uint64_t detector;

    int64_t cH,cV,cA,cD;
    int counter=0;  //delete it

    cH=0;
    cV=0;
    cA=0;
    cD=0;

    //alice correction 
    //cH=0;cV=1*500;cA=2*500+5*500;cD=5*500;
    //bob correction 
    cH=0;cV=0;cA=7*500;cD=0;

    ifstream infile;
    ofstream outfile;

    infile.rdbuf()->pubsetbuf(inBuffer, BUFFER_SIZE);
    outfile.rdbuf()->pubsetbuf(outBuffer, BUFFER_SIZE);

    infile.open("./testdata/bob.out", ios::in|ios::binary);
    outfile.open("./testdata/bob_corrected.out",ios::out|ios::binary|ios::trunc);

    while( 1 ){
        infile.read(reinterpret_cast<char *>(&raw_ts),sizeof(raw_ts));
        if (infile.eof()) break; // EOF can only be detected after the final *failed* read attempt. 


        detector = raw_ts & uint64_t(0xF);
        raw_ts = raw_ts >> 4;
        //printf("ts =%" PRIu64 "\n", raw_ts);
        //printf("detector =%" PRIu64 "\n", detector);
        
        switch (detector)
        {
        case H:
            corrected_ts = raw_ts + cH;
            break;
        case V:
            corrected_ts = raw_ts + cV;
            break;
        case A:
            corrected_ts = raw_ts + cA;
            break;
        case D:
            corrected_ts = raw_ts + cD;
            break;
        
        default:
            printf("error!\n");
            printf("at position %d\n",counter);
            printf("ts =%" PRIu64 "\n", raw_ts);
            printf("detector =%" PRIu64 "\n", detector);
            exit(1);
            break;
        }
        corrected_ts = (corrected_ts <<4)|detector;
        outfile.write(reinterpret_cast<char *>(&corrected_ts),sizeof(corrected_ts));
        //outfile.write(reinterpret_cast<char *>(&raw_ts),sizeof(raw_ts));
        counter++;
    }
    
    infile.close();
    outfile.close();
    return 0;

}
