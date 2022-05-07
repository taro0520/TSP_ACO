#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include "aco.h"


int main(int argc, char** argv)
{
    // ./main [#runs] [#iteration] [#ants] [#citynumber] [#alpha] [#beta] [#p] [#q] [#filename]
    int runs=stoi(argv[1]);
    int iterations=stoi(argv[2]);
    int ants=stoi(argv[3]);
    int citynumber=stoi(argv[4]);
    int alpha=stoi(argv[5]);
    int beta=stoi(argv[6]);
    double p=stod(argv[7]);
    int q=stoi(argv[8]);
    ifstream filename(argv[9]);

    if(filename.is_open())
    {
        int temp;
        vector<ACO::city>City;
        City.resize(citynumber);
        for(int i=0;i<citynumber;i++)
            filename>>temp>>City[i].x>>City[i].y;

        ACO acoMachine(runs,iterations,ants,citynumber,City,alpha,beta,p,q);
        acoMachine.run();
    }
    return 0;
}