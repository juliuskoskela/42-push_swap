# Push Swap

A Hive Helsinki (42 school) project to sort a stack of integers using
specialized commands.

## Commands

```
sa    // Swap first two values in stack a
sb    // Swap first two values in stack b
ss    // Swap first two values in both stacks
pa    // Push first value in b to the top of a
pb    // Push first value in a to the top of b
ra    // Rotate stack a
rb    // Rotate stack b
rr    // Rotate both stacks
rra   // Reverse rotate a
rrb   // Reverse rotate b
rrr   // Reverse rotate both stacks.
```

## Algorithm Description

The objective of the project is not to sort the stacks in the least amount of
time, but to do it in the least amount of commands (which is not necessarily the
same).

In order to optimise the instructions we can imagine the two stacks as rotating
wheels connected from the top. First we push all the values that are not already
sorted in stack a to stack b.  After that we use a sort of "pathfinding" method
to find the shortest amount of commands that takes either value from stack b to
it's correct placement in stack a. We also optimise for the combined
instructions so that we recognize when an option which might have more rotations
for each stack, but has less rotations when the rotations are combined is
chosen.

## Algorithm Performance

stack size: 100
full points: < 700
program average: 571

stack size 1000
full points: < 5500
program average: 5182

## Usage

```
make

// Create instructions

./build/push_swap "1 3 2"

// Run checker on input 1 3 2 and input commands manually
./build/checker "1 3 2"

// Run push swap in onput 1 3 2 and check correctens with checker.
./build/push_swap "1 3 2" | ./build/checker "1 3 2"

// Test performance with input size of 500 and take average of 100 runs.
bash test_perf.sh 500 100

```
