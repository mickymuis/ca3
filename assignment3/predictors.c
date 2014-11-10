
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "predictors.h"
#include "framework.h"

/* Random prediction */
void random_predictor() {
    /* Variable to store the prediction you predict for this branch. */
    bool prediction = false;

    /* Variable to store the the address of the branch. */
    uint32_t addr = 0;
    
    /* 
     * Variable to store the actual branch result 
     * (obtained from the predictor library)
     */
    bool actual = false;

    /* 
     * Prediction loop, until tracefile is empty.
     */
    while (predictor_getState() != DONE) {

        /* Get the next branch address from the state machine. */
        if (predictor_getNextBranch(&addr) != 0) {
            fprintf(stderr, "ERROR: \"predictor_getNextBranch()\" called in "\
                   "a state it shouldn't be called!\n");
        }

        /* Do a random prediction */
        prediction = rand() & 1;

        /* 
         * Feed the prediction to the state machine, and get the actual
         * result back.
         */
        if (predictor_predict(prediction, &actual) != 0) {
            fprintf(stderr, "ERROR: \"predictor_predict()\" called in "\
                    " a state it shouldn't be called\n");
        }
        
    }
}

/* Predict always true (taken) or false */
void always_x(bool p) {
    /* Variable to store the prediction you predict for this branch. */
    bool prediction = p;

    /* Variable to store the the address of the branch. */
    uint32_t addr = 0;
    
    /* 
     * Variable to store the actual branch result 
     * (obtained from the predictor library)
     */
    bool actual = false;

    /* 
     * Prediction loop, until tracefile is empty.
     */
    while (predictor_getState() != DONE) {

        /* Get the next branch address from the state machine. */
        if (predictor_getNextBranch(&addr) != 0) {
            fprintf(stderr, "ERROR: \"predictor_getNextBranch()\" called in "\
                   "a state it shouldn't be called!\n");
        }

        /* Do a prediction */
        prediction = p;

        /* 
         * Feed the prediction to the state machine, and get the actual
         * result back.
         */
        if (predictor_predict(prediction, &actual) != 0) {
            fprintf(stderr, "ERROR: \"predictor_predict()\" called in "\
                    " a state it shouldn't be called\n");
        }
        
    }
}

/* Implement assignment 1 here */
void assignment_1_simple() {
  always_x(false);
}

/* Implement assignment 2 here */
void assignment_2_GAg(int history) {
  always_x(false);
}

/* Implement assignment 3 here */
void assignment_3_SAs(int history, int n_sets) {
  always_x(false);
}

/* Assignment 4: Change these parameters to your needs */
void assignment_4_your_own(int k, int n) {
  always_x(false);
}

/* Bonus: Change these parameters to your needs */
void bonus_1() {
  always_x(false);
}

/* Bonus: Change these parameters to your needs */
void bonus_2() {
  always_x(false);
}
