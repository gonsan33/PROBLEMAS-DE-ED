#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <deque>
using namespace std; 

void resuelveCaso() {
	int n, m, t; 
	cin >> n >> m >> t; 
	deque<int> dq(1,m); //el primer par lleva el tiempo que tardan en reproducirse, el segundo el tiempo desde la última vez que se reprodujeron
	
	for (int i = 0; i < t; ++i) {
		stack<int> st; 
		while (i != 0 && i % dq.front() == 0) {//se tiene que reproducir
			st.push(n); 
			dq.pop_front(); 
		}
		int nuevos = st.size(); 
		stack<int> auxiliar; 
		while (!dq.empty() && dq.back() > st.top()) {
			auxiliar.push(dq.back()); 
			dq.pop_back(); 
		}
		while()
	}
}


int main() {
	int n; 
	cin >> n; 
	for (int i = 0; i < n; ++i) resuelveCaso(); 
	return 0; 
}