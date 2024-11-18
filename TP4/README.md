# TP4 (Shelly software)

## Structure of the program

We can find several files that come with the Shelly software. Here is the definition of teh different files:

1. commands.c : You will find the declaration of the builtin functions for the shell
2. logic.c : It includes all the detectors for different import operators such as "|" or ">". It includes also the main ways to execute commands in the following modes:
   * in background
   * default (waiting for child to be completed)
   * stdout
3. macros.h : different defined declarations
4. shell.c : The main program that calls the loop of the shell that is declared on logic.c
5. test.c : A simple file used for testing purposes
6. ui.c : ASCII colours declarations and some error messages declarations. It's everything related to User Interface.

## Installation

A bash file is provided for the automatic installation of the Shelly software. In order to execute the softawre please make sure that you have provided execution rights to this script.

```bash
cd TP4
chmod 777 shelly.sh
```

For the execution you need to perfom the following:

```bash
bash shelly.sh
```

## Treated functionalities

* [X] We can read a line in standard output and save it on memory. If needed it is capable to reallocate memory for that purpose
* [X] We can parse the line in order to receive an array of strings. This will alow us to execute the commands later.
* [X] We execute the commands in default mode
* [X] There are builtin commands. Those are the ones that have been implemented: "cd, help, exit, pwd, date, echo, cat, wc"
* [X] In order to call them, the list of pointer of functions that was quite interesting as implementation
* [X] Of course we have the commands execution with arguments in this shell implementation
* [X] Added functionality for the & operator
* [X] Tubes were applied according to the pricniple: left_of_the_operator => writes and right_of_the_operator => reads
* [X] stdout implemntation was added as well by using file descriptors.
* [ ] Bonus part was started to be treated however there were some segmntation fault issues when I was trying to seperate the semicolons, meaning to put the appropriate spaces before and after the ';' so that it is detcted as different argument and by extension extract the arguments between the ; operators.
