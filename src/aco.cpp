#include "../inc/aco.h"
#include <time.h>
#include <windows.h>
#include <cmath>
ACO::ACO(int runs,int iteration,int ants,int citynumber,vector<ACO::city>City,int alpha,int beta,double p,int q)
{
    this->mRuns=runs;
    this->mIterations=iteration;
    this->mAnts=ants;
    this->mCitynumber=citynumber;
    this->mCity=City;
    this->mAlpha=alpha;
    this->mBeta=beta;
    this->mP=p;
    this->mQ=q;

    unsigned seed;
    seed = (unsigned)time(NULL);
    srand(seed);
}
void ACO::Initial(vector<vector<double>>&pheromone,vector<vector<double>>&n,vector<vector<int>>&path,vector<vector<double>>&dis)
{
    vector<double>temp,dis_temp;
    vector<int>temp2;
    double dis_res;
    pheromone.clear();
    n.clear();
    path.clear();
    dis.clear();
    for(int i=0;i<this->mCitynumber;i++)
    {
        temp.clear();
        for(int j=0;j<this->mCitynumber;j++)
            temp.push_back(0.000001);
        pheromone.push_back(temp);
    }


    for(int i=0;i<this->mCitynumber;i++)
    {
        temp.clear();
        dis_temp.clear();
        for(int j=0;j<this->mCitynumber;j++)
            if(i!=j)
            {
                dis_res=Distance(this->mCity[i].x,this->mCity[i].y,this->mCity[j].x,this->mCity[j].y);
                temp.push_back((double)1/dis_res);
                dis_temp.push_back(dis_res);
            }
            else
            {
                temp.push_back(0);
                dis_temp.push_back(0);
            }
        n.push_back(temp);
        dis.push_back(dis_temp);
    }

    for(int i=0;i<this->mAnts;i++)
    {
        temp2.clear();
        for(int j=0;j<this->mCitynumber;j++)
            temp2.push_back(0);
        path.push_back(temp2);
    }
}
void ACO::ConstructAntSolutions(vector<vector<int>>&path,vector<vector<double>>pheromone,vector<vector<double>>n)
{
    vector<double>p(this->mCitynumber,0);
    vector<int>rnd_city(this->mCitynumber);
    int rnd=0;
    double rnd_d;
    int pos;
    double temp;
    for(int i=0;i<this->mCitynumber;i++)
        rnd_city[i]=i;
    for(int i=0;i<this->mCitynumber;i++)
    {
        rnd=rand()%this->mCitynumber;
        swap(rnd_city[rnd],rnd_city[i]);
    }
    for(int i=0;i<this->mAnts;i++)
    {
        pos=0;
        for(int k=0;k<this->mCitynumber;k++)
            p[k]=0;
        path[i][pos]=rnd_city[i];
        p[rnd_city[i]]=-1;
        while(1)
        {
            temp=0;
            for(int j=0;j<this->mCitynumber;j++)
            {
                if(p[j]!=-1)
                {
                    p[j]=Prob(pheromone,n,this->mAlpha,this->mBeta,path[i][pos],j,p);
                    temp+=p[j];
                }
            }
            rnd_d=(double)rand()/(RAND_MAX + temp);
            for(int k=0;k<this->mCitynumber;k++)
            {
                if(p[k]!=-1)
                {
                    if(rnd_d>=p[k])
                        rnd_d-=p[k];
                    else
                    {
                        p[k]=-1;
                        path[i][++pos]=k;
                        break;
                    }
                }
            }
            if(pos==this->mCitynumber-1)
                break;
        }
    }
}
void ACO::UpdatePheromones(vector<vector<double>>&pheromone,vector<vector<double>>dis,vector<vector<int>>path,vector<double>&Lk,vector<int>&best_path,double &MIN_Lk)
{
    double temp,dis_total;
    CalculateLk(path,dis,Lk);
    for(int i=0;i<this->mCitynumber;i++)
        for(int j=0;j<this->mCitynumber;j++)
            if(i!=j)
            {
                temp=(double)(1-this->mP)*pheromone[i][j];
                dis_total=0;
                for(int k=0;k<this->mAnts;k++)
                    if(FindAntPath(i,j,k,path))
                        dis_total+=(double)this->mQ/Lk[i];
                pheromone[i][j]=temp+dis_total;
            }
            else
                pheromone[i][j]=0;
    for(int i=0;i<this->mAnts;i++)
        if(Lk[i]<MIN_Lk)
        {
            best_path=path[i];
            MIN_Lk=Lk[i];
        }
}
double ACO::Distance(int x1,int y1,int x2,int y2)
{
    int x_,y_,total;
    x_=x2-x1;
    y_=y2-y1;
    total=x_*x_+y_*y_;
    return sqrt(total);
}
double ACO::Prob(vector<vector<double>>pheromone,vector<vector<double>>n,int alpha,int beta,int i,int j,vector<double>p)
{
    double temp1,temp2,probility;
    temp1=pow((pheromone[i][j]),alpha)*pow(n[i][j],beta);
    temp2=0;
    for(int k=0;k<this->mCitynumber;k++)
        if(p[k]!=-1)
            temp2+=pow((pheromone[i][k]),alpha)*pow(n[i][k],beta);
    probility=(double)temp1/temp2;
    return probility;
}
void ACO::CalculateLk(vector<vector<int>>path,vector<vector<double>>dis,vector<double>&Lk)
{
    for(int i=0;i<this->mAnts;i++)
    {
        Lk[i]=0;
        for(int j=0;j<this->mCitynumber-1;j++)
            Lk[i]+=dis[path[i][j]][path[i][j+1]];
        Lk[i]+=dis[path[i][0]][path[i][this->mCitynumber-1]];
    }
}
bool ACO::FindAntPath(int pos1,int pos2,int ant,vector<vector<int>>path)
{
    for(int j=0;j<this->mCitynumber-1;j++)
        if((path[ant][j]==pos1 && path[ant][j+1]==pos2)||(path[ant][j]==pos2 && path[ant][j+1]==pos1))
            return true;
    if((path[ant][0]==pos1 && path[ant][this->mCitynumber-1]==pos2)||(path[ant][this->mCitynumber-1]==pos2 && path[ant][0]==pos1))
        return true;
    return false;
}
void ACO::ShowCity(int size,vector<ACO::city>City)
{
    for(int i=0;i<size;i++)
        cout<<i<<" x="<<City[i].x<<" y="<<City[i].y<<endl;
}
void ACO::ShowPath(vector<vector<int>>path)
{
    for(int i=0;i<this->mAnts;i++)
    {
        cout<<i<<endl;
        for(int j=0;j<this->mCitynumber;j++)
            cout<<path[i][j]<<" ";
        cout<<endl;
    }
}
void ACO::run()
{
    int runs,iterations;
    runs=this->mRuns;
    iterations=this->mIterations;
    vector<vector<double>>pheromone;
    vector<vector<double>>dis;
    vector<vector<double>>n;
    vector<vector<int>>path;
    vector<double>Lk(this->mAnts,0.0);
    vector<int>best_path(this->mCitynumber,0);
    double MIN_Lk=INT_MAX;
    int temp;
    DWORD star_time = GetTickCount();

    while(runs--)
    {
        Initial(pheromone,n,path,dis);
        iterations=this->mIterations;
        while(iterations--)
        {
            ConstructAntSolutions(path,pheromone,n);
            UpdatePheromones(pheromone,dis,path,Lk,best_path,MIN_Lk);
        }
    }
    DWORD end_time = GetTickCount();
    temp=(end_time - star_time)/1000;

    cout<<"=====[Travelling Salesman Problem]====="<<endl;
    cout<<"#Algorithm:Ant Colony Optimization"<<endl;
    cout<<"#Runs:"<<this->mRuns<<endl;
    cout<<"#Iteration:"<<this->mIterations<<endl;
    cout<<"#Ants:"<<this->mAnts<<endl;
    cout<<"#Citynumber:"<<this->mCitynumber<<endl;
    cout<<"#Alpha:"<<this->mAlpha<<endl;
    cout<<"#Beta:"<<this->mBeta<<endl;
    cout<<"#P:"<<this->mP<<endl;
    cout<<"#Q:"<<this->mQ<<endl;
    cout<<"#Best Distance:"<<MIN_Lk<<endl;
    cout<<"#Best Path:"<<endl;
    for(int i=0;i<mCitynumber;i++)
        cout<<best_path[i]<<" ";
    cout<<endl;
    cout<<"#Cost Time:"<<temp<<"s"<<endl;
}