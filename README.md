# Phase-Field-DynamicMeshing
 OpenFOAM based phasefield solver with dynamic meshing
 #You can compile the lib where ever you want. This is just an example:
 mkdir -p $FOAM_RUN/../OpenFOAM_extensions

 #Switch to this directory
 cd $FOAM_RUN/../OpenFOAM_extensions

 #Clone the repository
 git clone https://bitbucket.org/shor-ty/dynamicinterfacerefinefvmesh.git

 #Move to the new library folder
 cd dynamicinterfacerefinefvmesh

 #Checkout the openfoam version you need (5.x is compatible with any version after it)
 git checkout OpenFOAM-5.x

 #Go to the library source
 cd src/dynamicFvMesh

 #Compile the lib
 wmake libso
