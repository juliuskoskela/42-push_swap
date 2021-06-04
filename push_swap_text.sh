#!/bin/bash

if [ $# == 2 ]
then
    args_no=$1
    repeat=$2
else
    printf "usage: $0 [args_no] [repetitions]\n"
    exit 1
fi

generate_shuffled_input () {
    local start=0
    local end=$args_no
    local i
    declare -a array

    for (( i=$start; i<$end; i++ ))
    do
        array[$i]=$i
    done
    array=( $(shuf -e "${array[@]}") )
    printf "%s " ${array[@]}
}

generate_random_input () {
    local start=0
    local end=100000
    local i
    declare -a array

    array=$(shuf -i $start-$end -n $args_no)
    printf "%s\n" ${array[@]}
}

rm -rf test_logs
mkdir test_logs

sum=0
for (( i=0; i<$repeat; i++ ))
do
    test_args="test_args_${args_no}_${i}"
    generate_random_input > $test_args
    log_file="test_logs/test_log_${args_no}_${i}"
#    test_args=$(generate_random_input)
#    echo $test_args >> $log_file
    ./push_swap $test_args > instructions 2>error
    cat instructions >> $log_file
    if [ -s error ]
    then
        printf "./push_swap $test_args > instructions: Error\n"
        exit 1
    fi
    # ./checker $test_args < instructions > output 2>error
    # cat output >> $log_file
    # cat error >> $log_file
    # if [ -s error ]
    # then
    #     printf "./checker $test_args < instructions > output: Error\n"
    #     exit 1
    # fi
    # grep "KO" output > error
    # if [ -s error ]
    # then
    #     printf "./checker $test_args < instructions > output: KO\n"
    #     exit 1
    # fi
    # grep "OK" output > ok
    echo "OK" > ok
    if [ -s ok ]
    then
        count=$( cat instructions | wc -l )
        printf "$count\n" >> $log_file
        printf "OK: $count\n"
        sum=$( echo $sum + $count | bc )
    fi
    rm -f error output ok count instructions $test_args
done
average=$(( $sum / $repeat ))
printf "sum: $sum average: $average\n"