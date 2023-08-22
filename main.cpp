#include <iostream>
#include <vector>
#include <memory>
#include <math.h>

using namespace std;

/*
y =  3
y =  2 + x
y =  3x
y =  1 / x
y =  x^3
y =  sin(x)
y =  ln(x)
y =  log2(x)
y =  e^(x)
y =  3^(x)
y =  ( x^2 + ln(x+3) ) / ( 3x^3 - 8x + 23)
*/

class NumericElement{

public:
	NumericElement(){}
	virtual double operate(double x_val){ return 1; }
};

class PureNumber : public NumericElement{

	double number;

public:
	PureNumber(double _number) : number(_number){}
	set_number(double _number) { number = _number; }
	
	double operate(double x_val)  { return number; }
};

class UnknownValue : public NumericElement{

public:
	UnknownValue(){}

	double operate(double x_val)  { return x_val; }
};


class AddendContainer : public NumericElement{

	vector<shared_ptr<NumericElement>> addends;

public:
	AddendContainer(){}
	AddendContainer(vector<shared_ptr<NumericElement>> _addends) : addends(_addends){}
	AddendContainer(vector<NumericElement*> _addends){
		for(NumericElement* N_el : _addends) 
			addends.push_back( shared_ptr<NumericElement>(N_el) );
	}

	void set_addends(vector<shared_ptr<NumericElement>> _addends) { addends = _addends; }
	void set_addends(vector<NumericElement*> _addends) { 

		for(NumericElement* N_el : _addends) 
			addends.push_back( shared_ptr<NumericElement>(N_el) ); 
	}

	void add(shared_ptr<NumericElement> N_el) { addends.push_back(N_el); }
	void add(NumericElement* N_el) { addends.push_back( shared_ptr<NumericElement>(N_el) ); }

	double operate(double x_val) override {

		double result = 0;

		for(shared_ptr<NumericElement> N_el : addends)
		{
			result += N_el->operate(x_val);
		}

		return result;
	}
};

class FactorContainer : public NumericElement{

	vector<shared_ptr<NumericElement>> factors;

public:
	FactorContainer(){}
	FactorContainer(vector<shared_ptr<NumericElement>> _factors) : factors(_factors){}
	FactorContainer(vector<NumericElement*> _factors){
		for(NumericElement* N_el : _factors) 
			factors.push_back( shared_ptr<NumericElement>(N_el) );
	}

	void set_factors(vector<shared_ptr<NumericElement>> _factors) { factors = _factors; }
	void set_factors(vector<NumericElement*> _factors) { 

		for(NumericElement* N_el : _factors) 
			factors.push_back( shared_ptr<NumericElement>(N_el) ); 
	}

	void add(shared_ptr<NumericElement> N_el) { factors.push_back(N_el); }
	void add(NumericElement* N_el) { factors.push_back( shared_ptr<NumericElement>(N_el) ); }

	double operate(double x_val) override {

		double result = 1;

		for(shared_ptr<NumericElement> N_el : factors)
		{
			result *= N_el->operate(x_val);
		}

		return result;
	}
};

class FractionContainer : public NumericElement{

	shared_ptr<NumericElement> numerator;
	shared_ptr<NumericElement> denominator;

public:
	FractionContainer(){}
	FractionContainer(shared_ptr<NumericElement> _numerator, shared_ptr<NumericElement> _denominator) : numerator(_numerator), denominator(_denominator){}
	FractionContainer(NumericElement* _numerator, NumericElement* _denominator){

		numerator = shared_ptr<NumericElement>(_numerator);
		denominator = shared_ptr<NumericElement>(_denominator);
	}

	void set_numerator(shared_ptr<NumericElement> _numerator) { numerator = _numerator; }
	void set_numerator(NumericElement* _numerator) { numerator = shared_ptr<NumericElement>(_numerator); }

	void set_denominator(shared_ptr<NumericElement> _denominator) { denominator = _denominator; }
	void set_denominator(NumericElement* _denominator) { denominator = shared_ptr<NumericElement>(_denominator); }

	double operate(double x_val) override {

		return numerator->operate(x_val) / denominator->operate(x_val); //check if denominador = 0 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	}
};

class PowerContainer : public NumericElement{

	shared_ptr<NumericElement> base;
	shared_ptr<NumericElement> exponent;

public:
	PowerContainer(){}
	PowerContainer(shared_ptr<NumericElement> _base, shared_ptr<NumericElement> _exponent) : base(_base), exponent(_exponent){}
	PowerContainer(NumericElement* _base, NumericElement* _exponent){

		base = shared_ptr<NumericElement>(_base);
		exponent = shared_ptr<NumericElement>(_exponent);
	}

	void set_base(shared_ptr<NumericElement> _base) { base = _base; }
	void set_base(NumericElement* _base) { base = shared_ptr<NumericElement>(_base); }

	void set_exponent(shared_ptr<NumericElement> _exponent) { exponent = _exponent; }
	void set_exponent(NumericElement* _exponent) { exponent = shared_ptr<NumericElement>(_exponent); }

	double operate(double x_val) override {

		return pow(base->operate(x_val), exponent->operate(x_val));
	}
};

class LogarithmContainer : public NumericElement{

