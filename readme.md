# QMPI - The Next Generation Profiling Interface for MPI

This is the README for QMPI 0.1. 

If you have any questions please contact:

Bengisu Elis <bengisu.elis@tum.de> or
Dai Yang <d.yang@tum.de> 


## Prerequisites

- An MPI distribution, e.g. [OpenMPI](https://openmpi.org)
- C compiler and MPICC compiler

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
## Exection
To test the existing tools, one must allow QMPI to load a given tool via environment variable.
Example:
```
t.b.d.
```

## Limitations
- Currently only support shared object (.so) based dynamic library tools
- Only supports linux system (and macOS), Windows is not supported. 


## Copyright

The QMPI interface is licensed under the BSD 3-clause license. 
You should consult the LICENSE file for further information. 

(C) 2019 Technical University of Munich, Chair of Computer Architecture and Parallel Systems. 


## Citation
Any academic work published with the content of this repository must cite the following paper as reference: 
- Bengisu Elis, Dai Yang and Martin Schulz. QMPI: A Next Generation MPI Profiling Interface for Modern HPC Platforms. EuroMPI '19: Proceedings of the 26th European MPI Users' Groups Meeting. ACM, New York, NY, USA. 2019. Accepted for Publication.


## Disclaimer
THIS APPLICATION IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 