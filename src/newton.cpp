#include<iostream>
#include<cmath>
using namespace std;

double E_uu(double u, double v){
	return exp(u) + exp(u*v)*v*v + 2;
}

double E_vv(double u, double v){
	return 4*exp(2*v) + exp(u*v)*u*u + 4;
}

double E_uv(double u, double v){
	return exp(u*v) + exp(u*v)*u*v - 2;
}

double E_u(double u, double v){
	return exp(u) + exp(u*v)*v + 2*u - 2*v - 3;
}

double E_v(double u, double v){
	return 2*exp(2*v) + u*exp(u*v) + 4*v - 2*u - 2;
}

int main(){
	double u=0, v=0;
	for(int i=0; i<50; ++i){
		double a = E_u(u,v), b = E_v(u,v);
		// newton
		/*
		double aa = E_uu(u,v), bb = E_vv(u,v), ab = E_uv(u,v);
		double delta_u = a*aa + b*ab;
		double delta_v = a*ab + b*bb;
		u = u - 0.01 * delta_u/2;
		v = v - 0.01 * delta_v/2;
		*/

		// stochastic gradient descent
		///*
		u = u - 0.01 * a;
		v = v - 0.01 * b;
		//*/

		cout << u << "," << v << endl;
	}
	return 0;
}
