#include <iostream>
#include <stdexcept>
#include <iomanip>

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

	loan_amount = arguments[0];
	yearly_interest_rate = arguments[1];
	monthly_payment = arguments[2];
	cout << loan_amount << " " << yearly_interest_rate << " " << monthly_payment << endl;
       
// Variables for loan

        double monthly_rate;
        double monthly_interest;
        double principal;
	double total_interest = 0;
	double last_payment = 0;
	int current_month = 0;

        int months = 0;

//convert yearly interest rate to monthly
	monthly_rate = yearly_interest_rate / 12;

// formatting from the hints
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
	
	
	//make sure values are valid
	if (loan_amount <= 0)
	{
		cout << "Invalid loan amount" << endl;
	       return -1;
	}

	if (yearly_interest_rate < 0)
	{
		cout << "Invalid interest rate" << endl;
		return -1;
	}

	double interest_rate_calculation = monthly_rate / 100;

        if (monthly_payment <= loan_amount * interest_rate_calculation)
	{
		cout << "Invalid monthly payment" << endl;
		return -1;
	}
   // AMORTIZATION TABLE from hint

   cout << "********************************************************" << endl;
   cout << "                Amortization Table " << endl;  
   cout << "********************************************************" << endl;   
     
	
	 cout << "Month"
	 << "\tBalance"
	 << "\tPayment"
	 << "\tRate"
	 << "\tInterest"
	 << "\tPrincipal"
	 << endl;

   //month zero
   //cout << left
   //     << setw(8) << current_month
   //     << "$" << setw(11) << loan_amount
   //     << setw(12) << "N/A"
   //     << setw(8) << "N/A"
   //     << setw(12) << "N/A"
   //     << setw(12) << "N/A"
   //     << endl;

   // can start here we need monthly calculation loop for each month's interest
   // print each row of the remaining balances using principal
   // and after that should be the last payment and final totals
 

    while (loan_amount > 0)
    {
		// used for first month + came from the hint sheet
	    if (current_month == 0) {
			cout << current_month++ << "\t$" << loan_amount;
		
			if (loan_amount < 1000) cout << "\t"; {
				cout << "\t" << "N/A\tN/A\tN/A\t\tN/A\n";
			}
		}
		else 
		{
			double interest = loan_amount * interest_rate_calculation; // interest owed in the period so it updates
			// below is the last monthe that includes whatever is left to be paid
			if (loan_amount * (1 + interest_rate_calculation) < monthly_rate) {
				last_payment = loan_amount + interest;
				principal = loan_amount;
				loan_amount = 0;
			}
			// below is a normal month 
			if (loan_amount * (1 + interest_rate_calculation) >= monthly_rate) {
				last_payment = monthly_payment;
				principal = monthly_payment - interest;
				loan_amount -= principal;
			}
		total_interest += interest; // adding the interest up for final output
		// below is printing out the month information
		cout << current_month << "\t$" << loan_amount << "\t$" << last_payment << "\t$" << interest_rate_calculation << "\t$" << interest << "\t$" << principal << endl;
		current_month++;
    	}
	}
	// below is formating and printing of the final outputs
	cout << "****************************************************************\n";
	cout << "\nIt takes " << --current_month << " months to pay off " << "the loan.\n" << "Total interest paid is: $" << total_interest << endl;
	return 0;
}
