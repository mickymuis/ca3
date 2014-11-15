=================================
CA Assignment  3 - BranchPredicion
=================================

Orson Peters, s....; Micky Faas, s1407937

*************
The Framework
*************

Files are organized in three sections: ``main.c``, which parses the commandline
arguments and fires up the correct predictor, ``framework.h/c`` which contain
the framework functions and ``predictors.h/c`` which contain only the specific
predictor functions.

The program cycle is as follows:
- ``main()`` calls ``predictor_setup()`` with the filename and the name of the
predictor from the commandline arguments. (The latter is only used for the
output of the statistics in the end)
- After all is set-up well, ``main()`` calls the predictor function of the
user's choice.
- The predictor function now uses the framework to fetch new branches and file
predictions. This is essentially where the mainloop takes place, so every
predictor-function has its own mainloop.
- Every iteration, the predictor calls ``predictor_getState()`` to check if
there are branches remaining
- If so, it calls ``predictor_getNextBranch()`` which returns the address of the
branch and advances the pseudo programcounter. This address may or may not be
used by the predictor
- Then ``predictor_predict()`` is called with the prediction. It returns the
actual outcome (taken or not taken) of the branch to the predictor function.
It also maintains the internal statistics.
- If no more branches are left, control is transfered back to ``main()`` which
calls one of the statistics-print functions and terminates the program.

**********************
The 'Simple' predictor
**********************

The Simple Predictor is implemented using a ``state`` enum which contains the
values ``TAKEN=0x1`` and ``CORRECT=0x01``. It can represent the four states of the
automaton by bitwise operations, e.g.: ``TAKEN | CORRECT``, ``TAKEN & ~CORRECT``,
``~TAKEN & CORRECT`` and ``0`` meaning respectively taken and correct, taken but
not correct, not taken and correct and not taken and not correct.

*****************
The GAg predictor
*****************

GAg is implemented using a simple bit-queue of k bits for the Branch History Register. 
A bit queue is of the type ``bitQueue_t`` which holds at most 64 bits. 
Only k bits are used. A bit (branch outcome) is added to the register 
using ``pushFront()`` by shifting all bits to the left towards the MSB by one step. 
The LSB is then set to the new bit (the head of the queue). 
Everything beyond the k-th bit is masked off.
The Pattern History Table is an array of 2^k elements and is indexed directly
by the integer value obtained by the bit-queue in the Branch History Register.
The PHT array holds elements that are 8 bit wide as this is the with closest to
2 bit for the counter. All counters are initialized on 2 (weak taken).

When a prediction is made, the following cycle happens:
- The address is fetched and discarded (global prediction)
- The counter at ``PHT[BHR]`` is fetched, if greather than 1, the prediction is
taken.
- After the prediction is made, ``PHT[BHR]`` is updated with the actual outcome.
- If is was taken, the counter is incremented, otherwise decremeneted
- Lastly, the outcome is added to the current pattern, the BHR by doing
``pushFront( &branchRegister, k, actual )``

The GAg is a fairly productive predictor. The hitrates range from 70% all the
way up to 94% (fib30, k=18). 

*****************
The SAs predictor
*****************

bla

**********
Finally...
**********
