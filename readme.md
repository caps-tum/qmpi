# QMPI - The Next Generation Profiling Interface for MPI

This is the README for QMPI 0.1. 

If you have any questions please contact:

Bengisu Elis <bengisu.elis@tum.de> or
Dai Yang <d.yang@tum.de> 


## Prerequisites

- An MPI distribution, e.g. [OpenMPI](https://openmpi.org) 
- C compiler and MPICC compiler

## Notes
- Master branch is compatible with MPI version 3 and requires some MPI funcitons which are removed in MPI version 4
- The for MPI version 4 MPI-v4-development branch is under development and unstable at the moment.

## Building with Makefile

- Edit Makefile, edit CXXFLAGS and LDFLAGS according to the location of MPI sessions / MPI process sets
- Execute 
``` 
make 
```
- Our prototype creates the `libqmpi.a`, which is a static **PMPI** library intercepting **all** MPI functions in your application. This means that you have to load our library as a PMPI tool in order to use its functionality in your application. 
You application msut be linked with our QMPI library, which can be done with the following call. 
Note you do not need to link against the MPI library if you link to QMPI (**NO** `-lmpi`) !!!!!
```
-lqmpi
```

- Building the example application: 
```
cd sample
make
```

## Sample Tools

This repository contains two sample tools:
- [mpiP](https://github.com/LLNL/mpiP), which is a light-weight MPI Profiler developed by the Lawrence Livermore National Laboratory.
- very_simple_tool (aka. EmptyTool),  which intercepts every single MPI call but returns immediately, for evaluation purposes only. 

The tools can be built easily with make:
```
cd tools_example
cd mpiP_refactored
make
```
```
cd tools_example
cd very_simple_tool
make
```
## Execution
To test the existing tools, one must allow QMPI to load a given tool via environment variable "TOOLS". Assignment of the TOOLS variable must be made so that tool paths are seperated by a colon character. The ordering of the paths of the tools will also determine the ordering of the tools in the tool-chain.
Example:
```
export TOOLS=<path_to_qmpi_directory>/tool_examples/very_simple_tool/very_simple_tool.so:<path_to_qmpi_directory>/tool_examples/mpiP_refactored/libmpiP.so
```

## Context Seperation
QMPI allows multiple execution of the same tool file in a single tool-chain. In order to achieve this the path to the tool file should be added to the TOOLS environment varible multiple times as if one would add different tool paths. To make sure your tool supports context seperation feature there are extra requirements that must be satisfied by the tools.

### Tool Design for Context Seperation
The tool must declare and initialize a data structure that includes all of the global variables that affect the computations and output of the tool. By using "QMPI_Set_context" QMPI is enabled to allocate a memory and store the initialized data. This data can be reached via the void pointer returned by "QMPI_Get_context" function.
The refactored mpiP tool is an example of QMPI compatible tool with support of context seperation 

## Limitations
- Currently only support shared object (.so) based dynamic library tools
- Only supports linux system (and macOS), Windows is not supported. 


## Copyright

The QMPI interface is licensed under the BSD 3-clause license. 
You should consult the LICENSE file for further information. 

(C) 2019 Technical University of Munich, Chair of Computer Architecture and Parallel Systems. 


## Publications
Any academic work published with the content of this repository must cite the following paper as reference: 
- Bengisu Elis, Dai Yang, and Martin Schulz. 2019. QMPI: a next generation MPI profiling interface for modern HPC platforms. In Proceedings of the 26th European MPI Users' Group Meeting (EuroMPI '19), Torsten Hoefler and Jesper Larsson Träff (Eds.). ACM, New York, NY, USA, Article 4, 10 pages. DOI: https://doi.org/10.1145/3343211.3343215



## Disclaimer
THIS APPLICATION IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
