# Homework 1

This assingment consisted of four C files with bits of skeleton code in each. Any function prototypes in the files were to stay as they were, but we were permitted to add functions as we needed. 

## Program 1

We wrote the function `int foo(int* a, int* b, int c)` meant to do the following:
- Increment `a`
- Decrement `b`
- Assign `(a - b)` to `c`
- Return the value of `c`

The main function had three integers declared, `x y z`, assigned to random integers in the range `[0, 10]`. They are printed, `foo()` is then called, and then they are printed again.

## Program 2

Here we were to write the following functions and call them in the order listed:
- `struct student * allocate()` which allocates memory for 10 students and returns the pointer.
- `void generate(struct student* students)` which generates random initials and scores for each student, then stores them in the `students` array.
- `void output(struct student* students)` which prints the initials and scores of all students
- `void summary(struct student* students)` which prints minimum, maximum, and average score of all students
- `void deallocate(struct student* students)` which frees the memory allocated to `students`.

## Program 3

In this program, we were to write the function `void sort(int* numbers, int n)` to sort an array of `n` integers in ascending order. In the `main` function:
- Declare an integer `n` and allocate an array for `n` integers. 
- Fill the array with random numbers.
- Print the contents of the array
- Pass `n` and the array to `sort()`
- Print the contents of the sorted array after `sort()` has been called. 

## Program 4

Here we used the `student` structure from `Program2.c` and the `sort()` function from `Program3.c` to sort an array first by first initial, with ties being broken by the second initial.

### Assignment Score

100/100

