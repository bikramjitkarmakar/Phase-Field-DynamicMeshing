/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    laplacianFoam

Description
    Solves a simple Laplace equation, e.g. for thermal diffusion in a solid.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
//#include "fvOptions.H"
#include "simpleControl.H"
#include "Random.H"
#include "dynamicFvMesh.H"
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    #include "setRootCase.H"

    #include "createTime.H"
    #include "createDynamicFvMesh.H"

    simpleControl simple(mesh);

    #include "createFields.H"

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< "\nCalculating temperature distribution\n" << endl;

   volVectorField q=dimx*fvc::grad(phi);
   volScalarField magq = 0.0*phi;
   volScalarField T = 0.0*phi + initial;
   volScalarField sumLHS = 0.0*phi;
   volVectorField q_4 = 0.0*q;
   volVectorField q_6 = 0.0*q;
   volScalarField ac_01 =0.0*phi;
   volVectorField dAdq01= phi*vector(0,0,0);
   volVectorField dadgradPhi=q*0.0;

    while (simple.loop(runTime))
    {
        Info<< "Time = " << runTime.timeName() << nl << endl;
       
          //  T = initial*(1/dimx)*mesh.C();    
            T = G*( (1/dimx)* mesh.C().component(vector::X) - v*runTime.value()) + initial; 
        
          while (simple.correctNonOrthogonal())
        {
           

          label curTimeIndex = mesh.time().timeIndex();

	for (int i=0; i<30; i++)
        {
		if(curTimeIndex == 0)
				{
                                    #include "preAlan.H"
                                }	
		
	}
                
                mesh.update();
                #include "alphaEqn.H"
		 


	}

	

    if (runTime.writeTime())
    {
      runTime.write();
    }
        Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
        runTime.write();
    }

    Info<< "End\n" << endl;

    return 0;
}
