#ifndef __ACO_H__
#define __ACO_H__

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ACO
{
public:
    struct city{
        int x;
        int y;
    };
    ACO(int runs,int iteration,int ants,int citynumber,vector<city>City,int alpha,int beta,double p,int q);
    void run();
private:
    int mRuns;
    int mIterations;
    int mAnts;
    int mCitynumber;
    int mAlpha;
    int mBeta;
    double mP;
    int mQ;
    vector<city>mCity;
    void Initial(vector<vector<double>>&pheromone,vector<vector<double>>&n,vector<vector<int>>&path,vector<vector<double>>&dis);
    void ConstructAntSolutions(vector<vector<int>>&path,vector<vector<double>>pheromone,vector<vector<double>>n);
    void UpdatePheromones(vector<vector<double>>&pheromone,vector<vector<double>>dis,vector<vector<int>>path,vector<double>&Lk,vector<int>&best_path,double &MIN_Lk);
    double Distance(int x1,int y1,int x2,int y2);
    double Prob(vector<vector<double>>pheromone,vector<vector<double>>n,int alpha,int beta,int i,int j,vector<double>p);
    void CalculateLk(vector<vector<int>>path,vector<vector<double>>dis,vector<double>&Lk);
    bool FindAntPath(int pos1,int pos2,int ant,vector<vector<int>>path);
    void ShowCity(int size,vector<city>City);
    void ShowPath(vector<vector<int>>path);
};

#endif