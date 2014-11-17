
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "predictors.h"
#include "framework.h"

#define PUSH_FRONT(q, b) (q << 1) | (b ? 0x1 : 0x0)

void pushFront_8( bitQueue8_t* q, bool b ) {
    (*q) = PUSH_FRONT((*q), b);
}

void pushFront_16( bitQueue16_t* q, bool b ) {
    (*q) = PUSH_FRONT((*q), b);
}

void pushFront_32( bitQueue32_t* q, bool b ) {
    (*q) = PUSH_FRONT((*q), b);
}

void pushFront( bitQueue_t* q, uint16_t length, bool b ) {
    (*q) = PUSH_FRONT((*q), b);
    (*q) &= (1 << length) -1;
  
    // This is push-back:
    // (*q) = ((*q) >> 1) | ((b ? 0x1 : 0x0) << (length -1));
}


// Random prediction.
void random_predictor() {
    // Variable to store the prediction you predict for this branch.
    bool prediction = false;

    // Variable to store the the address of the branch.
    uint32_t addr = 0;
    
    // Variable to store the actual branch result (obtained from the predictor library).
    bool actual = false;

    // Prediction loop, until tracefile is empty.
    while (predictor_getState() != DONE) {
        // Get the next branch address from the state machine.
        if (predictor_getNextBranch(&addr) != 0) {
            fprintf(stderr, "ERROR: \"predictor_getNextBranch()\" called in "\
                   "a state it shouldn't be called!\n");
        }

        // Do a random prediction.
        prediction = rand() & 1;

        // Feed the prediction to the state machine, and get the actual result back.
        if (predictor_predict(prediction, &actual) != 0) {
            fprintf(stderr, "ERROR: \"predictor_predict()\" called in "\
                    " a state it shouldn't be called\n");
        }
    }
}


// Predict always true (taken) or false.
void always_x(bool p) {
    // Variable to store the prediction you predict for this branch.
    bool prediction = p;

    // Variable to store the the address of the branch.
    uint32_t addr = 0;
    
    // Variable to store the actual branch result (obtained from the predictor library).
    bool actual = false;

    // Prediction loop, until tracefile is empty.
    while (predictor_getState() != DONE) {
        // Get the next branch address from the state machine.
        if (predictor_getNextBranch(&addr) != 0) {
            fprintf(stderr, "ERROR: \"predictor_getNextBranch()\" called in "\
                   "a state it shouldn't be called!\n");
        }

        // Do a prediction.
        prediction = p;

        // Feed the prediction to the state machine, and get the actual result back.
        if (predictor_predict(prediction, &actual) != 0) {
            fprintf(stderr, "ERROR: \"predictor_predict()\" called in "\
                    " a state it shouldn't be called\n");
        }
    }
}


void assignment_1_simple() { 
    enum {
        TAKEN = 0x01,
        NOT_TAKEN = 0x00, 
        CORRECT = 0x10
    } state = TAKEN | CORRECT;
       
    uint32_t addr = 0;
    bool actual, prediction;

    while (predictor_getState() != DONE) {
        if (predictor_getNextBranch(&addr)) {
            fprintf( stderr, "ERROR: couldn't get next branch.\n" );
        }
            
        prediction = (state & TAKEN);

        if (predictor_predict(prediction, &actual)) {
            fprintf( stderr, "ERROR: couldn't call predictor_predict( ).\n" );
        }

        if (prediction != actual) {
            if (!(state & CORRECT)) state = (~state) & TAKEN;
            else state &= ~CORRECT;
        } else state |= CORRECT;
    }
}


void assignment_2_GAg(int history) {
    // The Branch History Register.
    bitQueue_t branch_register = 0; // This is the 'G' in Gag.
             
    // The Pattern History Table.
    const int queue_length = history <= 64 ? history : 64;
    const uint64_t k = 1 << queue_length; // n bit queue length, table has 2^n entries.
    counter_t pattern_table[k]; // This is the 'g' in Gag.
    
    printf("GAg: Branch History Register length is %d bits, %" PRIu64 " PHT entries\n", 
            queue_length, k); // May go away :-)

    // Initialize the PHT.
    for (uint64_t i = 0; i < k; i++) pattern_table[i] = 2; // 'Weak taken'.
       
    uint32_t addr = 0;
    bool actual, prediction;

    while (predictor_getState() != DONE) {
        if (predictor_getNextBranch(&addr)) {
            fprintf(stderr, "ERROR: couldn't get next branch.\n");
        }
            
        // Use the most recent pattern in the Branch Register to lookup a prediction in the Pattern
        // Table.
        prediction = pattern_table[branch_register] > 2;
        if (predictor_predict( prediction, &actual)) {
            fprintf(stderr, "ERROR: couldn't call predictor_predict().\n");
        }
            
        // Update the Pattern History Table to reflect the outcome.
             if  (actual && (pattern_table[branch_register] < 3)) pattern_table[branch_register]++;
        else if (!actual && (pattern_table[branch_register] > 0)) pattern_table[branch_register]--;
            
        // Add the actual outcome to the current pattern in the Branch History Register.
        pushFront(&branch_register, queue_length, actual);
    }
}

// Implement assignment 3 here.
void assignment_3_SAs(int history, int n_sets) {
    // The Branch History Table.
    bitQueue_t branch_history_table[n_sets] = {0}; // This is the 'S' in Sas.
    
    // The Pattern History Tables.
    const int queue_length = history <= 64 ? history : 64;
    const uint64_t k = 1 << queue_length; // n bit queue length, table has 2^n entries.
    counter_t pattern_tables[k][n_sets]; // This is the 'g' in Gag.
    
    // Initialize the PHT.
    for (uint64_t i = 0; i < k; i++) pattern_table[i] = 2; // 'Weak taken'.

}

// Assignment 4: Change these parameters to your needs.
void assignment_4_your_own(int k, int n) {
    always_x(false);
}

// Bonus: Change these parameters to your needs.
void bonus_1() {
    always_x(false);
}

// Bonus: Change these parameters to your needs.
void bonus_2() {
    always_x(false);
}
