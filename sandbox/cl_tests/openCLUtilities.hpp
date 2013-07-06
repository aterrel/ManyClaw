//  This file was retrieved from github.com/smistad/OpenCLUtilities
//  git commit: 6692e7f6168da764fb538888bdbc164e9958f0e1
//
//  Copyright 2011 Erik Smistad. All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without modification, are
//  permitted provided that the following conditions are met:
//
//     1. Redistributions of source code must retain the above copyright notice, this list of
//        conditions and the following disclaimer.
//
//     2. Redistributions in binary form must reproduce the above copyright notice, this list
//        of conditions and the following disclaimer in the documentation and/or other materials
//        provided with the distribution.
//
//  THIS SOFTWARE IS PROVIDED BY Erik Smistad ''AS IS'' AND ANY EXPRESS OR IMPLIED
//  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
//  FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> OR
//  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
//  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
//  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//  The views and conclusions contained in the software and documentation are those of the
//  authors and should not be interpreted as representing official policies, either expressed
//  or implied, of Erik Smistad.
//

#ifndef OPENCL_UTILITIES_H
#define OPENCL_UTILITIES_H

// ART: Using __NO_STD_VECTOR seems to break on my mac
//#define __NO_STD_VECTOR // Use cl::vector instead of STL version
#define __CL_ENABLE_EXCEPTIONS


#include <CL/cl.hpp>


#include <string>
#include <iostream>
#include <fstream>


enum cl_vendor {
    VENDOR_ANY,
    VENDOR_NVIDIA,
    VENDOR_AMD,
    VENDOR_INTEL
};

cl::Context createCLContextFromArguments(int argc, char ** argv);

cl::Context createCLContext(cl_device_type type = CL_DEVICE_TYPE_ALL, cl_vendor vendor = VENDOR_ANY);

cl::Platform getPlatform(cl_device_type = CL_DEVICE_TYPE_ALL, cl_vendor vendor = VENDOR_ANY); 

cl::Program buildProgramFromSource(cl::Context context, std::string filename, std::string buildOptions = "");

cl::Program buildProgramFromBinary(cl::Context context, std::string filename, std::string buildOptions = "");

char *getCLErrorString(cl_int err);

#endif
