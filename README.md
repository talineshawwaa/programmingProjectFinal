# ChemiScript 🐛 🍀 🪷 🌍 ⛅️ 🥭 🏄‍♀️
As part of our final C Programming course project, we have decided to create a chemistry-based programming language. ChemiScript is designed with a different approach to learning how to code through the lens of basic chemistry. With a focus on Mendeleev's periodic table of elements and an emphasis on logic, this language makes use of key features of chemistry, yet allowing all new users to attempt it. The purpose of our language is to implement key features of basic chemistry as a method of learning a programming language through a different lens. Indeed, users with a different, less technological background could then be drawn towards learning coding by implementing a different type of logic. Another key aspect of our language is its simplicity. The logic we used to create it relies on both previous knowledge of the characteristics of elements of the periodic table, but not to the extent where one lacking chemical knowledge will be hindered by such. An instance of this would be beginning the code with the function H( ), relating to hydrogen, as it is the first element of the periodic table. Another example would be denoting vital function within the code through the function O( ), relating to oxygen, as we all know it is a crucial element for our survival (no previous chemical knowledge is needed to know such facts). All things considered, our target audience would be any user who wishes to learn a new programming language through a different, logical and simplified perspective.

## 🚀 Purpose
The purpose of ChemiScript is to blend the principles of chemistry with programming concepts, creating an educational tool that caters to users interested in both domains. By associating programming constructs with elements of the periodic table, users can grasp coding logic through familiar concepts. The language aims to attract users who seek an alternative and intuitive way to learn programming.

## 💻 Language Design

### Syntax
ChemiScript's syntax is inspired by the periodic table elements, representing reserved words in the code. For example, the element Hydrogen (H) initiates the program, and the choice of elements reflects their characteristics in the language. This design encourages users to associate programming elements with their chemical counterparts, fostering a logic-based, intuitive learning experience. Throughout our code, we have made us of ~ 20 core, known elements to be employed as various functions by the user.

Here are the elements used!

- Hydrogen (H): Initiates the program and is found in the beginning of the program, in the same way hydrogen is the first element on the periodic table.
- Carbon (C): Shows a link between certain parts of a code and connecting different parts of the code, and it is similar to linking two diefs in the C language, especially since carbon is the most versatile element and forms the most links between compounds.
- Neon (Ne): Highlights crucial parts of the code for enhanced visibility, drawing inspiration from neon's use in standout lighting.
- Gold (Au): Represents constants in the system, especially since gold is an extremely hard solid and is found and use in specific ways, in the same way constants are used in a code.
- Mercury (Hg): Used for dynamic lists and changing values, resembling mercury's liquid state at room temperature.
- Iron (Fe): Functions similarly to a struct, organizing variables under one name, inspired by iron's structural prominence.
- Silicon (Si): Used for data handling, copying, appending, and inverting, reflecting silicon's versatile properties.
- Tungsten (W): Handles data formatting, demonstrating robustness and durability similar to tungsten.
- Zinc (Zn): Can simulate an exit/break mechanism in the code
- Phosphorus (P): This element will be used for file handling, creating new files, appending existing one and has no ability to delete anything. This element is chosen because it is relatively  stable.
- Copper (C): Receive the input and store it in a variable (chlorine). This is because copper is usually used in alloying mixtures, in the same way in our code it is going to be used with other elements.
- Fluorine (F): Represents reactivity and is used to change data types, akin to fluorine's high reactivity.
- Krypton (Kr): Represents hidden or dormant functionality in the code, activated under certain conditions.
- Oxygen (O): Shows essential elements in the code The program could not run without the main aspects working in “O” mode. Call on oxy at the end of a code block in order to run the code. 
- Potassium (K): This is going to be the basic print function of the code. Potassium was chosen because when performing flame tests with potassium, you instantly see a lilac colour, in the same way print instantly prints a statement.
- Francium (Fr): Will be used to display errors and warnings in the code. As francium is the most radioactive element and can be very harmful, in the same way errors can be harmful to the code.
- Calcium (Ca): In the same way calcium is essential for bone growth and is essential for overall enhancement of human health. Comments are main component of a code so that it can highlight important parts of a code and show how the code can be enhanced and grow.

### Key Components
Aside from elements, we implemented key components of a programming languages, namely `conditional statements`, `loops`, `data types` and `libraries`.

