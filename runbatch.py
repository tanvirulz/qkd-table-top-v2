import os
from os import walk
input_directory = "./swabian/20200714_Swabian_Timestamp/data"
log_file_name = "result_data.csv"
work_directory = "14july0db"
input_files = []
for (dirpath, dirnames, filenames) in walk(input_directory):
    input_files.extend(filenames)
    break

os.system("mkdir -p "+work_directory)

print(input_files)

fp = open(work_directory+"/"+log_file_name,"w")
#print(work_directory+log_file_name)
fp.write("input_filename, alice_singles, bob_singles, coincidence_window(ps), coincidence_count, sifted_key_length, num_error, QBER, hv_count,ad_count,alice_efficiency(%), bob_effeciency(%)\n")
fp.close()
  
i = 0
for file in input_files:
    i+=1
    #./run.sh ./swabian/20200714_Swabian_Timestamp/data_2 4_1uW0dB.1.ttbin 14july0db 
    #os.system( "print '"+file+",'>> input_directory+"/"+log_file_name")
    os.system("./run.sh "+input_directory+" "+file+" "+work_directory+" "+log_file_name)
    print (file,"Done")
    print (len(input_files)-i, "files to go")
