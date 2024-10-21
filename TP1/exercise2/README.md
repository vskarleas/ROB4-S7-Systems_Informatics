# Question 1

We observe the following warning:

```bash
exemple.c:9:17: warning: format specifies type 'int *' but the argument has type 'int' [-Wformat]
    9 |     scanf("%d", n_max);
      |            ~~   ^~~~~
1 warning generated.
```

# Question 2

We modify the Makefile in order to debug. We add the options -g -O0 and we re-make so that we can launch the debuger on th eterminal: `lldb ./exemple`

> Please note that on my computer GDB is not available since it requires the x86_64 architecture. lldb is available instead but they completly similar

Here is the result once we start the execution of the program:

```bash
(lldb) run
Process 42510 launched: '/Users/vasilisskarleas/Library/Mobile Documents/com~apple~CloudDocs/Documents/University Sorbonne/4th year/S7/Computer systems/TP1/exercise2/exemple' (arm64)
calcule la somme des n premiers entiers, entrez n : 3
Process 42510 stopped
* thread #1, queue = 'com.apple.main-thread', stop reason = EXC_BAD_ACCESS (code=1, address=0x1)
    frame #0: 0x000000019a44dd74 libsystem_c.dylib`__svfscanf_l + 5576
libsystem_c.dylib`__svfscanf_l:
->  0x19a44dd74 <+5576>: str    w24, [x25]
    0x19a44dd78 <+5580>: b      0x19a44e14c    ; <+6560>
    0x19a44dd7c <+5584>: adrp   x8, 403384
    0x19a44dd80 <+5588>: add    x8, x8, #0xb28 ; libc_hooks
Target 0: (exemple) stopped.
```

We can see clearly that it is all about a BAD_ACESS, meaning that we are trying to access on a place in the memory where we shouldn't and simply the operating system stops the process with ID 42510.

Here is what the pile of the functions call looks like:

```bash
(lldb) bt 1
* thread #1, queue = 'com.apple.main-thread', stop reason = EXC_BAD_ACCESS (code=1, address=0x1)
    frame #0: 0x000000019a44dd74 libsystem_c.dylib`__svfscanf_l + 5576
(lldb) bt 2
* thread #1, queue = 'com.apple.main-thread', stop reason = EXC_BAD_ACCESS (code=1, address=0x1)
  * frame #0: 0x000000019a44dd74 libsystem_c.dylib`__svfscanf_l + 5576
    frame #1: 0x000000019a4a3290 libsystem_c.dylib`scanf + 96
(lldb) bt
* thread #1, queue = 'com.apple.main-thread', stop reason = EXC_BAD_ACCESS (code=1, address=0x1)
  * frame #0: 0x000000019a44dd74 libsystem_c.dylib`__svfscanf_l + 5576
    frame #1: 0x000000019a4a3290 libsystem_c.dylib`scanf + 96
    frame #2: 0x0000000100003ea8 exemple`somme_n + 52
    frame #3: 0x0000000100003f34 exemple`main + 28
    frame #4: 0x000000019a22c274 dyld`start + 2840
```

We already know that program violates the access to the memory but what else we can see. Well, the error occurs inside the `scanf` function, which is often related to incorrect use of pointers, uninitialized variables, or improper format specifiers.  The crash originates in a function called `somme_n` from the `exemple` executable, where `scanf` is being called.

This error, escalates up to the `main function` because `somme_n` leads to main function, that is correct if get a look to the code.

Now we can take a look to the code and we see that the scanf() functionw as trying to save to the addresse n_max (probably reserved from the system) instead of the addresse of the variable n_max. Here is the proposed fix:

```c
scanf("%d", &n_max); // line 9
```

# Question 3

We compile the programe exemple2.c without any problem. It is supposed to generate 100 doubles (aleartoires between 0 and 1). Well, we can say that probably it does this, however, it do not stop, so we can't verify if it works as expected and personally I believe that this is not the general purpose of the program (being on infinite loop).
