# Homework 2

This assignment consisted of two parts. Each part is a use of dynamic array structures, used for different purposes.

## Part 1: Convert a Bag to a Set

Here, the function `void bag2set(struct DynArr *da)` calls functions from `dynArray.c` to convert a bag to a set. A bag may have multiple instances of the same value, but a set has no repeated instances. For example, a bag `(1, 3, 3, 4, 4, 5)`, when converted to a set, would be `(1, 3, 4, 5)`. 
The datatype used in this implemention of a dynamic array is `double`.


## Part 2: Application of Stacks

Here, the dynamic array is implemented as a stack with the expected FILO structure. The compiled code accpets a string at runtime and determines if the string has a balanced set of brackets, parenthesis, and curly braces. However, it does not check if the expression is valid mathematically. Some examples of balacned strings are 

- "(a ++++ b)"
- "no brackets"
- "{(x + y), [x + (y + z)]}"
- "()()[][]{[{}]}"

Some examples of unbalanced strings are

- "[x + (y + z)" 
- "[x + (y + z])"
- "( [ ) ]"

The datatype in this implementation of a dynamic array is `char`.

### Assignment grade
100/100
