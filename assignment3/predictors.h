
#ifndef PREDICTORS_H
#define PREDICTORS_H

#include <stdbool.h>
#include <inttypes.h>

/* Simple types representing a queue of bits 
 *
 * MSB, least recently added bit | 000 ... 000 | most recently added bit, LSB
 */
typedef uint8_t  bitQueue8_t;
typedef uint16_t bitQueue16_t;
typedef uint32_t bitQueue32_t;

typedef uint64_t bitQueue_t; // general oversized type.

/* Substitute for a 2 bit counter */
typedef uint8_t counter_t;

/* pushFront_*
 * Adds a bit to the head of the queue (the least significant bit)
 * Discards the most significant bit.
 */
void pushFront_8( bitQueue8_t*, bool );
void pushFront_16( bitQueue16_t*, bool );
void pushFront_32( bitQueue32_t*, bool );

/* pushFront() - pushes to a bit queue of up to 64 bits length
 * Adds a bit to the head of the queue (the least significant bit)
 * Discards the most significant bit.
 */
void pushFront( bitQueue_t*, uint16_t length, bool );


/* Random prediction */
void random_predictor();

/* Predict always true (taken) or false */
void always_x(bool p);

/* Implement assignment 1 here */
void assignment_1_simple();

/* Implement assignment 2 here */
void assignment_2_GAg(int history);

/* Implement assignment 4 here */
void assignment_3_SAs(int history, int n_sets);

/* Assignment 4: Change these parameters to your needs */
void assignment_4_your_own(int k, int n);

/* Bonus: Change these parameters to your needs */
void bonus_1(int history);

/* Bonus: Change these parameters to your needs */
void bonus_2();

#endif
