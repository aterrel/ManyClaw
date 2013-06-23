#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <vector>
#include <cmath>
#include <numeric>

typedef double real;

struct rp_grid_params
{
  int num_ghost;
  int num_eqn;
  int num_aux;
  int num_waves;
};

typedef void (*set_bc_t)(real* q, real* aux, const int nx, const int ny,
                               const int num_ghost, const int num_eqn);

typedef void (*rp_t)(const real* q_left, const real* q_right,
                  const real* aux_left, const real* aux_right,
                  const void* aux_global,
                     real* amdq, real* apdq, real* wave, real* s);

typedef void (*rp_step_t)(const real* q, const real* aux,
                          const int nx, const int ny, real* amdq,  real* apdq,
                          real* wave, real* wave_speeds);

typedef void (*updater_t)(real* q, const real* aux, const int nx, const int ny,
                                   const real* amdq, const real* apdq,
                                   const real* wave, const real* wave_speeds,
                                   const int num_ghost, const int num_eqn,
                                   const real dtdx);

template <typename Vector>
void randomize_vector(Vector& v)
{
  // generate numbers in [0,1) deterministically
  real seed = 0.123456789;

  for(unsigned int i = 0; i < v.size(); i++)
  {
    seed = (314159.26535 * seed);
    seed = seed - floor(seed);
    v[i] = seed;
  }
}

template <unsigned nx, unsigned ny, unsigned num_ghosts, unsigned num_eqns>
struct FieldIndexer
{
	inline int idx(int row, int col){return (col + row*(nx + 2*num_ghosts))*num_eqns;}

	inline int up(int row, int col){return (col + (row + 1)*(nx + 2*num_ghosts))*num_eqns;}

	inline int down(int row, int col){return (col + (row - 1)*(nx + 2*num_ghosts))*num_eqns;}

	inline int left(int row, int col){return (col - 1 + row*(nx + 2*num_ghosts))*num_eqns;}

	inline int right(int row, int col){return (col + 1 + row*(nx + 2*num_ghosts))*num_eqns;}

	inline int size(){return (nx + 2*num_ghosts)*(ny + 2*num_ghosts)*num_eqns;}
};

struct Grid
{
  // size info
  static const int dim=2;
  int num_cells[dim];
  double dx[dim];
  double lower[dim];
  double upper[dim];

  Grid(int nx, int ny);
};

struct State
{
  // size info
  int num_eqn;
  int num_aux;
  int num_ghost; // not strictly needed but makes life easier for now


  // State and auxilary variables
  std::vector<real> q;
  std::vector<real> aux;

  // Non-owned reference
  Grid &grid;

  State(Grid& grid, int num_eqn, int num_aux, int num_ghost);
  void randomize();

};

struct Solution
{
  // non-own references
  Grid& grid;
  State& state;
  double t;

  Solution(Grid& grid, State& state):
    grid(grid), state(state), t(0.0)
  {}

  void write(int frame, char *output_path);
};

struct Solver
{
  // Size info
  int num_ghost;
  int num_waves;

  // Interface data
  std::vector<real> amdq;
  std::vector<real> apdq;
  std::vector<real> waves;
  std::vector<real> wave_speeds;

  // Non-owned references
  Solution& solution;

  Solver(Solution& solution, int num_waves);

  void step(Solution& solution, double dt, set_bc_t set_bc, rp_step_t rp_step, updater_t update);
};



#endif // DATA_STRUCTURES_H
