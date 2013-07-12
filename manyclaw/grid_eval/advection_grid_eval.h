#ifndef ADVECTION_GRID_EVAL_H
#define ADVECTION_GRID_EVAL_H

#include "../common/data_structures.h"
#include "../riemann/advection_rp.h"

#include <tbb/parallel_for.h>
#include <tbb/blocked_range2d.h>


// Evaluates advection_rp via serial execution
void advection_rp_grid_eval_serial(const real* restrict q,
				   const real* restrict aux,
				   const int nx,
				   const int ny,
				   real* restrict amdq,
				   real* restrict apdq,
				   real* restrict wave,
				   real* restrict wave_speed);

// Evaluates advection_rp via parallel execution via openmp
void advection_rp_grid_eval_omp(const real* restrict q,
				const real* restrict aux,
				const int nx,
				const int ny,
				real* restrict amdq,
				real* restrict apdq,
				real* restrict wave,
				real* restrict wave_speed);

// Evaluates advection_rp via parallel execution via TBB
void advection_rp_grid_eval_tbb(const real* restrict q,
				const real* restrict aux,
				const int nx,
				const int ny,
				real* restrict amdq,
				real* restrict apdq,
				real* restrict wave,
				real* restrict wave_speed);


extern const char * advection_rp_grid_eval_names[];
extern const rp_grid_eval_t advection_rp_grid_evals[];
extern const size_t num_advection_rp_grid_eval_kernels;

#endif // ADVECTION_GRID_EVAL_H

