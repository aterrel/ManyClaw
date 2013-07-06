#include "openCLUtilities.hpp"

inline void checkErr(cl_int err, const char * name)
{
  if (err != CL_SUCCESS) {
    std::cerr << "ERROR: " << name
              << " (" << getCLErrorString(err) << ")"
              << std::endl;
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char** argv)
{
  cl_int err;
  cl::Context ctx = createCLContextFromArguments(argc, argv);

  char * outH = new char[128];
  cl::Buffer outCL(ctx, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR,
      128, outH, &err); checkErr(err, "Buffer::Buffer()");

  std::vector<cl::Device> devices;
  devices = ctx.getInfo<CL_CONTEXT_DEVICES>();
  checkErr(devices.size() > 0 ? CL_SUCCESS : -1, "devices.size() > 0");

  cl::Program prog = buildProgramFromSource(ctx, "hello_kernel.cl");
  cl::Kernel kernel(prog, "hello", &err); checkErr(err, "kernel");
  err = kernel.setArg(0, outCL);
  cl::CommandQueue queue(ctx, devices[0], 0, &err); checkErr(err, "queue");
  cl::Event event;
  err = queue.enqueueNDRangeKernel(kernel, cl::NullRange,
      cl::NDRange(128), cl::NDRange(1, 1), NULL, &event);
  checkErr(err, "enqueueNDRangeKernel");
  event.wait();

  err = queue.enqueueReadBuffer(outCL, CL_TRUE, 0, 128, outH);
  checkErr(err, "enqueueReadBuffer");
  std::cout <<outH;
  return EXIT_SUCCESS;
}
