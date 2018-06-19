Hi, here is what you need to know in the ML part.

Basically, you have 5 files : a cpp for the model creation, the prediction, the training (only for bayes) and the extra functions (with its header), and in the end the makefile to make the compilation easier.

You don't need to read that paragraph if you won't use the make file
To create a model, make sure that you selected the same one on each cpp file, and then go to the makefile and change the line
class = xxxxx/ (line 9) to whatever you want. Then go to your terminal and tip make buildclass and you re good to go. A new folder will be created 
with the name you specified in the makefile and it will contain the executables. If you need to change everything, just change it in the cpp file concerned and to recompile it, you only need to use make with the file concerned (for exemple make predict for the prediction)




enjoy 


one last thing: you will probably need to change the variable 'nom' in each file to load the right csv file. 
