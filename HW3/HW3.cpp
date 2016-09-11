/*
Name:				Robert Price
Filename:			HW3.cpp
Development Enviornment:	Bash on Ubuntu on Windows, nano, g++
Compile Instructions:		g++ HW3.cpp -o HW3
Run Instructions:		./HW3
*/



#include <iostream>
#include <string>
#include <iomanip>
using namespace std;


// Table Template Function
template<typename T> void printElement(T t, const int& width = 12, const char& separator = ' ') {

	cout << left << fixed << setprecision(2) << setw(width) << setfill(separator) << t;

}


// Main Function
int main() {


	// Declare Variables
	float loan_amount = 0.0;
	float interest_rate = 0.0;
	float monthly_interest_rate;
	float monthly_payment = 0.0;
	float balance;
	float principal = 0;
	float monthly_interest;
	float total_interest = 0;
	int count = 0;


	// User Input
	cout << endl << endl;
	cout << "***************************************************************************" << endl;
	cout << "                                   User Input                              " << endl;
	cout << "***************************************************************************" << endl;

	cout << "Loan Amount: ";
	cin >> loan_amount;
	cout << "Interest Rate: ";
	cin >> interest_rate;
	cout << "Monthly Payment: ";
	cin >> monthly_payment;


	// Calculate Monthly Interest Rate
	monthly_interest_rate = interest_rate / 100 / 12;

	// Error Checking
	if(monthly_payment < loan_amount * monthly_interest_rate) {

		cout << "Error: Invalid payment amount." << endl;
		return -1;

	} else if(loan_amount <= 0) {

		cout << "Error: Loan amount is negative." << endl;
		return -1;

	} else if(interest_rate <= 0) {

		cout << "Error: Interest rate is negative." << endl;
		return -1;

	} else if(interest_rate > monthly_payment) {

		cout << "Error: Monthly payment is less than the interest rate." << endl;
		return -1;

	}


	// Calculation & Output
	cout << endl << endl;
	cout << "***************************************************************************" << endl;
	cout << "                             Amortization Table                            " << endl;
	cout << "***************************************************************************" << endl;

	printElement("Month");
	printElement("Balance", 14);
	printElement("Payment", 14);
	printElement("Rate (%)");
	printElement("Interest", 14);
	printElement("Principal", 14);
	cout << endl;

	printElement(count);
	printElement(loan_amount, 14);
	printElement("N/A", 14);
	printElement("N/A");
	printElement("N/A", 14);
	printElement("N/A", 14);
	cout << endl;

	balance = loan_amount;

	while(balance > 0) {

		if(balance * monthly_interest_rate + balance > monthly_payment) {

			++count;
			monthly_interest = balance * monthly_interest_rate;
			principal = monthly_payment - monthly_interest;
			balance = balance - principal;
			total_interest = total_interest + monthly_interest;

			printElement(count);
			printElement("$", 2);
			printElement(balance);
			printElement("$", 2);
			printElement(monthly_payment);
			printElement(monthly_interest_rate * 100);
			printElement("$", 2);
			printElement(monthly_interest);
			printElement("$", 2);
			printElement(principal);
			cout << endl;

		} else {

			++count;
			monthly_interest = balance * monthly_interest_rate;
			monthly_payment = monthly_interest + balance;
			principal = balance;
			balance = 0;
			total_interest = total_interest + monthly_interest;

			printElement(count);
			printElement("$", 2);
			printElement(balance);
			printElement("$", 2);
			printElement(monthly_payment);
			printElement(monthly_interest_rate * 100);
			printElement("$", 2);
			printElement(monthly_interest);
			printElement("$", 2);
			printElement(principal);
			cout << endl;

		}


	}

	cout << "***************************************************************************" << endl;
	cout << "It takes " << count << " months to pay off the loan" << endl;
	cout << "Total interest paid is: $" << total_interest << endl;

	return 0;

}
