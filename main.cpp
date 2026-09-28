#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>

using namespace std;

// Pass in space-delimited arguments when you call the executable
// Example: ./a.out 1000 18 50
int main(int argc, char *argv[])
{
    // More than 3 arguments
    if (argc > 4)
    {
        cout << "Too many arguments. Cannot pass in more than three." << endl;
        return -1;
    }

    double arguments[3] = {0.0, 0.0, 0.0};

    // Convert each supplied argument to a number
    for (int i = 1; i < argc; i++)
    {
        try
        {
            arguments[i - 1] = stod(argv[i]);
        }
        catch (const invalid_argument&)
        {
            if (i == 1)
            {
                cout << "(Invalid loan amount): "
                     << argv[i] << endl;
            }
            else if (i == 2)
            {
                cout << "(Invalid interest rate): "
                     << argv[i - 1] << " "
                     << argv[i] << endl;
            }
            else
            {
                cout << "(Invalid payment): "
                     << argv[i - 2] << " "
                     << argv[i - 1] << " "
                     << argv[i] << endl;
            }

            return -2;
        }
        catch (const out_of_range&)
        {
            cout << "Invalid argument." << endl;
            return -2;
        }
    }

    // Check supplied values BEFORE checking for missing arguments.
    // This allows cases such as "./a.out -1000" to report
    // the invalid loan amount correctly.

    if (argc >= 2 && arguments[0] <= 0)
    {
        cout << "(Invalid loan amount): "
             << argv[1] << endl;
        return -1;
    }

    if (argc >= 3 && arguments[1] < 0)
    {
        cout << "(Invalid interest rate): "
             << argv[1] << " "
             << argv[2] << endl;
        return -1;
    }

    if (argc >= 4 && arguments[2] <= 0)
    {
        cout << "(Invalid payment): "
             << argv[1] << " "
             << argv[2] << " "
             << argv[3] << endl;
        return -1;
    }

    // Make sure all three arguments were entered
    if (argc < 4)
    {
        cout << "Not enough arguments." << endl;
        return -1;
    }

    double loan_amount = arguments[0];
    double yearly_interest_rate = arguments[1];
    double monthly_payment = arguments[2];

    // Calculate monthly interest rate
    double monthly_interest_rate =
        yearly_interest_rate / 12.0;

    double monthly_interest_decimal =
        monthly_interest_rate / 100.0;

    // Check whether payment is enough to reduce the loan
    double first_month_interest =
        loan_amount * monthly_interest_decimal;

    if (monthly_payment <= first_month_interest)
    {
        cout << "(Insufficient payment): "
             << loan_amount << " "
             << yearly_interest_rate << " "
             << monthly_payment << endl;

        return -1;
    }

    // Currency formatting
    cout << fixed << setprecision(2);

    // Display original input
    cout << "Loan Amount: "
         << loan_amount << endl;

    cout << "Interest Rate (% per year): "
         << yearly_interest_rate << endl;

    cout << "Monthly Payments: "
         << monthly_payment << endl;

    cout << endl;

    // Amortization table
    cout << "*****************************************************************" << endl;
    cout << "\t\tAmortization Table" << endl;
    cout << "*****************************************************************" << endl;

    cout << "Month\tBalance\t\tPayment\tRate\tInterest\tPrincipal"
         << endl;

    int currentMonth = 0;
    double interestTotal = 0.0;

    // Month 0
    cout << currentMonth
         << "\t$"
         << loan_amount
         << "\t\tN/A\tN/A\tN/A\t\tN/A"
         << endl;

    // Calculate each month
    while (loan_amount > 0)
    {
        currentMonth++;

        double interest =
            loan_amount * monthly_interest_decimal;

        interestTotal += interest;

        double payment;
        double principal;

        // Final payment
        if (loan_amount + interest <= monthly_payment)
        {
            payment = loan_amount + interest;
            principal = loan_amount;
            loan_amount = 0.0;
        }
        else
        {
            payment = monthly_payment;
            principal = payment - interest;
            loan_amount -= principal;
        }

        // Prevent tiny floating-point balances
        if (loan_amount < 0.005)
        {
            loan_amount = 0.0;
        }

        // Display the month's information
        cout << currentMonth
             << "\t$"
             << loan_amount;

        if (loan_amount < 1000)
        {
            cout << "\t";
        }

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

    cout << "*****************************************************************"
         << endl;

    cout << endl;

    if (currentMonth == 1)
    {
        cout << "It takes 1 month to pay off the loan."
             << endl;
    }
    else
    {
        cout << "It takes "
             << currentMonth
             << " months to pay off the loan."
             << endl;
    }

    cout << "Total interest paid is: $"
         << interestTotal
         << endl;

    cout << endl;

    return 0;
}
