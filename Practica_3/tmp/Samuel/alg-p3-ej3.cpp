#include<iostream>
#include <fstream>
#include<vector>
#include<cmath>
#include<algorithm>

using namespace std;

struct Point{
    double x;
    double y;
};

int nearest_point(vector<int> v,vector<int> candidates){

    int pos_min;
    int min = 300000000;

    for (int i=0; i < v.size();++i){ 
        if(v.at(i) != 0 && min>v.at(i) && (find(candidates.begin(),candidates.end(),i)==candidates.end())){
            min=v.at(i);
            pos_min = i;
        }
    }
    return pos_min;
}
    
vector<int> tsp_near_neighbor(vector<vector<int>> v){

    vector<int> candidates,result;
    int size = v.at(0).size();
    int index;
    int i=0;
    
    candidates.push_back(i);
    while(candidates.size() < size){
        index = nearest_point(v.at(i),candidates);
        candidates.push_back(index);
        i=index;
    }

    return candidates;
}

vector<vector<int>> distance(vector<Point> p){

    vector<Point>::iterator it,it1;
    vector<vector<int>> matrix;
    vector<Point> copy = p;


    for (it=p.begin();it!=p.end();++it){
        vector<int> vector;
        for (it1=copy.begin();it1!=copy.end();++it1){   
            double d = sqrt(pow((*it1).x-(*it).x,2) + pow((*it1).y-(*it).y,2));
            int dist = trunc(d);
            vector.push_back(dist);
        }
        matrix.push_back(vector);
    }
    return matrix;
}

void toString(vector<vector<int>> matrix){
    for (auto it=matrix.begin();it!=matrix.end();++it){
        for (int i=0;i<matrix.size();++i){   
            cout<<(*it).at(i)<<"  ";
        }
        cout<<endl;
    }
}

void toString(vector<int> v){
    for (auto it=v.begin();it!=v.end();++it){
        cout<<(*it)<<"  ";
    }
}

int main(int argc,char *argv[]){

    char cadena[128];
    int dimension;
    vector<Point> p,copy;

    ifstream fe("../GeneradorTSP/ulysses16.tsp");
    fe >> cadena;
    fe >> cadena;
    dimension=stoi(cadena);

    cout<<"Dimensión: "<<dimension<<endl;

    int i = 0;
    int pos = 0;
    while (!fe.eof()){
        fe >> cadena;
        if(i%3 != 0){
            Point point;
            if(i%3 == 1){
                point.x=stod(cadena);
            }

            if(i%3 == 2){
                point.y=stod(cadena);
                p.push_back(point);
            }
        }
        else{
            pos++;
        }
        i++;
    }

    fe.close();

    vector<vector<int>> matrix=distance(p);

    cout<<"Matriz: "<<endl;
    toString(matrix);

    vector<int> v;
    v=tsp_near_neighbor(matrix);
    cout<<endl<<endl;
    cout<<"Vector resultante para TSP: "<<endl;
    toString(v);
    cout<<endl<<endl;

    return 0;
}