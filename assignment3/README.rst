=================================
 Computer Architecture 2014/2015
=================================

---------------
 Assignment 3
---------------

:Date: October 14th 2014
:Deadline: November 19th 2014, 23:59

.. section-numbering::

Overview
~~~~~~~~

The purpose of assignment 3 is to implement branch predictors.  A
branch predictor is an optimization to a processor pipeline that
attempts to minimize the amount of pipeline flushes upon taken
branches, by predicting early (at the fetch or decode stage) whether a
branch will be taken.
Contraints:

- Hardware is fixed: you cannot use dynamically sized resources in
  your branch predictor. You can make the number of resources
  initially configurable, but not variable after your branch predictor
  starts.

- The provided files ``framework.c`` and ``framework.h`` may not be modified.

- Your code has to be properly formatted and documented.

- You must submit a code archive and a report:

  - The archive you submit must be created with the ``make tarball``
    command provided by the enclosed ``Makefile``.

  - Reports must be in PDF format.

You can work in this assignment in groups of 2.

Trace files
~~~~~~~~~~~

Your branch predictors will be tested using *trace files*. A trace file
is a list of branches performed by a test program ran within a
processor simulation (like MGSim).

The format of a trace file is a sequence of number pairs, one pair per
input line. The first number in each pair is the program counter of a
branch; the second number is 1 or 0 to indicate whether the branch was
actually taken or not in the simulated program.

You can build your own trace files using your simulator from
assignment 2, but a few examples are provided as well.

The framework program in ``framework.c`` then reads this trace, then
provides repeatedly only the first column (the PC) to your own branch
predictor. Your branch predictor must answer with a prediction (taken
or not taken), and the framework then compares your prediction with
the actual taken value in the trace file. How often your predictor
"guessed right" determines the *accuracy* of your algorithm, which is
subsequently reported by the framework program.

Programming assignment
~~~~~~~~~~~~~~~~~~~~~~

Your programming assignment is to "fill the blanks" in the file
``predictors.c``. You can use the following steps to perform the assignment:

1. get to know the framework: compile the files as-is without changes,
   run them, then read the source code. Explain in your report in one
   paragraph (1/4 A4 page) how the framework works in a general way.

2. Implement the following simple branch preditor  in ``assignment_1_simple``:

   .. image:: simple.png
      :width: 50%

   For this your program only needs 2 boolean variables to keep the history.

3. Implement the algorithm GAg from the following article in ``assignment_2_GAg``:

     Tse-Yu Yeh and Yale N. Patt. *A comparison of dynamic branch
     predictors that use two levels of branch history.* In Proc 20th
     Annual International Symposium on Computer Architecture, ISCA
     ’93, pages 257–266, New York, NY, USA, 1993. ACM.

   Write a section in your report on this branch predictor: how you
   have implemented this, what are the advantages and disadvantages of
   this branch predictor, etc. The number of history elements are
   provided by the -k option.

4. Optionally, implement the algorithm SAs from the previous article
   in ``assignment_3_SAs``.  Again, write a section in your report on
   this branch predictor.

5. Optionally, implement your own algorithm in
   ``assignment_4_your_own``. Again, write a section in your report on
   this branch predictor.

Grading
~~~~~~~

- 1 points if you have submitted a code archive and report that demonstrates
  you have used and tested the framework successfully.

- +3 points if your implementation of the "simple" branch predictor is correct.

- +3 points if your implementation of the GAg algorithm is correct.

- +2 points if your implementation of SAs is correct.

- +1 point if you have implemented your own branch predictor(s) and
  documented them appropriately in your report.
