# CMOS Circuit SPICE Generator
The goal of this project is to implement a program that generates the part of a SPICE netlist (also  known as a SPICE deck) that describes a CMOS circuit realizing an arbitrary Boolean function provided by the user.

### A Brief Description of the project

SPICE (Simulation Program with Integrated Circuit Emphasis) is a widely-used online
tool in building electronic circuits. It is a great assist in describing the connections of
the components of these circuits for the users by displaying the SPICE netlist or the
SPICE deck.
In this project, I aim to implement a SPICE netlist generator using C++
programming language. First of all, I utilize the knowledge of how to implement
logic circuits using CMOS transistors in generating the SPICE netlist of the
implemented circuit. Thus, the program receives the input from the user as a boolean
expression and implements the boolean expression using CMOS transistors to finally
generate the SPICE netlist which describes the connections of the implemented
circuit.

### User Guide

##### How to use the program?
- After you run the program, you will be asked to enter the boolean expression that you want to implement using CMOS technology.
- Write the expression while putting in mind the input specifications guidelines.
- Press Enter.
- The Output will be displayed in a form of SPICE netlist describing the connections of the circuit in the following format:
| Mname  | drain | gate | source | body | type |

Examples:
| Mname  | drain | gate | source | body | type |
| -----  | ----- | ----- | ----- | ----- | ----- |
| M0 | A | a | VDD | VDD | PMOS |
| M1 | A | a | 0 | 0 |NMOS |

Note: the ground is always referred to as 0 in the output.

##### Input Specifications
An error message will appear if the user violated any of the following:

- It’s not allowed to enter any spaces in the input characters.
- The symbol of the output shouldn’t be used as one of the input symbols.
Example: y=y&x|z is an invalid input.
- Consistency is required throughout the entered expression!
Example: You cannot use ‘A’ and ‘a’ inside the same expression.
- The input must contain an ‘=’ sign; and at most one sign for each entered expression.
- The input must contain at least one logical operator (&, |, ‘ ) in order to be considered as a valid expression.
- While using parentheses, make sure each left parenthesis _i.e. ‘(’_ has a right parenthesis _i.e. ‘)’_ to have a valid expression.
Example: e=(a’&b|(c) is an invalid input.
- If you choose to use parentheses, avoid using the letters from u to z, either in capital or small case, in your expression.
- Variables should be made of single characters.
Example: y=aa&bb is an invalid input.


