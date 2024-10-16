# Interpret

## Objectives
 
This lab has two parts: indirection with function pointers, and an interpreter for a stack-based instruction set.

C makes it possible to call functions through pointers to functions.    Function pointers have many uses.   In particular,
they are useful for a module to configure which procedures to call to handle events of various kinds.
In this way, the choice (binding) is deferred until runtime.   It allows modular composition of different
implementations of the module.

- Create function pointers for procedures and interfaces in C.
- Call functions with indirect calls through function pointers.
- Gain familiarity with the strange syntax for indirection through function pointers in C.

Stack-based computation is common in ISAs such as the Java Virtual Machine (JVM) *bytecode* \-\- Java's transportable intermediate representation.   The concepts of stack-based languages are fundamental to ISAs for
modern CPUs that support procedure calls.

- Gain familiarity with a stack-based language.
- Understand how the stack is used to transfer data (arguments/operands and results) among functional operators.
- See why stack-based code is compact and easy to interpret.

## Part 1: Function Pointers and Indirection

A *function pointer* is a typed pointer variable whose value is the
address of a function, i.e., the address of the location of the function's first instruction in the *text segment* of the address space.
The pointer's type incorporates the function's signature \-\- the types of its arguments and return value.   That enables the
compiler to type-check the call sites in the usual fashion.   The C syntax is tricky but it makes sense.

It is common for a C module to construct tables of pointers to functions
that handle requests or events of various types.   Callers of the module invoke a function using an indirect call through the
pointer in a selected table entry.   Such a table is often called a *dispatch table* or *virtual method table* or sometimes a
*handler vector*.   They are often used for *upcall* interfaces, in which the caller of some operation supplies handler routines
for callbacks to notify it of events that occur while the operation is executing.   Dispatch tables are everywhere in operating
systems.

Dispatch tables support interfaces with multiple interchangeable implementations.   That support is so important that it is a
defining concept of modern object-oriented languages.
For example, in Java, a subclass may override methods of a parent class or interface.
Code that holds a reference to an object may invoke the methods of the interface, independent of the object's subclass.
This concept is called *inclusion polymorphism*: from the caller's perspective, objects of all of the subclasses 
``look the same''.   Any calls to the interface execute the object's methods automatically.   If it looks like a duck and quacks
like a duck, then it's a duck.   Support for virtual method tables is a cornerstone of C++.

***Function pointers in C***

Look at the source file `indirect.c`.    It defines a function pointer called `add_ab`.   The type of `add_ab` is a pointer to a function that returns an
int and takes a single argument: a pointer to a `struct obj1`.   You can see that the definition `add_ab` uses `*` syntax indicating a pointer, enclosed
in parentheses to indicate that the pointer is to a function.   The rest of the declaration looks just like the argument signature for any function.

Then, down in `main()`, see how an ordinary assignment statement initializes the object field `add_ab`.   The rvalue of the assignment is simply the
name of a defined function whose signature matches the corresponding pointer type.   In C, an rvalue that is the name of a function evaluates to the
address of the function, i.e., a function pointer value.   There are two such assignments in `main()` of `indirect.c`.  Build and run the program to see that the two `printf` calls behave differently eventhough they look the same.

***What to do***

1. modify the structure OBJ1 to add four new function pointers to the structure.
```
set_a takes two arguments, a pointer to an object of type OBJ1 and an integer value.
set_b takes two arguments, a pointer to an object of type OBJ1 and an integer value.
set_c takes two arguments, a pointer to an object of type OBJ1 and an integer value.
sum_all takes one argument, a pointer to an object of type OBJ1, and returns an integer value.
```
2. Write implementations of the above four functions.   The `set` functions set the corresponding a, b, c field to the value.  The `sum_all` function returns the sum of the a,b,c fields.
3. Modify the main program to set these function pointers appropriately.
4. Test your program so that it ouputs the correct values (see below).

## Part 2: Interpret

Your task here is to complete the main body of `interpret.c` to interpret and execute
the instruction set of a simple stack machine to compute arithmetic expressions. 
The ISA is defined as an 8-bit stack architecture, where
each instruction is one byte with the following binary encoding:
```
| opcode | operand | 
``` 
the upper (most significant) 3 bits are the opcode and the lower (least significant) 5 bits give an operand.

The instruction set includes the following eight instructions (see isa.h for instruction definitions):
```
push val
pop
add
sub
neg
xor
mul
out
```

Note that push is the only instruction that has an operand.  The operand is a 5 bit *signed* integer. 

We provide you code to open a binary program file and read program instructions from the file.
You fill in your code to decode and execute each instruction.

To decode, first extract the opcode and operand from the instruction.
So be sure to sign extend the operand.   Note that a right shift on a signed type will
extend the sign bit for you.   Then write code to handle each opcode value.

The *out* instrution prints the current value
at the top of the stack.  The format for the output is as follows:
```
"TOS = %d\n" if the stack is not empty, print the value.
"TOS = empty\n" if the stack is empty.  
```
You must follow this format exactly.

The program ./asm is an assembler for this simple ISA that takes programs written in a simple
assembly as above (all lower case!) and produces a binary file of the instructions.  Several
small programs are provided (all the *.s files).  The make file includes the ability to assemble
these files for you. They are used for testing your interpreter.  You can assemble them yourself by running the ./asm command:
for example ./asm add.s would produce the file add.bin that can be used as input to your interepter.

Example output: 
```
./interpret add.bin
TOS = 3
TOS = 4
TOS = 7
```

This interpreter is in the spirit of the Java virtual machine (JVM) instruction set.
There is a lot more to the java virtual machine, but the idea of interpretation is key.  Java goes
a step further and includes something called dynamic compilation or just-in-time compliation that
translates its stack instructions to machine instructions, which in our class would be x86_64 instructions.

***Testing***

To test locally, run the following on the unix command line

```
python3 test_kit.py ALL
```

Or test individual components:

```
python3 test_kit.py TEST_SUITE_NAME [indirect or interpret]
```

What to submit:

- Add, commit, push: indirect.c and interpret.c, and statement.txt
- Submit to gradescope in the usual way

