#include <iostream>
#include <fstream>
#include <string>
#include "Escultor3D.h"
using namespace std;
{
     char* documento = "Projeto01";
     Sculptor desenho(20,20,20);
     desenho.setColor(0.5,0,0,0.5);
     desenho.putVoxel(18,18,18);
     desenho.cutVoxel(0,0,0);
     desenho.setColor(0,0.5,0,0.5);
     desenho.putBox(0,8,0,8,0,8);
     desenho.cutBox(0,1,0,1,0,1);
     desenho.setColor(0,0,0.5,0.5);
     desenho.putSphere(10,10,10,5);
     desenho.cutSphere(9,9,9,4);
     desenho.setColor(0.5,0,0.5,0.5);
     desenho.putEllipsoid(15,15,15,2,4,1);
     desenho.cutEllipsoid(16,16,16,1,1,1);
     desenho.writeOFF(documento);
     return 0;
 }