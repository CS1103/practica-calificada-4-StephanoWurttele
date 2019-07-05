#include <iostream>
#include <vector>
#include <thread>

using namespace std;


template<typename A>
void maximo(vector<A> &vec,int &a,int &b,A &max){
	A maximo=vec[a];
	for (int i=a+1; i<b; i++){
		if(vec[i]>maximo){
			maximo=vec[i];
		}
	}
	max=maximo;
}



template<typename T>
void concurrente(vector<T> vec,int numhilos){
	int lim_inf[numhilos];
	int lim_sup[numhilos];
	vector<thread> hilos={};
	T maximos[numhilos];
	T max;
	for(int i=0;i<numhilos;i++){
		lim_inf[i]=(vec.size()*i)/numhilos;
		lim_sup[i]=(vec.size()*(i+1))/numhilos;
	}
	for(int i=0;i<numhilos;i++){
		T max;
		thread x(maximo<T>,ref(vec),ref(lim_inf[i]),ref(lim_sup[i]),ref(maximos[i]));
		hilos.push_back(move(x));
		maximos[i]=max;
	}
	for (int i=0;i<numhilos;i++){
		hilos[i].join();
	}
	max=maximos[0];
	for (int i=1; i<numhilos; i++){
		if(maximos[i]>max){
			max=maximos[i];
		}
	}
	cout<<"Maximo es "<<max<<endl;
}



int main() {
	int numhilos=4;
	vector<int> vec={1,2,3,1,3,4,5,1,4,3,2,8,9};
	concurrente(vec,numhilos); 	
	vector<float> vec2={13.1,2.13,3.1,1.1,43.1,64.1,53.1,11.1,4.1,3.1,2.1,8.1,9.1};
	concurrente(vec2,numhilos);
	vector<double> vec3={15.1,2.1,83.1,1.1,3.1,4.1,5.1,14.1,4.1,3.12,2.19,8.1,93.1};
	concurrente(vec3,numhilos);
	return 0;
}
