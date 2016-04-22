Manual:

There are three sections to the assignment:

1)CPU

2)Memory

3)Disk

If all the experiments have to be run together the following command has to be run

./full.sh

1)CPU has two parts

                The GIOPS and FLOPS calculation:

                                This is done by two programs. Iops.cpp and flops.cpp

                                This experiment can be run by running the following command

                                ./cpu_1.sh

                The 600 sample program:

                                This is done by two programs.iops_600.cpp and flops_600.cpp

                                This experiment can be run by running the following command

                                ./cpu_2.sh

2)Memory

                This experiment is run by the program memory.cpp

                This can be run by the following command

                ./memory.sh

3)Disk

                This experiment is run by the program disk.cpp

                This can be run by the following command

                ./disk.sh

Every program can be run after compiling the program using the command

g++ -std=c++11 –pthread <filename>

and this can be run by the command

./a.out
