#include <iostream>
#include <string>
using namespace std;

int main()
{
	int startOd = 0;
	int endOd = 0;
	int days = 0;
	int month = 0;
	string name = "";
	string lux = "";
	cout << "Odometer at Start: ";
	cin >> startOd;
	cout << "Odometer at End: ";
	cin >> endOd;
	cout << "Rental Days: ";
	cin >> days;
	cout << "Customer Name: ";
	cin.ignore(10000, '\n');
	getline(cin, name);
	cout << "Luxury Car? (y/n): ";
	getline(cin, lux);
	cout << "Starting Month (1=Jan, 2=Feb, etc.): ";
	cin >> month;
	cout << "---"<< endl;
	if (startOd < 0) {
		cout << "The starting odometer reading must not be negative." << endl;
	}
	else if (endOd < startOd) {
		cout << "The ending odometer reading must be at least as large as the starting reading." << endl;
	}
	else if (days<=0) {
		cout << "The number of rental days must be positive." << endl;
	}
	else if (name=="") {
		cout << "You must enter a customer name." << endl;
	}
	else if (!(lux=="y" || lux=="n")) {
		cout << "You must enter y or n." << endl;
	}
	else if (!(month<=12 && month>=1)) {
		cout << "The month number must be in the range 1 through 12." << endl;
	}
	else{
		double rate = 0;
		if (lux == "y") {
			rate = 75;
		}
		else {
			rate = 45;
		}
		double mileCost = 0;
		double dist = endOd - startOd;
		if (dist <= 100) {
			mileCost += 0.33 * dist;
		}
		else if (dist <= 600) {
			mileCost += 33;
			if (month == 12 || month <= 3) {
				mileCost += (dist - 100) * 0.33;
			}
			else {
				mileCost += (dist - 100) * 0.27;
			}
		}
		else {
			mileCost += 33;
			if (month == 12 || month <= 3) {
				mileCost += 500 * 0.33;
			}
			else {
				mileCost += 500 * 0.27;
			}
			mileCost += (dist - 600) * 0.21;
		}
		double amount = (days * rate) + mileCost;
		cout.setf(ios::fixed);
		cout.precision(2);
		cout << "The rental charge for " << name << " is $" << amount << endl;
	}
	return 0;


}