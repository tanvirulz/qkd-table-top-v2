to compile type 

    make

to run on a single file type 

    make run 

to run on the whole batch of experiments type 

    make runbatch

You have to configure the runbatch.py file to direct to your batch directory. 
You will have to assign a work directory and the  name of the result csv file in the code. 

If you want to change the coincidence window you have to update the run.sh file line 27 
Line 8 and 14 corrects Alice and Bob s detector delays. The detector order is 
H V A D 
Change this if neecessary. 

SwabianCoincidence.ipynb is a jupyter notebook file that I use for calibrating detector delays. 


'readRawSwabian.cpp' requires the swabian timetagger software suit to be installed. 
Download the version compatible with your OS form here 

https://www.swabianinstruments.com/support/downloads/

On debian based Linux you can doubleclick the downloaded .deb file to initiate the installation. 
This will install the necessary C and Python libraries. 
