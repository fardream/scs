#ifndef CONES_H_GUARD
#define CONES_H_GUARD

#ifdef __cplusplus
extern "C" {
#endif

#include "glbopts.h"
#include "scs.h"
#include "scs_blas.h"

/* private data to help cone projection step */
struct SCS_CONE_WORK {
/*
 * cone_boundaries will contain array of indices of rows of A corresponding to
 * cone boundaries, boundaries[0] is starting index for cones of size larger
 * than 1
 */
  scs_int cone_boundaries_len;
  scs_int * cone_boundaries; 
#ifdef USE_LAPACK
  /* workspace for eigenvector decompositions: */
  scs_float *Xs, *Z, *e, *work;
  blas_int *iwork, lwork, liwork;
#endif
};

ScsConeWork *SCS(init_cone)(const ScsCone *k);
char *SCS(get_cone_header)(const ScsCone *k);
scs_int SCS(validate_cones)(const ScsData *d, const ScsCone *k);

/* pass in iter to control how accurate the cone projection
 with iteration, set iter < 0 for exact projection, warm_start contains guess
 of solution, can be SCS_NULL*/
scs_int SCS(proj_dual_cone)(scs_float *x, const ScsCone *k, ScsConeWork *c,
                            const scs_float *warm_start, ScsScaling *scal,
                            scs_int iter);
void SCS(finish_cone)(ScsConeWork *c);

#ifdef __cplusplus
}
#endif
#endif
