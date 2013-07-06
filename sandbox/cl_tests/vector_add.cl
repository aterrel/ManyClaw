__kernel void
vadd(__global int * a, __global int * b, __global int *c)
{
    size_t i = get_global_id(0);
    c[i] = a[i] + b[i];
}