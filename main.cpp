#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

//pass in space-delimited arguments when you call the executable
//Example: ./a.out 1 2 3.3
int main( int argc, char * argv[] )
{
	if (argc > 4) 
	{
		cout << "Too many arguments. Cannot pass in more than three." << endl;
		return -1;
	}

	int i = 1;
	double loan_amount, yearly_interest_rate, monthly_payment;

	double arguments [3];

	if (argc > 1)
	{
		while ( i < argc )
		{

			try
			{
				arguments[i-1] = stod(argv[i]);
			}
			catch(const std::invalid_argument&)
			{
				if(i==1)
					cout << "(Invalid loan amount): " << argv[i] << endl;
				else if (i==2)
					cout << "(Invalid interest rate): " << argv[i-1] << " " << argv[i] << endl;
				else
					cout << "(Invalid payment): " << argv[i-2] << " " << argv[i-1] << " " << argv[i] << endl;
				return -2;
			}
			i++;
		}
	}

	// Make sure three arguments were entered
	if (argc < 4)
	{
		cout << "Not enough arguments." << endl;
		return -1;
	}

	loan_amount = arguments[0];
	yearly_interest_rate = arguments[1];
	monthly_payment = arguments[2];

	// Check for invalid values
	if (loan_amount <= 0)
	{
		cout << "(Invalid loan amount): " << loan_amount << endl;
		return -1;
	}

	if (yearly_interest_rate < 0)
	{
		cout << "(Invalid interest rate): "
			 << loan_amount << " "
			 << yearly_interest_rate << endl;
		return -1;
	}

	if (monthly_payment <= 0)
	{
		cout << "(Invalid payment): "
			 << loan_amount << " "
			 << yearly_interest_rate << " "
			 << monthly_payment << endl;
		return -1;
	}

	// Calculate monthly interest rate
	double monthly_interest_rate = yearly_interest_rate / 12.0;
	double monthly_interest_decimal = monthly_interest_rate / 100.0;

	// Check if monthly payment is enough to pay the loan
	double first_month_interest = loan_amount * monthly_interest_decimal;

	if (monthly_payment <= first_month_interest)
	{
		cout << "(Insufficient payment): "
			 << loan_amount << " "
			 << yearly_interest_rate << " "
			 << monthly_payment << endl;
		return -1;
	}

	// Set currency formatting
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	// Display original input
	cout << "Loan Amount: " << loan_amount << endl;
	cout << "Interest Rate (% per year): " << yearly_interest_rate << endl;
	cout << "Monthly Payments: " << monthly_payment << endl;
	cout << endl;

	// Amortization table
	cout << "*****************************************************************" << endl;
	cout << "\t\tAmortization Table" << endl;
	cout << "*****************************************************************" << endl;
	cout << "Month\tBalance\t\tPayment\tRate\tInterest\tPrincipal" << endl;

	int currentMonth = 0;
	double interestTotal = 0.0;

	// Display month 0
	cout << currentMonth << "\t$"
		 << loan_amount
		 << "\t\tN/A\tN/A\tN/A\t\tN/A" << endl;

	// Loop until loan is paid off
	while (loan_amount > 0)
	{
		currentMonth++;

		// Calculate this month's interest
		double interest = loan_amount * monthly_interest_decimal;

		// Add interest to total interest paid
		interestTotal += interest;

		double payment;
		double principal;

		// Check if this is the last payment
		if (loan_amount + interest < monthly_payment)
		{
			payment = loan_amount + interest;
			principal = loan_amount;
			loan_amount = 0;
		}
		else
		{
			payment = monthly_payment;
			principal = payment - interest;
			loan_amount = loan_amount - principal;
		}

		// Prevent tiny floating point values from displaying
		if (loan_amount < 0.005)
		{
			loan_amount = 0;
		}

		// Display this month's information
		cout << currentMonth << "\t$"
			 << loan_amount;

		if (loan_amount < 1000)
			cout << "\t";

		cout << "\t$"
			 << payment
			 << "\t"
			 << monthly_interest_rate
			 << "\t$"
			 << interest
			 << "\t\t$"
			 << principal
			 << endl;
	}

	cout << "*****************************************************************" << endl;

	cout << endl;
	cout << "It takes " << currentMonth
		 << " months to pay off the loan." << endl;

	cout << "Total interest paid is: $"
		 << interestTotal << endl;

	cout << endl;

	return 0;
}
