#include <iostream>
#include <fstream>
#include <string>
#include "Escultor3D.h"
using namespace std;

//CONSTRUTOR
Sculptor::Sculptor(int _nx, int _ny, int _nz)
{
    //dimensoes em x,y,z
    nx = _nx;
    ny = _ny;
    nz = _nz;

    //alocacao dinamica da matriz de voxels v
    v = new Voxel**[nx];
    v[0] = new Voxel*[nx*ny];
    v[0][0]= new Voxel[nx*ny*nz];
    v[1] = v[0] + ny*sizeof(Voxel**);
    for(int i=1; i<nz; i++){
        v[i] = v[i-1] + ny;
    }
    for(int i=1; i<nz*ny; i++){
        v[0][i] = v[0][i-1] + nx;
    }
    v[4][6][6].isOn = false;
}

//DESTRUTOR
Sculptor::~Sculptor(){
    delete [] v[0][0];
    delete [] v[0];
    delete [] v;
}

//Coloca uma cor
void  Sculptor :: setColor ( float r, float g, float b, float alpha)
{
    if (r>= 0.0 && r<= 1.0 ){
        this -> r=r;
    }
    if (g>= 0.0 && g <= 1.0 ){
        this -> g=g;
    }
    if (b>= 0.0 && b<= 1.0 ){
        this -> b=b;
    }
    if (g>= 0.0 && g <= 1.0 ){
        this -> g=g;
    }
    if (alpha>= 0.0 && alpha<= 1.0 ){

        a=alpha;
    }
}

//Coloca um voxel em uma posicao com uma determinada cor
void Sculptor::putVoxel(int x, int y, int z){
    v[x][y][z].isOn = true;
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;
}

//Apaga um voxel
void  Sculptor :: cutVoxel ( int x, int y, int z)
{
    v[x][y][z].isOn = false;
}

//Coloca uma caixa de voxels eu um determinado conjuto de pontos
void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    int i,j,k;
    for(i = x0; i <= x1; i++){
        for(j = y0; j <= y1; j++){
            for(k = z0; k <= z1; k++){
                putVoxel(i,j,k);
            }
        }
    }
}

//Apaga uma caixa de voxels em um determinado conjunto de pontos
void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    int i,j,k;
    for(i = x0; i <= x1; i++){
        for(j = y0; j <= y1; j++){
            for(k = z0; k <= z1; k++){
                cutVoxel(i,j,k);
            }
        }
    }
}

//coloca uma esfera em um raio e um centro determinados
void  Sculptor :: putSphere ( int xcenter, int ycenter, int zcenter, int radius) {
    for ( int i = 0 ; i <(2*xcenter); i ++)
    {
        for ( int j = 0 ; j < (2*ycenter); j ++)
        {
            for ( int k = 0 ; k < (2*zcenter); k ++)
            {
                if (((i-xcenter) * (i-xcenter) + (j-ycenter) * (j-ycenter) + (k-zcenter) * (k-zcenter)) <= (radius*radius))
                {
                   putVoxel(i,j,k);
                }
            }
        }
    }
}

//Apaga uma esfera em um raio e um centro determinados
void  Sculptor :: cutSphere ( int xcenter, int ycenter, int zcenter, int radius) {
    //utiliza a equacao da esfera
    for ( int i = 0 ; i <2*xcenter; i ++)
    {
        for ( int j = 0 ; j <2*ycenter; j ++)
        {
            for ( int k = 0 ; k <2*zcenter; k ++)
            {
                if (((i-xcenter) * (i-xcenter) + (j-ycenter) * (j-ycenter) + (k-zcenter) * (k-zcenter)) <= (radius * radius))
                {
                    cutVoxel(i,j,k);
                }
            }
        }
    }
}

//Coloca uma elipse em um raio e um centro determinados
void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    int i,j,k;
    float equacao_X,equacao_Y,equacao_Z;
    //utiliza a equacao da elipse para preencher os voxels
    for(i = (xcenter-rx); i <= (xcenter+rx); i++){
        for(j = (ycenter-ry); j <= (ycenter+ry); j++){
            for(k = (zcenter-rz); k <= (zcenter+rz); k++){
                if(rx != 0){equacao_X = ((i - xcenter)*(i - xcenter))/(rx*rx);}
                else{equacao_X = ((i - xcenter)*(i - xcenter));}
                if(ry != 0){equacao_Y = ((j - ycenter)*(j - ycenter))/(ry*ry);}
                else{equacao_Y = ((j - ycenter)*(j - ycenter));}
                if(rz != 0){equacao_Z = ((k - zcenter)*(k - zcenter))/(rz*rz);}
                else{equacao_Z = ((k - zcenter)*(k - zcenter));}
                float equacao_Ellipsoid = equacao_X + equacao_Y + equacao_Z;
                if(equacao_Ellipsoid <= 1.0){
                    putVoxel(i,j,k);
                }
            }
        }
    }
}

