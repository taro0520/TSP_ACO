#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct City{
    int x;
    int y;
};
int main(int argc, char** argv)
{
    int n=stoi(argv[1]);
    ifstream filename(argv[2]);
    ifstream filename2(argv[3]);
    ofstream filename3(argv[4]);
    vector<City>city;
    vector<int>path(n,0);
    if(filename.is_open())
    {
        int temp;
        city.resize(n);
        for(int i=0;i<n;i++)
            filename>>temp>>city[i].x>>city[i].y;
    }
    filename.close();
    if(filename2.is_open())
    {
        for(int i=0;i<n;i++)
            filename2>>path[i];
    }
    filename2.close();

    for(int i=0;i<n;i++)
        filename3<<i<<" "<<city[path[i]].x<<" "<<city[path[i]].y<<endl;
    filename3<<n<<" "<<city[path[0]].x<<" "<<city[path[0]].y<<endl;

    return 0;
}