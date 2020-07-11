#ifndef GLOBAL_DPU_H_
#define GLOBAL_DPU_H_

#include <perfcounter.h>
#include <defs.h>

// Dimension of the hypervectors
extern int32_t dimension;

// Number of acquisition's CHANNELS
extern int32_t channels;

// Dimension of the hypervectors after compression (dimension/32 rounded to the smallest integer)
extern int32_t bit_dim;

// Number of samples in each channel's dataset
extern int32_t number_of_input_samples;

// Dimension of the N-grams (models for N = 1 and N = 5 are contained in data.h)
extern int32_t n;

extern int32_t im_length;

extern uint32_t chAM[MAX_CHANNELS * (MAX_BIT_DIM + 1)];
extern uint32_t iM[MAX_IM_LENGTH * (MAX_BIT_DIM + 1)];
extern uint32_t aM_32[MAX_N * (MAX_BIT_DIM + 1)];

typedef struct in_buffer {
    int32_t *buffer;
    uint32_t buffer_size;
} in_buffer;

extern perfcounter_t compute_N_gram_cycles;
extern perfcounter_t associative_memory_cycles;
extern perfcounter_t bit_mod_cycles;

#endif
