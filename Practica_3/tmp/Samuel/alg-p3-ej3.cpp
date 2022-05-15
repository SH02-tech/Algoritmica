#include<iostream>
#include <fstream>
#include<vector>
#include<cmath>

using namespace std;

int main(int argc,char *argv[]){


    struct Point{
        double x;
        double y;
    };

    char cadena[128];
    int dimension;
    vector<Point> p,copy;

    ifstream fe("../GeneradorTSP/ulysses16.tsp");
    fe >> cadena;
    fe >> cadena;
    dimension=stoi(cadena);

    cout<<dimension<<endl;

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

    copy = p;

    vector<vector<int>> matrix;

    vector<Point>::iterator it,it1;

    for (it=p.begin();it!=p.end();++it){
        vector<int> vector;
        for (it1=copy.begin();it1!=copy.end();++it1){   
            double d = sqrt(pow((*it1).x-(*it).x,2) + pow((*it1).y-(*it).y,2));
            int dist = trunc(d);
            vector.push_back(dist);
        }
        matrix.push_back(vector);
    }

    for (auto it=matrix.begin();it!=matrix.end();++it){
        for (int i=0;i<matrix.size();++i){   
            cout<<(*it).at(i)<<"  ";
        }
        cout<<endl;
    }



    return 0;
}