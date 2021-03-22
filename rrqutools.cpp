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

int main(int argc, char * argv[]){

    char infile_name[256];
    char outfile_name[256];

    char inBuffer[BUFFER_SIZE];
    char outBuffer[BUFFER_SIZE];

    uint64_t raw_ts;
    int d; 
    uint64_t detector_bitmask;
    uint16_t raw_d; 
    uint64_t combined_ts; 

    int c1,c2,c3,c4,c104;
    c1=c2=c3=c4=c104=0;

        // scope for reading the file

    // opening of the raw tag file
    //FileReader reader("./8thJuly/2.97mW_1.1.ttbin");
    if (argc <4){
        printf("rrswabian [inputdir] [inputefile] [existing output directory name]\n");
        exit(0);
    }

    //printf("here! \n");
    //FileReader reader("./swabian/20200714_Swabian_Timestamp/data_2/4_1uW10dB.1.ttbin");
    sprintf(infile_name,"%s/%s",argv[1],argv[2]);

    sprintf(outfile_name,"%s/%s.out",argv[3],"alice");

    ifstream infile;
    ofstream outfile;


    infile.rdbuf()->pubsetbuf(inBuffer, BUFFER_SIZE);
    outfile.rdbuf()->pubsetbuf(outBuffer, BUFFER_SIZE);


    printf("%s\n%s\n",infile_name,outfile_name);
    infile.open(infile_name, ios::in|ios::binary);
    outfile.open(outfile_name,ios::out|ios::binary|ios::trunc);
    
    
    //skip 40 bytes header
    int count = 5;
    while( count-- ){
        infile.read(reinterpret_cast<char *>(&raw_ts),sizeof(raw_ts));
        if (infile.eof()) break; // EOF can only be detected after the final *failed* read attempt. 
        infile.read(reinterpret_cast<char *>(&raw_d),sizeof(raw_d));
        if (infile.eof()) break; // EOF can only be detected after the final *failed* read attempt. 
    }
    count = 0;
    while( 1 ){
        infile.read(reinterpret_cast<char *>(&raw_ts),sizeof(raw_ts));
        if (infile.eof()) break; // EOF can only be detected after the final *failed* read attempt. 
        infile.read(reinterpret_cast<char *>(&raw_d),sizeof(raw_d));
        if (infile.eof()) break; // EOF can only be detected after the final *failed* read attempt.
        d = (int) raw_d;
        
        /*if (d==104){
            continue;
        }*/
        //printf ("%d,\t%d\n", int(raw_ts),int(d));
        if (d==1) c1++;
        else if(d==2) c2++;
        else if (d==3) c3++;
        else if (d==4) c4++;
        else if (d==104) c104++;
        else {
            printf ("unknown value %d\n",int(d) );
            break;
        }
        
        //if (count >20) break; 
        detector_bitmask = 1;
        if (d<=4 && d >0){
            count++; 
            combined_ts = (raw_ts <<4)|(detector_bitmask<<(d-1));
            outfile.write(reinterpret_cast<char *>(&combined_ts),sizeof(combined_ts));
        }

    }
    printf("Total timestamp read %d\n",count);
    //printf("%d %d %d %d %d\n", c1,c2,c3,c4,c104);
    printf("ch    count\n");
    printf("1  -> %d \n2  -> %d \n3  -> %d \n4  -> %d \n104-> %d\n", c1,c2,c3,c4,c104);
    infile.close();
    outfile.close();

    return 0;
}