__Conditional Statements__

Conditional statements represent two possibilities, whether a condition occurs or not, in the same way in any chemical reaction there are three possible outcomes, a reaction occurs, a reaction does not occur or intermediate reactions occurs before the final one. In our program, the conditional statement will be in terms of a reaction.

1. _React_

   Because in any chemical reaction the first thought a person has is when combining elements or placing them under certain conditions, will it react? In the same way a person always wants their first
   condition to be successful in a code, the first conditional statement will be “react”
   
2. _Unreact_

   In any chemical reaction, the main alternative is that no reaction will take place between the elements or under those specific conditions. Using this logic, if the conditions of the react statement are
   not satisfied, we move on to the next statement, which is that these conditions are non-reactive, or not satisfied.
   
3. _Intermediate React_

   The third possibility is that there are multiple intermediate reactions that will take place before a final condition is satisfied for the reaction to be a success. This logic will be used to provide
   alternative conditions if the react statement’s conditions were not satisfied 


__Data Types__

In terms of int, void, double and float, our code bases this off of the atomic theory, including protons, electrons, neutrons and the cloud.

1. _Protons_

   These represents the integer values in our coding language, as integers are fixed with no floating points in the same way the number of protons are fixed in an atom
   
2. _Electrons_

   These represent the floating point precision values that take up less memory within the code, because even though they can be variable due to decimal places, they still have the least weight in an atom\
   
3. _Neutrons_

   These represent the double floating point precision values, there can be different number of neurons due to isotopes, and they form most of the weight in an atom, and double float values usually take up the most memory

4. _Cloud_

   In the same way the electron cloud is basically empty and most of it is empty space, the void has no output and just stores the main components of the function and can carry any output, in the same the electron cloud stores the component parts of an atom

__Libraries__

1. _Alkali_

   Will be the representative of the string library in ChemiScript. Alkali metals are known to be very radioactive and have a high tendency to change form as their atoms can easily lose one electron, reflecting its dynamic and interactive nature, in the same way a string library is designed for dynamic and interactive use of strings.

2. _Halogens_

   Will be the representatives of the random library. Halogens are the most reactive elements on the periodic table, and is known to be unpredictable in nature, and using it for the random library reflects the dynamic and random nature of this library and how the outcome is unpredictable.

3. _Nobles_

   Will be the representative of the standard input/output library. This is the main library that is standard in all codes and will not change no matter what, in the same way noble gases have a standard form that does not change.

4. _Transition elements_
   Will be the representative of the Math library because transition elements are known for their diverse properties (multiple oxidation levels, coloured complexes…), in the same way a math library can perform countless and diverse operations.

__Loops__

Our program has two types of loops; molecular and periodic

1. _Molecular_

   Molecular performs the same function as of the for loop in any other programming language because a molecule is a combination of elements put together to form something different, and molecules are formed in a specific order with a specific number of elements, in the same way a for loop is a group of conditions that carry out a specific command in a specific order for a specific amount of time. 

2. _Periodic_

   Periodic is similar to the while loop, first of all its name, such that within a while loop, actions are periodic, meaning that they happen within the same period of time, and all the elements within a period have similar energy levels, similar to a while loop where the block within the while loop are the same and do not change during the execution of the loop until the condition is achieved (same in a period when it reaches the end).


## 🤸‍♀️ Target Audience
ChemiScript is designed for any user interested in learning a new programming language from a different, logical, and simplified perspective. Whether you have a background in chemistry or not, ChemiScript provides an engaging platform for exploring coding concepts through the familiar lens of the periodic table elements. No prior knowledge needed :)

## 🧿 Gameplan
After planning the task, defining the language design/syntax and creating a general timeline, we created a general step-by-step of our execution. Considering we pre-defined our key components, our idea and the components to implement within ChemiScript, our next step was the lexer. However, it does not work alone! Indeed, programming languages are essentially a 3-step process, the first being the lexer, followed by the parser and the interpreter/compiler. After the key components are done, you must work on the semantics, which refer to the meaning or interpretation of the constructs within the language. It defines how the statements and expressions in a program should be executed or evaluated. Following the semantics, we had to ensure error handling within our language, and testing it ourselves by running some sample programs. Below, you will find a visual we created describing our general process.