//Apaga uma elipse em um raio e um centro determinados
void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    int i,j,k;
    float equacao_X,equacao_Y,equacao_Z;
    for(i = (xcenter-rx); i <= (xcenter+rx); i++){
        for(j = (ycenter-ry); j <= (ycenter+ry); j++){
            for(k = (zcenter-rz); k <= (zcenter+rz); k++){
                if(rx != 0){equacao_X = ((i - xcenter)*(i - xcenter))/(rx*rx);}
                else{equacao_X = ((i - xcenter)*(i - xcenter));}
                if(ry != 0){equacao_Y = ((j - ycenter)*(j - ycenter))/(ry*ry);}
                else{equacao_Y = ((j - ycenter)*(j - ycenter));}
                if(rz != 0){equacao_Z = ((k - zcenter)*(k - zcenter))/(rz*rz);}
                else{equacao_Z = ((k - zcenter)*(k - zcenter));}
                float equacao_Ellipsoid = equacao_X + equacao_Y + equacao_Z;
                if(equacao_Ellipsoid <= 1.0){
                    cutVoxel(i,j,k);
                }
            }
        }
    }
}

//Cria um arquivo .off para ser exibido no MashLab
void Sculptor::writeOFF(char* filename){
    //Cria um arquivo vazio de acordo com o nome que o usuario escolheu
    string file = filename;//Coloca o ponteiro de char em uma string
    ofstream arquivo;
    arquivo.open(file+".off");

    if(!arquivo.good()){
        cout << "Falha ao criar arquivo\n";
    }
    else
        cout << "Arquivo criado!\n";
    //Aqui determinamos quantos voxels diferentes de zero possui o arquivo
    int cont = nx*ny*nz;
    for(int i = 0; i<nz; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nx; k++){
                if(v[i][j][k].isOn == false){
                    cont--;
                }
            }
        }
    }

    file += "OFF\n";//Adiciona off na string
    //obtem a quantidade total de vertices e faces por meio da multiplicacao
    //dos Voxels pelo numero de vertices e faces de um cubo (8 vertices e 6 faces)
    file += to_string(cont*8) + " " + to_string(cont*6) + " " + "0\n";
    //Para cada Voxel ele calcula a posicao de seus 8 vertices
    for(int i = 0; i < nz; i++){
        for(int j = 0; j < ny; j++){
            for(int k = 0; k < nx; k++){
                if(v[i][j][k].isOn == true){
                    file += to_string(k-0.5) + " " + to_string(j+0.5) + " " + to_string(i-0.5) + "\n";
                    file += to_string(k-0.5) + " " + to_string(j-0.5) + " " + to_string(i-0.5) + "\n";
                    file += to_string(k+0.5) + " " + to_string(j-0.5) + " " + to_string(i-0.5) + "\n";
                    file += to_string(k+0.5) + " " + to_string(j+0.5) + " " + to_string(i-0.5) + "\n";
                    file += to_string(k-0.5) + " " + to_string(j+0.5) + " " + to_string(i+0.5) + "\n";
                    file += to_string(k-0.5) + " " + to_string(j-0.5) + " " + to_string(i+0.5) + "\n";
                    file += to_string(k+0.5) + " " + to_string(j-0.5) + " " + to_string(i+0.5) + "\n";
                    file += to_string(k+0.5) + " " + to_string(j+0.5) + " " + to_string(i+0.5) + "\n";
                }
            }
        }
    }
    /*O primeiro numero da linha representa quantos vertices sao precisos para fazer
    * uma face, os numeros seguintes sao os vertices que formam uma face
    * por ultimo temos as propriedades de cor e transparencia.
    */
    cont = 0;
    for(int i = 0; i<nz; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nx; k++){
                if(v[i][j][k].isOn == true){
                    int pos = 8*cont;
                    file += "4 " + to_string(pos) + " " + to_string(pos+3) + " " + to_string(pos+2) + " " + to_string(pos+1) + " " + to_string(v[i][j][k].r) + " " + to_string(v[i][j][k].g) + " " + to_string(v[i][j][k].b) + " " + to_string(v[i][j][k].a) + "\n";
                    file += "4 " + to_string(pos+4) + " " + to_string(pos+5) + " " + to_string(pos+6) + " " + to_string(pos+7) + " " + to_string(v[i][j][k].r) + " " + to_string(v[i][j][k].g) + " " + to_string(v[i][j][k].b) + " " + to_string(v[i][j][k].a) + "\n";
                    file += "4 " + to_string(pos) + " " + to_string(pos+1) + " " + to_string(pos+5) + " " + to_string(pos+4) + " " + to_string(v[i][j][k].r) + " " + to_string(v[i][j][k].g) + " " + to_string(v[i][j][k].b) + " " + to_string(v[i][j][k].a) + "\n";
                    file += "4 " + to_string(pos) + " " + to_string(pos+4) + " " + to_string(pos+7) + " " + to_string(pos+3) + " " + to_string(v[i][j][k].r) + " " + to_string(v[i][j][k].g) + " " + to_string(v[i][j][k].b) + " " + to_string(v[i][j][k].a) + "\n";
                    file += "4 " + to_string(pos+3) + " " + to_string(pos+7) + " " + to_string(pos+6) + " " + to_string(pos+2) + " " + to_string(v[i][j][k].r) + " " + to_string(v[i][j][k].g) + " " + to_string(v[i][j][k].b) + " " + to_string(v[i][j][k].a) + "\n";
                    file += "4 " + to_string(pos+1) + " " + to_string(pos+2) + " " + to_string(pos+6) + " " + to_string(pos+5) + " " + to_string(v[i][j][k].r) + " " + to_string(v[i][j][k].g) + " " + to_string(v[i][j][k].b) + " " + to_string(v[i][j][k].a) + "\n";
                    cont++;
                }
            }
        }
    }
    arquivo << file; //coloca a string no arquivo
    arquivo.close(); //fecha o arquivo
}

int main(){
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
