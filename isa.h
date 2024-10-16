// the isa is defined as an 8-bit stack architecture
// bits are ordered | opcode | operand | with 3 bits for opcode and 5 for operand.


#define PUSH    0x0     // this is only instruction that takes an operand
#define POP     0x1     // pop the top value off the stack, decrement stack pointer
#define ADD     0x2     // removes the top two values of stack, adds them and places result on stack
#define SUB     0x3     // removes the top two values of stack, subtracts them and places result on stack
#define NEG     0x4     // negates the value on the top of stack
#define XOR     0x5     // removes the top two values of stack, xors them and places result on stack
#define MUL     0x6     // removes the top two values of stack, multiplies them and places result on stack
#define OUT     0x7     // print top of stack in format "TOS = %d\n", or say "TOS = empty\n" if it is

#define INST_MASK (7 << 5)
