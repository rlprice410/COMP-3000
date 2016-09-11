
// Name:			Robert Price
// Auburn UserID:		rlp0018
// Filename:			hw2.cpp
// Development Environment: 	nano, g++, Linux
// Compile:			g++ hw2.cpp -o hw2
// Sample Usage: 		./hw2


#include <iostream>
#include <cmath>
using namespace std;


int main() {

	// Variables
	float amount_to_kill = 0;	
	float weight_mouse = 0;
	float weight_dieter = 0;
	const double PERCENT = 0.001;
	int num_soda = 0;	

	
	// Input
	cout << "What is the amount of artificial sweetener needed to kill a mouse: ";
	cin >> amount_to_kill;

	cout << "What is the weight of the mouse: ";
	cin >> weight_mouse;

	cout << "What is the weight of the dieter: ";
	cin >> weight_dieter;


	// Calculations
	num_soda = (1/PERCENT) * amount_to_kill * (weight_dieter / weight_mouse);
	

	// Output
	cout << "You can drink " << num_soda << " diet sodas without dying as a result." << endl;


	return 0;


}