	shared_ptr<NumericElement> base;
	shared_ptr<NumericElement> argument;

public:
	LogarithmContainer(){}
	LogarithmContainer(shared_ptr<NumericElement> _base, shared_ptr<NumericElement> _argument) : base(_base), argument(_argument){}
	LogarithmContainer(NumericElement* _base, NumericElement* _argument){

		base = shared_ptr<NumericElement>(_base);
		argument = shared_ptr<NumericElement>(_argument);
	}

	void set_base(shared_ptr<NumericElement> _base) { base = _base; }
	void set_base(NumericElement* _base) { base = shared_ptr<NumericElement>(_base); }

	void set_argument(shared_ptr<NumericElement> _argument) { argument = _argument; }
	void set_argument(NumericElement* _argument) { argument = shared_ptr<NumericElement>(_argument); }

	double operate(double x_val) override {

		return log(argument->operate(x_val)) / log(base->operate(x_val));
	}
};

class SinContainer : public NumericElement{

	shared_ptr<NumericElement> parameter;

public:
	SinContainer(){}
	SinContainer(shared_ptr<NumericElement> _parameter) : parameter(_parameter){}
	SinContainer(NumericElement* _parameter){

		parameter = shared_ptr<NumericElement>(_parameter);
	}

	void set_parameter(shared_ptr<NumericElement> _parameter) { parameter = _parameter; }
	void set_parameter(NumericElement* _parameter) { parameter = shared_ptr<NumericElement>(_parameter); }

	double operate(double x_val) override {

		return sin(parameter->operate(x_val));
	}
};

class MathExpressionNode{

	string math_expression;
	string type_of_expr_container; // AddendCont., FactorCont., ...
	vector<shared_ptr<MathExpressionNode>> son_nodes;

	bool chr_is_num(char token) { return (token >= 48 && token <= 57)? true : false; }

public:
	MathExpressionNode(string _math_expression) : math_expression(_math_expression){}
	
	void break_down_expression(){

		vector<string> token_list;
		string token_buffer;
		int opened_parenthesis = 0;

		for(int i = 0; i < math_expression.size(); i++)
		{
			if(opened_parenthesis > 0)
			{
				if(math_expression[i] != '(' && math_expression[i] != '[' && math_expression[i] != '{'
					&& math_expression[i] != ')' && math_expression[i] != ']' && math_expression[i] != '}')
				{
					token_buffer += math_expression[i];
					continue;
				}
			}

			if(math_expression[i] == ' ') continue;

			if(chr_is_num(math_expression[i]) || math_expression[i] == 'x')
			{cout << "numbers";
				if(chr_is_num(math_expression[i+1]) || math_expression[i+1] == 'x') 
					token_buffer += math_expression[i];
				else {
					token_list.push_back( token_buffer + math_expression[i] );
					token_buffer = "";
				}
				
				continue;
			}
/*
			if(math_expression.substr(i,3) == "log") { token_buffer += "log"; continue; }
			if(math_expression.substr(i,2) == "ln")  { token_buffer += "ln";  continue; }
			if(math_expression.substr(i,3) == "sin") { token_buffer += "sin"; continue; }
			if(math_expression.substr(i,3) == "cos") { token_buffer += "cos"; continue; }
			if(math_expression.substr(i,3) == "tan") { token_buffer += "tan"; continue; }*/

			if(math_expression[i] == '(' || math_expression[i] == '[' || math_expression[i] == '{')
			{
				token_buffer += math_expression[i];
				opened_parenthesis++;cout << "open_par"<<opened_parenthesis;
				continue;
			}

			if(math_expression[i] == ')' || math_expression[i] == ']' || math_expression[i] == '}')
			{cout << "close_par"<<opened_parenthesis;
				token_buffer += math_expression[i];

				if(opened_parenthesis > 0) opened_parenthesis--;

				if(opened_parenthesis == 0 && token_buffer.size() > 0)
				{cout << "\n" << token_buffer << "\n";
					token_list.push_back( token_buffer );
					token_buffer = "";
				}

				continue;
			}

			if(math_expression[i] == '+' || math_expression[i] == '-' || math_expression[i] == '*' 
				|| math_expression[i] == 250/* '·' */ || math_expression[i] == '/' || math_expression[i] == '^')
			{cout << "sign";
				token_list.push_back(string(1,math_expression[i]));
				continue;
			}

			//Error recognizing tokens
			//...
		}
		cout << "\n\n";
		for(string s : token_list)
			cout << s << "\n";
	}
};

class Function{


public:

	Function(){}
	Function(string expression){


	}
};



int main(){

	/*
	shared_ptr<NumericElement> a1(new PureNumber(2));
	shared_ptr<NumericElement> a2(new UnknownValue());
	shared_ptr<NumericElement> A(new FactorContainer({a1,a2}));


	shared_ptr<NumericElement> b1(new UnknownValue());

	shared_ptr<NumericElement> bb2(new PureNumber(-3));
	shared_ptr<NumericElement> bb3(new UnknownValue());

	shared_ptr<NumericElement> b2(new FactorContainer({bb2,bb3}));

	shared_ptr<NumericElement> B(new AddendContainer({b1,b2}));


	shared_ptr<NumericElement> C(new PureNumber(-5));*/
/*
	NumericElement* A = new PureNumber(10);
	NumericElement* B = new PureNumber(20);
	LogarithmContainer c(A,B);
	cout << c.operate(1);*/

	MathExpressionNode m("[2x + (x - 3x) - 5] / (3 - x) + 6");
	m.break_down_expression();

	cin.get();
}