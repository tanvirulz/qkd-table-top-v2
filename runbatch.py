import os
from os import walk
input_directory = "./swabian/20200803_swabian_highres_highcount"
coincidence_window = 1000 #pico-seconds


work_directory = "03Aug_new"

log_file_name = "result_" + work_directory+"_cw"+str(coincidence_window)+"ps.csv"

input_files = []
for (dirpath, dirnames, filenames) in walk(input_directory):
    input_files.extend(filenames)
    break

os.system("mkdir -p "+work_directory)

print(input_directory)
print(input_files)

fp = open(work_directory+"/"+log_file_name,"w")
#print(work_directory+log_file_name)
fp.write("input_filename, alice_singles_rate, bob_singles_rate, coincidence_window(ps), coincidence_count_rate, sifted_key_length, num_error, QBER, hv_count,ad_count,alice_efficiency(%), bob_effeciency(%),duration(s)\n")
fp.close()
  
i = 0
for file in input_files:
    print (len(input_files)-i, "files to go")
    i+=1
    #./run.sh ./swabian/20200714_Swabian_Timestamp/data_2 4_1uW0dB.1.ttbin 14july0db 
    #os.system( "print '"+file+",'>> input_directory+"/"+log_file_name")
    os.system("./run.sh "+input_directory+" "+file+" "+work_directory+" "+log_file_name+" "+str(coincidence_window)+" "+"runbatch")
    print (file,"Done")
    
