#include <iostream>
#include <string>
#include <stack>
#include <math.h>
#include <stdlib.h>

using namespace std;

int main()
{
    stack <double> RPN_stk;
	double in1;
	double in2;
	double cur_num;
	bool only_0s = true;
	bool do_out = true;
	unsigned int stk_size;
	string cur_ins;
	cout << "Write something in reverse polish notation with\nspaces seperating numbers/operators and\n'=' / 'equals' to mark the end of equations."
		"\nTo get a list of possible operations, write '?' and press enter." << endl;
	while (true)
	{
		while (true)
		{
			cin >> cur_ins;
			if (cur_ins == "?")
			{
				cout << "\nOperators are:\na b + (a plus b / addition)\na b - (a minus b / subtraction)\na b * (a times b / multiplication)\na b / (a divided by b / division)\n"
					"a b % (the remainder of a divided by b / modulo)\na b ^ (a to the power of b / exponentiation)\na b hypo (hypotenuse of a and b)\na b atant (arctangent of a and b)\n"
					"a b max (the bigger number between a and b)\na b min (the smallest number between a and b)\n"
					"x sqrt (square root of x)\nx cbrt (cube root of x)\nx abs (absolute value of x)\nx sign (sign of x)\n"
					"x flor (x rounded down)\nx ceil (x rounded up)\nx round (x rounded to nearest integer)\n"
					"x nlog (natural logarithm of x / base e log)\nx clog (common decimal logarithm of x / base 10 log)\nx blog (common binary logarithm of x / base 2 log)\n"
					"x sin (sine of x)\nx cos (cosine of x)\nx tan (tangent of x)\n"
					"x asin (arcsine of x)\nx acos (arccosine of x)\nx atan (arctangent of x)\n"
					"x sinh (hyperbolic sine of x)\nx cosh (hyperbolic cosine of x)\nx tanh (hyperbolic tangent of x)\n"
					"x sinh (hyperbolic arcsine of x)\nx cosh (hyperbolic arccosine of x)\nx tanh (hyperbolic arctangent of x)\n"
					"\nConstants are:\npi - it is pi\neu - euler's number\ngr - golden ratio\n" << endl;
			}
			else if (cur_ins == "+" || cur_ins == "-" || cur_ins == "*" || cur_ins == "/" || cur_ins == "^" || cur_ins == "%" ||
				cur_ins == "hypo" || cur_ins == "atant" || cur_ins == "max" || cur_ins == "min" ||
				cur_ins == "sqrt" || cur_ins == "cbrt" || cur_ins == "abs" || cur_ins == "sign" ||
				cur_ins == "flor" || cur_ins == "ceil" || cur_ins == "round" || cur_ins == "nlog" || cur_ins == "clog" || cur_ins == "blog" ||
				cur_ins == "sin" || cur_ins == "cos" || cur_ins == "tan" || cur_ins == "asin" || cur_ins == "acos" || cur_ins == "atan" ||
				cur_ins == "sinh" || cur_ins == "cosh" || cur_ins == "tanh" || cur_ins == "asinh" || cur_ins == "acosh" || cur_ins == "atanh")
			{
				if (RPN_stk.size() > 0)
				{
					if (cur_ins == "sqrt" || cur_ins == "cbrt" || cur_ins == "abs" || cur_ins == "sign" ||
						cur_ins == "flor" || cur_ins == "ceil" || cur_ins == "nlog" || cur_ins == "clog" || cur_ins == "blog" ||
						cur_ins == "sin" || cur_ins == "cos" || cur_ins == "tan" || cur_ins == "asin" || cur_ins == "acos" || cur_ins == "atan" ||
						cur_ins == "sinh" || cur_ins == "cosh" || cur_ins == "tanh" || cur_ins == "asinh" || cur_ins == "acosh" || cur_ins == "atanh")
					{
						in2 = RPN_stk.top();
						RPN_stk.pop();
						cout << "POP: " << in2 << " BECAUSE OF OPERATION: '" << cur_ins << "', ";
					}
					else if (RPN_stk.size() > 1)
					{
						in2 = RPN_stk.top();
						RPN_stk.pop();
						in1 = RPN_stk.top();
						RPN_stk.pop();
						cout << "POP: " << in1 << " AND " << in2 << " BECAUSE OF OPERATION: '" << cur_ins << "', ";
					}
					else 
					{
						cerr << "ERROR: Not enough numbers for operation. OPERATOR IS: " << cur_ins << endl;
						do_out = false;
						break;
					}

					     if (cur_ins == "+") RPN_stk.push (in1 + in2);
					else if (cur_ins == "-") RPN_stk.push (in1 - in2);
					else if (cur_ins == "*") RPN_stk.push (in1 * in2);
					else if (cur_ins == "/") RPN_stk.push (in1 / in2);
					else if (cur_ins == "^") RPN_stk.push (pow(in1, in2));
					else if (cur_ins == "%") RPN_stk.push (fmod(in1, in2));
					else if (cur_ins == "hypo") RPN_stk.push (hypot(in1, in2)); //only c++11
					else if (cur_ins == "atant") RPN_stk.push (atan2(in1, in2));
					else if (cur_ins == "max") RPN_stk.push (max(in1, in2)); //only c++11
					else if (cur_ins == "min") RPN_stk.push (min(in1, in2)); //only c++11
					else if (cur_ins == "sqrt") RPN_stk.push (sqrt(in2));
					else if (cur_ins == "cbrt") RPN_stk.push (cbrt(in2)); //only c++11
					else if (cur_ins == "abs") RPN_stk.push (fabs(in2));
					else if (cur_ins == "sign") RPN_stk.push (copysign(1, in2)); //only c++11
					else if (cur_ins == "flor") RPN_stk.push (floor(in2));
					else if (cur_ins == "ceil") RPN_stk.push (ceil(in2));
					else if (cur_ins == "round") RPN_stk.push (round(in2)); //only c++11
					else if (cur_ins == "nlog") RPN_stk.push (log(in2));
					else if (cur_ins == "clog") RPN_stk.push (log10(in2));
					else if (cur_ins == "blog") RPN_stk.push (log2(in2)); //only c++11
					else if (cur_ins == "sin") RPN_stk.push (sin(in2));
					else if (cur_ins == "cos") RPN_stk.push (cos(in2));
					else if (cur_ins == "tan") RPN_stk.push (tan(in2));
					else if (cur_ins == "asin") RPN_stk.push (asin(in2));
					else if (cur_ins == "acos") RPN_stk.push (acos(in2));
					else if (cur_ins == "atan") RPN_stk.push (atan(in2));
					else if (cur_ins == "sinh") RPN_stk.push (sinh(in2));
					else if (cur_ins == "cosh") RPN_stk.push (cosh(in2));
					else if (cur_ins == "tanh") RPN_stk.push (tanh(in2));
					else if (cur_ins == "asinh") RPN_stk.push (asinh(in2)); //only c++11
					else if (cur_ins == "acosh") RPN_stk.push (acosh(in2)); //only c++11
					else if (cur_ins == "atanh") RPN_stk.push (atanh(in2)); //only c++11
					
					cout << " PUSH: " << RPN_stk.top() << " AS THE RESULT" << ", STACK SIZE: " << RPN_stk.size() << endl;
				}
				else
				{
					cerr << "ERROR: Not enough numbers for operation. OPERATOR IS: " << cur_ins << endl;
					do_out = false;
					break;
				}
			}
			else if (cur_ins == "=" || cur_ins == "equals")
			{
				break;
			}
			else if (cur_ins == "pi" || cur_ins == "eu" || cur_ins == "gr")
			{
				if (cur_ins == "pi") cur_num = 3.14159;
				else if (cur_ins == "eu") cur_num = 2.71828;
				else if (cur_ins == "gr") cur_num = 1.61803;

				RPN_stk.push (cur_num);
				cout << "PUSH: " << cur_num << " (" << cur_ins << "), STACK SIZE: " << RPN_stk.size() << "\n" ;
			}
			else
			{
				for (unsigned int cur_char = 0; cur_char < cur_ins.length(); cur_char++)
				{
					if (cur_ins[cur_char] != '0')
					{
						only_0s = false;
					}
				}
				cur_num = atof (cur_ins.c_str());
				if (cur_num == 0)
				{
					if (only_0s)
					{
						RPN_stk.push (cur_num);
						cout << "PUSH: " << cur_num << ", STACK SIZE: " << RPN_stk.size() << "\n";
					}
					else
					{
						cout << "'" << cur_ins << "' IS NOT COUNTED AS A NUMBER OR OPERATOR" << endl;
						only_0s = true;
					}
				}
				else
				{
					RPN_stk.push (cur_num);
					cout << "PUSH: " << cur_num << ", STACK SIZE: " << RPN_stk.size() << "\n";
					only_0s = true;
				}
			}
		}
		if (RPN_stk.size() == 1)
		{
			if (do_out) cout << "ANSWER: " << RPN_stk.top() << "\n" << endl;
			RPN_stk.pop();
		}
		else if (RPN_stk.size() > 1)
		{
			if (do_out) cerr << "ERROR: Too many inputs / stack too large. STACK SIZE: " << RPN_stk.size() << endl;
		}
		else if (RPN_stk.size() < 1)
		{
			if (do_out) cerr << "ERROR: Too few inputs / stack too small. STACK SIZE: " << RPN_stk.size() << endl;
		}
		stk_size = RPN_stk.size();
		for (unsigned int stk_pos = 0; stk_pos < stk_size; stk_pos++)
		{
			RPN_stk.pop();
		}
		do_out = true;
	}
	return 0;
}