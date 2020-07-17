#include <Iterators.h>  // FileReader
#include <TimeTagger.h> // struct Tag
#include <math.h>       // sqrt
#include <stdio.h>      // fopen, fread, fclose
#include <stdlib.h>     // malloc, calloc, free
#include <vector>
#include <stdint.h>


int main() {
    // scope for reading the file

    // opening of the raw tag file
    FileReader reader("./8thJuly/2.97mW_1.1.ttbin");
    //folder = "./8thJuly"
    //file = '2.97mW_1.1.ttbin'
    // buffer for raw Time Tags
    std::vector<Tag> buffer;

    // initial state before the processing of all tags
    timestamp_t last_start_click = 0;

    // loop over all chunks of tags
    char  alice_file_name[] = "alice.out";
    char  bob_file_name[] ="bob.out";
    FILE * bob_outfile;
    FILE * alice_outfile;

    bob_outfile = fopen(bob_file_name,"wb");
    alice_outfile = fopen(alice_file_name,"wb");

    long long time;
    long long channel; 
    int acount=0;
    int bcount = 0;
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
                // swap bob's H & V
                if (t.channel==5) channel = 6;
                else if(t.channel==6) channel = 5;
                else channel = t.channel;
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
    printf("\n\n acount = %d\nbcounr = %d\na+b = %d",acount,bcount,acount+bcount);
    return 0;
}
