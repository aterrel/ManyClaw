#define __CL_ENABLE_EXCEPTIONS

#include "CL/cl.hpp"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>

#define BUFFER_SIZE 20

int A[BUFFER_SIZE];
int B[BUFFER_SIZE];
int C[BUFFER_SIZE];

const std::string kernel_filename("vecadd.cl");


int main(int argc, char** argv)
{
  // Initialize A, B, C
  for (int i = 0; i<BUFFER_SIZE; i++) {
    A[i] = i;
    B[i] = i*2;
    C[i] = 0;
  }

  try {
    std::vector<cl::Platform> platformList;
    cl::Platform::get(&platformList);
    cl_context_properties cprops[] = {CL_CONTEXT_PLATFORM,
        (cl_context_properties) (platformList[0])(),
        0};
    cl::Context context(CL_DEVICE_TYPE_CPU, cprops);
    std::vector<cl::Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();
    cl::CommandQueue queue(context, devices[0], 0);
    std::ifstream file(kernel_filename.c_str());
    std::string prog(std::istreambuf_iterator<char>(file),
                     (std::istreambuf_iterator<char>()));
    cl::Program::Sources sources(1, std::make_pair(prog.c_str(), 0));
    cl::Program program(context, sources);

    program.build(devices);

    cl::Buffer aBuffer = cl::Buffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
        BUFFER_SIZE*sizeof(int), (void *) &A[0]);
    cl::Buffer bBuffer = cl::Buffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
        BUFFER_SIZE*sizeof(int), (void *) &B[0]);
    cl::Buffer cBuffer = cl::Buffer(context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR,
        BUFFER_SIZE*sizeof(int), (void *) &C[0]);
    cl::Kernel kernel(program, "vadd");
    kernel.setArg(0, aBuffer);
    kernel.setArg(1, bBuffer);
    kernel.setArg(2, cBuffer);
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(BUFFER_SIZE),
        cl::NullRange);

    // Map cBuffer to host pointer. This enforces a sync with the host backing
    // space; remember we chose a GPU Device.
    int * output = (int *) queue.enqueueMapBuffer(cBuffer, CL_TRUE, //block
        CL_MAP_READ, 0, BUFFER_SIZE * sizeof(int));
    for (int i = 0; i < BUFFER_SIZE; i++) {
        std::cout << C[i] << " ";
    }
    std::cout << std::endl;
    queue.enqueueUnmapMemObject(cBuffer, (void *) output);
  } catch (cl::Error err) {
      std::cerr << "ERROR: " << err.what() << "(" << err.err() << ")" << std::endl;
      return EXIT_FAILURE;
  };
  return EXIT_SUCCESS;
}
