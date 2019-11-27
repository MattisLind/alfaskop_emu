# Disks

The software disks are originally dumped ina format called InterMedia for Windows. It wasn't to difficult to figure out how to extract the raw 
data from the disks. The small shell script does the job pretty well. 

Then the next task is to understand the filesystem layout. The alfaskopS41Dump.c program is a horrid little program that extract all files and
also lists all directories. While dumping files it will create the corresponding directories so the same structure i achived.

