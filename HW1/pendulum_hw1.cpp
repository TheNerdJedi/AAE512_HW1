#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;

const double gR = 1;	// ratio of acceleration due to gravity and length

struct Point	// object to store variables
{
	double t;
	double u2;
	double u1;
};

void EulerCromerStep(

	Point& p,
	double dt)
{
	double t =p.t, u2 = p.u2, u1 = p.u1;

	// Apply Euler-Cromer algorithm
	u1 -= -gR * sin(u2) * dt;
	u2 += u1 * dt;
	t += dt;

	p.t = t, p.u2 = u2, p.u1 = u1;
}

void simulate(
	void method(Point&, double),
	double tMax,
	double dt,
	string fileName)
{
	// initialize
	Point p;
	p.t = 0;
	p.u2 = 1;
	p.u1 = 0;
	ofstream file(fileName.c_str());

	// algorithm loop 
	while (p.t <= tMax){
		method(p, dt);
		file << p.t << '\t' << p.u2 << '\t' << p.u1 << '\n';
	}

	// finalize
	cout << "Trajectory data in file" << fileName << endl;
	file.close();
}


int main() {
	cout << "Simulation of Simple Pendulum using Euler\n"
		<< "--------------------------------------------------------\n";
	double tMax, dt;
	cout << "Enter time step dt (s): ";
	cin >> dt;
	cout << "Enter integration time t_max: ";
	cin >> tMax;
		
	cout << "Running simulation using Euler-Cromer method" << endl;
	simulate(EulerCromerStep, tMax, dt, "euler-cromer.txt");

	return EXIT_SUCCESS;
}
