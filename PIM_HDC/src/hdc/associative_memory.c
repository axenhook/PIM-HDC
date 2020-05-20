#include "associative_memory.h"
#include "aux_functions.h"

int associative_memory_32bit(uint32_t q_32[BIT_DIM + 1], uint32_t aM_32[][BIT_DIM + 1]) {
/*************************************************************************
    DESCRIPTION:  tests the accuracy based on input testing queries

    INPUTS:
        q_32        : query hypervector
        aM_32		: Trained associative memory
    OUTPUTS:
        class       : classification result
**************************************************************************/

    int sims[CLASSES] = {0};
    int class;

    //Computes Hamming Distances
    hamming_dist(q_32, aM_32, sims);

    //Classification with Hamming Metri
    class = max_dist_hamm(sims);

    return class;
}