<img width="965" alt="Screenshot 2023-12-08 at 03 29 45" src="https://github.com/talineshawwaa/programmingProject/assets/132683425/d6ccb1c1-0f32-4785-92a1-fa44b19e51d2">

## 🩻 Lexer
A lexer is a vital component in the compilation process of a programming language, as it. breaks down the code into a sequence of tokens to be processed by the compiler/interpreter. A token is understood as the smallest units of meaning such as keywords, identifiers, symbols. The lexer works through first scanning the code and noticing patterns, tokenization, (through pre-established rules), which then match to a type of token that will be generated. To develop our lexer, we firstly made a ‘lexer.h’ file, which is a header file that consists of the main elements of the lexer and it defines every possible token that will be needed to develop the actual lexer, such as the data structures for the tokens, functions for creating tokens, printing them, and freeing them, and similar functions were applied to the token list. The second file is ‘lexer.c’, which carried out the process of tokenization, it converted the tokens into string representation, matching of tokens, building the tokens to create a linked list of tokens and multiple other areas that contributed to forming the lexer.

** Our lexer is attached, please find the _lexer.c_ and _lexer.h_ files

In order to run the lexer, you will need to install a few things in the terminal:

`xcode-select --install` -> You can use the Xcode Command Line Tools, which include the GCC (GNU Compiler Collection) suite

`gcc --version` -> After the installation is complete, you can verify that GCC is installed by checking its version

`gcc lexer.c -o lexer` -> You may now run the code, careful to run the correct name of your file

`./lexer` -> You may then run the executable

## 🌳 Parser
In this step, you must develop a parser that builds an abstract syntax tree (AST) from the tokenized input, while usig a parsing technique (recursive descent parsing) to process the grammar defined.
The parser works with the lexer and the interpreter in order to read and output your inputted code in the language created. After the lexer has broken down the language into components, the parser takes these pieces and checks/compares them to the defined grammar of the language. The output of the parser is to create the output as a data structure called the abstract syntax tree. The parser was coded so that an AST is used in order to show the relationship between different constructs of the code. The constructs in this case are the tokens defined. Also, within the parser grammar rules were defined to traverse the tokens.

** Our parser is attached, please find the _parser.c_ and _parser.h_ files

In order to run the parser, after the lexer is complete, you must link the two in the terminal:

`gcc parser.c lexer.c -o parser` -> Compile your parser code using GCC, please replace "parser.c" and "lexer.c" with the actual names of your parser and lexer source files

`./parser` -> After successful compilation, you can run the generated executable

## 📇 Interpreter & Semantics
Designing and implementing the interpreter basically refers to the main process of creating the software part that will be responsible for running the code we write into the programming language. An interpreter takes a high-level code, and we use the Abstract Syntax Tree (AST) to represent it. What this means is that the AST will translate the high-level code into instructions that the machine can understand and be able to execute. The process is composed of different steps, to begin with, we should start with defining the execution semantics. In this step, there should be a clear and concise outline of how the language’s construct (nodes) should be executed into the program when it is run. In other words, here is an explanation of how our chemistry concepts relate to the actual operations. Its also crucial to understand and showcase how the language will interact with the libraries mentioned (ex. Input/output, maths, random…). The error handling will also be explained, which is basically how the interpreter will handle errors and will go over the specified exceptions. Next is implementation where the different variables are inputted and structured well into the program. It also consists of library functions, which implements the functions in regards to their chosen standard library. Testing, documentation and integration are the following steps, where we ensure that the program is run correctly, and the interpreter is tested with a number of different programs making sure that all issues are identified and fixed.

Within our interpreter portion, we have the `executor.h`, the `executor.c` and the `interpreter.c` file itself. Each of these serves a different and interdependent purpose. The executor is responsible for executing the parsed code, interpreting the parsed syntax tree or intermediate representation and performs the actions specified by the code. This involves traversing the parse tree, interpreting statements, and executing them. Then, the interpreter reads and executes the source code directly, without a separate compilation step. It interprets the code line by line or statement by statement. -- This would be in contrast to a compiler which must translate the program before excuting it.



## 🪭 How to Run
To run the entire code, ensure that all of them are compiled together, as follows:

`gcc -o chemiscript parser.c lexer.c executor.c interpreter.c`

Then execute using the code:

`./chemiscript sample.chem`

## 🧬 Sample Program

