#include <Iterators.h>  // FileReader
#include <TimeTagger.h> // struct Tag
#include <math.h>       // sqrt
#include <stdio.h>      // fopen, fread, fclose
#include <stdlib.h>     // malloc, calloc, free
#include <vector>
#include <stdint.h>


int main(int argc, char* argv[]) {
    // scope for reading the file

    // opening of the raw tag file
    //FileReader reader("./8thJuly/2.97mW_1.1.ttbin");
    if (argc <4){
        printf("rrswabian [inputdir] [inputefile] [existing output directory name]");
        exit(0);
    }
    char infile_name[256];
    //printf("here! \n");
    //FileReader reader("./swabian/20200714_Swabian_Timestamp/data_2/4_1uW10dB.1.ttbin");
    sprintf(infile_name,"%s/%s",argv[1],argv[2]);

    //printf ("input file : %s\n",infile_name);
    FileReader reader(infile_name);
    //exit(0);

   
    //folder = "./8thJuly"
    //file = '2.97mW_1.1.ttbin'
    // buffer for raw Time Tags
    std::vector<Tag> buffer;

    // initial state before the processing of all tags
    timestamp_t last_start_click = 0;

    // loop over all chunks of tags
    //char  alice_file_name[] = "./output/alice.out";
    //char  bob_file_name[] ="./output/bob.out";

    char  alice_file_name[256];// = "./output/alice.out";
    char  bob_file_name[256]; //="./output/bob.out";
    sprintf(alice_file_name,"%s/%s",argv[3],"alice.out");
    sprintf(bob_file_name,"%s/%s",argv[3],"bob.out");
    
    //printf("alice file: %s\n",alice_file_name);


    FILE * bob_outfile;
    FILE * alice_outfile;

    bob_outfile = fopen(bob_file_name,"wb");
    alice_outfile = fopen(alice_file_name,"wb");

    long long time;
    long long channel; 
    int acount=0;
    int bcount = 0;
    //printf("here! ");
    while (reader.hasData()) {

        // read one chunk of tags into the local buffer
        reader.getDataRaw(buffer);
        //printf("buffer size %ld\n",buffer.size());
        //break;

        for(Tag t : buffer){
            //printf("%d",t.channel);
            if (t.type != Tag::Type::TimeTag) {
                // on overflow, invalidate the last start click
                
                ;
            } else {
                //get my tags in local variables;

                time = t.time;
                //H V A D 
                //5 6 7 8
                if (t.channel==5) channel = 7;
                else if(t.channel == 6  ) channel = 8;
                else if (t.channel == 7) channel = 5;
                else if (t.channel == 8) channel = 6;
                else channel = t.channel; 

                /*
                // swap bob's A & D
                // 14th July data
                if (t.channel==7) channel = 8;
                else if(t.channel==8) channel = 7;
                else channel = t.channel;
                */
            }

            if (channel<=4){
                acount ++;
                time = (time<<4) | (1<<(channel-1));
                fwrite(&time,sizeof(long long),1,alice_outfile);
            }else{
                bcount ++;
                channel = channel - 4;
                time = (time<<4) | (1<<(channel-1));
                fwrite(&time,sizeof(long long),1,bob_outfile);
            }
        }
        fflush(alice_outfile);
        fflush(bob_outfile);
        //break;

    }

    fclose(alice_outfile);
    fclose(bob_outfile);
    //printf("\n\nacount = %d\nbcounr = %d\na+b = %d\n",acount,bcount,acount+bcount);
    return 0;
}

