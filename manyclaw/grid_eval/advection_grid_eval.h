#ifndef ADVECTION_GRID_EVAL_H
#define ADVECTION_GRID_EVAL_H

#include "../common/data_structures.h"
#include "../riemann/advection_rp.h"

#include <tbb/parallel_for.h>
#include <tbb/blocked_range2d.h>


// Evaluates advection_rp via serial execution
void advection_rp_grid_eval_serial(const real* q,
				   const real* aux,
				   const int nx,
				   const int ny,
				   real* amdq,
				   real* apdq,
				   real* wave,
				   real* wave_speed);

// Evaluates advection_rp via parallel execution via openmp
void advection_rp_grid_eval_omp(const real* q,
				const real* aux,
				const int nx,
				const int ny,
				real* amdq,
				real* apdq,
				real* wave,
				real* wave_speed);

// Evaluates advection_rp via parallel execution via TBB
void advection_rp_grid_eval_tbb(const real* q,
				const real* aux,
				const int nx,
				const int ny,
				real* amdq,
				real* apdq,
				real* wave,
				real* wave_speed);

#endif // ADVECTION_GRID_EVAL_H
