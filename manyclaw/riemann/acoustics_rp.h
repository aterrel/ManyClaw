#ifndef ACOUSTICS_RP_H
#define ACOUSTICS_RP_H

#include "../common/manyclaw_common.h"

const real BULK = 1.0;
const real RHO = 1.0;

struct acoustics_const_rp_aux_global_t
{
    // Bulk modules (k)
    real bulk;
    // Density
    real rho;
    // Impedence
    real c;  // = sqrt(bulk / rho);
    // Speed of sound
    real Z; // = c * rho;
};

static const acoustics_const_rp_aux_global_t acoustics_const_rp_aux_global_default = {1.0, 1.0, 1.0, 1.0};
static const rp_grid_params_t acoustics_const_rp_grid_params = {2, 3, 0, 2};

// Point-wise constant acoustics Riemann solver
inline
void acoustics_const_rp(const real* q_left, const real* q_right,
                        const real* aux_left, const real* aux_right,
                        const void* aux_global_void,
                        const int direction,
                        real* amdq, real* apdq, real *wave, real *s)
{

    const acoustics_const_rp_aux_global_t* aux_global = (acoustics_const_rp_aux_global_t*) aux_global_void;

    // Local physical constants
    real alpha[2],delta[2];
    const int num_eqn = acoustics_const_rp_grid_params.num_eqn;

    // Wave strengths
    delta[0] = q_right[0] - q_left[0];
    delta[1] = q_right[1] - q_left[1];
    alpha[0] = (-delta[0] + aux_global->Z * delta[1]) / (2.0 * aux_global->Z);
    alpha[1] = ( delta[1] + aux_global->Z * delta[1]) / (2.0 * aux_global->Z);

    // Wave speeds
    s[0] = -aux_global->c, s[1] = aux_global->c;

    // Set wave vectors
    wave[0 * num_eqn + 0] = -alpha[0] * aux_global->Z;
    wave[0 * num_eqn + 1] =  alpha[0];
    wave[0 * num_eqn + 2] =  0.0;

    wave[1 * num_eqn + 0] = alpha[1] * aux_global->Z;
    wave[1 * num_eqn + 1] = alpha[1];
    wave[1 * num_eqn + 2] = 0.0;

    // Grid edge fluctuations
    amdq[0] = s[0] * wave[0 * num_eqn + 0];
    amdq[1] = s[0] * wave[0 * num_eqn + 1];
    amdq[2] = s[0] * wave[0 * num_eqn + 2];  // This could just be set to zero

    apdq[0] = s[1] * wave[1 * num_eqn + 0];
    apdq[1] = s[1] * wave[1 * num_eqn + 1];
    apdq[2] = s[1] * wave[1 * num_eqn + 2];  // This could just be set to zero
}


struct acoustics_var_rp_aux_global_t
{
};

static const acoustics_var_rp_aux_global_t acoustics_var_rp_aux_global_default = {};
static const rp_grid_params_t acoustics_var_rp_grid_params = {2, 3, 2, 2};

// Point-wise constant acoustics Riemann solver
// aux_* = [rho,bulk]
inline
void acoustics_var_rp(const real* q_left, const real* q_right,
                      const real* aux_left, const real* aux_right,
                      const void* aux_global_void,
                      const int direction,
                      real* amdq, real* apdq, real *wave, real *s)
{
    const int num_eqn = acoustics_var_rp_grid_params.num_eqn;

    // Local physical constants
    real c_left = sqrt(aux_left[1] / aux_left[0]);
    real c_right = sqrt(aux_right[1] / aux_right[0]);
    real Z_left = c_left * aux_left[0];
    real Z_right = c_right * aux_right[0];

    // Wave strengths
    real delta[2],alpha[2];
    delta[0] = q_right[0] - q_left[0];
    delta[1] = q_left[1] - q_right[1];
    alpha[0] = (-delta[0] + Z_right * delta[1]) / (Z_right + Z_left);
    alpha[1] = ( delta[0] + Z_left * delta[1])  / (Z_right + Z_left);

    // Wave speeds
    s[0] = -c_left;
    s[1] =  c_right;

    // Set wave vectors
    wave[0 * num_eqn + 0] = -alpha[0] * Z_left;
    wave[0 * num_eqn + 1] = alpha[0];
    wave[0 * num_eqn + 2] = 0.0;

    wave[1 * num_eqn + 0] = alpha[1] * Z_right;
    wave[1 * num_eqn + 1] = alpha[1];
    wave[1 * num_eqn + 2] = 0.0;

    // Grid edge fluctuations
    amdq[0] = s[0] * wave[0 * num_eqn + 0];
    amdq[1] = s[0] * wave[0 * num_eqn + 1];
    amdq[2] = s[0] * wave[0 * num_eqn + 2];  // This could just be set to zero

    apdq[0] = s[1] * wave[1 * num_eqn + 0];
    apdq[1] = s[1] * wave[1 * num_eqn + 1];
    apdq[2] = s[1] * wave[1 * num_eqn + 2];  // This could just be set to zero
}

#endif // ACOUSTICS_RP_H
