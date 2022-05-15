#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<int> max_weight(vector<int> containers,int capacity){  
    
    int weight = 0;
    int container = 0;
    vector<int> result;
    
    sort(containers.begin(),containers.end(),greater<int>());
    
    while(weight <= capacity && container < containers.size()){
        
        if(weight+containers.at(container)<=capacity){
            result.push_back(containers.at(container));
            weight += containers.at(container);
        }

        container++;
    }

    return result;
}

vector<int> max_containers(vector<int> containers,int capacity){
    
    int weight = 0;
    int container = 0;
    vector<int> result;
    
    sort(containers.begin(),containers.end());
    
    while(weight <= capacity && container < containers.size()){
        result.push_back(containers.at(container));
        weight += containers.at(container);
        container++;
    }

    return result;
}

int main(){

    int capacity;
    vector<int> containers;
    vector<int> mcontainers,mweight;

    mcontainers = max_containers(containers,capacity);
    mweight = max_weight(containers,capacity);

    cout<<"Max containers: "<<endl;
    for(auto it=mcontainers.begin();it!=mcontainers.end();it++){
        cout<<(*it)<<" ";
    }

    cout<<endl;
    cout<<"Max weight: "<<endl;
    for(auto it=mweight.begin();it!=mweight.end();it++){
        cout<<(*it)<<" ";
    }
    cout<<endl;

    return 0;
}