#!/bin/bash

make > /dev/null

printf "\nMEMORY LEAKS\n\n"

valgrind --leak-check=full --show-leak-kinds=all ./build/push_swap "1 2 3"

printf "\nERROR MANAGEMENT\n\n"

printf "EVAL TEST: Non numeric parameters\n\n"
printf "./build/checker \"1 3 2a\"\n"
./build/checker "1 3 2a"

printf "\nEVAL TEST: Duplicate parameters\n\n"
printf "./build/checker \"1 2 2\"\n"
./build/checker "1 2 2"

printf "\nEVAL TEST: No parameters\n\n"
printf "./build/checker\n"
./build/checker

printf "\nEVAL TEST: Unkown command 1\n\n"
printf "printf \"kk\" | ./build/checker \"1 3 5\"\n"
printf "kk\n" | ./build/checker "1 3 5"

printf "\nEVAL TEST: Unkown command 2\n\n"
printf "printf \"   pb \" | ./build/checker \"1 3 5\"\n"
printf "kk\n" | ./build/checker "1 3 5"

printf "\nEVAL TEST: Push swap dentity 1\n\n"
printf "./build/push_swap 42\n"
./build/push_swap 42

printf "\nEVAL TEST: Push swap dentity 2\n\n"
printf "./build/push_swap 0 1 2 3\n"
./build/push_swap 0 1 2 3

printf "\nEVAL TEST: Push swap dentity 3\n\n"
printf "./build/push_swap 0 1 2 3 4 5 6 7 8 9\n"
./build/push_swap 0 1 2 3 4 5 6 7 8 9
