#include <iostream>
#include <vector>
#include <algorithm>
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

class SineContainer : public NumericElement{

	shared_ptr<NumericElement> parameter;

public:
	SineContainer(){}
	SineContainer(shared_ptr<NumericElement> _parameter) : parameter(_parameter){}
	SineContainer(NumericElement* _parameter){

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
	vector<string> token_list;
	string type_of_expr_container; // AddendCont., FactorCont., ...
	vector<shared_ptr<MathExpressionNode>> son_nodes;

	bool chr_is_num(char token) { return (token >= 48 && token <= 57)? true : false; }
	bool is_symbol(string token) { return (token == "+" || token == "-" || token == "*" || token == "/" || token == "^"); }

	void break_down_expression(){

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

			if(chr_is_num(math_expression[i]))
			{
				if(chr_is_num(math_expression[i+1]))
				{
					token_buffer += math_expression[i];
				}
				else if(math_expression[i+1] == '.' && token_buffer.find(".") == string::npos) //For decimals
				{
					token_buffer = token_buffer + math_expression[i] + ".";cout << "decima num " << token_buffer<<"\n";
				}
				else 
				{
					token_list.push_back( token_buffer + math_expression[i] );
					token_buffer = "";

					if(math_expression[i+1] == 'x') token_list.push_back("*");
				}
				
				continue;
			}

			if(math_expression[i] == 'x')
			{
				token_list.push_back("x");

				if(math_expression[i+1] == 'x' || chr_is_num(math_expression[i+1])) token_list.push_back("*");

				continue;
			}

			if(math_expression.substr(i,3) == "log") { token_buffer += "log"; continue; }
			if(math_expression.substr(i,2) == "ln")  { token_buffer += "ln";  continue; }
			if(math_expression.substr(i,3) == "sin") { token_buffer += "sin"; continue; }
			if(math_expression.substr(i,3) == "cos") { token_buffer += "cos"; continue; }
			if(math_expression.substr(i,3) == "tan") { token_buffer += "tan"; continue; }

			if(math_expression[i] == '(' || math_expression[i] == '[' || math_expression[i] == '{')
			{
				token_buffer += math_expression[i];
				opened_parenthesis++;
				continue;
			}

			if(math_expression[i] == ')' || math_expression[i] == ']' || math_expression[i] == '}')
			{
				token_buffer += math_expression[i];

				if(opened_parenthesis > 0) opened_parenthesis--;

				if(opened_parenthesis == 0 && token_buffer.size() > 0)
				{
					token_list.push_back( token_buffer );
					token_buffer = "";
				}

				continue;
			}

			if(math_expression[i] == '+' || math_expression[i] == '-' 
				|| math_expression[i] == '*' || math_expression[i] == '/' || math_expression[i] == '^')
			{
				token_list.push_back(string(1,math_expression[i]));
				continue;
			}

			//Error recognizing tokens
			//...
		}

		if(token_list.size() == 1 && math_expression != "(-1)" &&
			((token_list[0])[0] == '(' || (token_list[0])[0] == '[' || (token_list[0])[0] == '{')) //If all the expression is encapsulated
		{
			math_expression = math_expression.substr(1, math_expression.size()-2); //Remove () [] {}
			token_list.clear();
			this->break_down_expression();
		}

		cout << "\n\nBreaked: \n";
		for(string s : token_list)
			cout << s << " | ";
		cout << "\n\n";
	}

	void set_type_of_expr_container(){

		if(token_list.size() <= 2 && 
			((token_list[0])[0] != '(' && (token_list[0])[0] != '[' && (token_list[0])[0] != '{')) //If all the expression is the parameter of a function
		{
			
			if(math_expression.substr(0,3) == "log") type_of_expr_container = "LogarithmContainer";
			if(math_expression.substr(0,2) == "ln")  type_of_expr_container = "NaturalLogarithmContainer";
			if(math_expression.substr(0,3) == "sin") type_of_expr_container = "SineContainer"; 
			if(math_expression.substr(0,3) == "cos") type_of_expr_container = "CosineContainer";
			if(math_expression.substr(0,3) == "tan") type_of_expr_container = "TangentContainer";

			return;
		}

		if(find(token_list.begin(), token_list.end(), "+") != token_list.end() ||
			find(token_list.begin(), token_list.end(), "-") != token_list.end())
		{
			type_of_expr_container = "AddendContainer";
			return;
		}

		if(find(token_list.begin(), token_list.end(), "*") != token_list.end())
		{
			type_of_expr_container = "FactorContainer";
			return;
		}

		if(find(token_list.begin(), token_list.end(), "/") != token_list.end())
		{
			type_of_expr_container = "FractionContainer";
			return;
		}

		if(find(token_list.begin(), token_list.end(), "^") != token_list.end())
		{
			type_of_expr_container = "PowerContainer";
			return;
		}
	}

public:
	MathExpressionNode(string _math_expression) : math_expression(_math_expression){}
	

	void make_tree(){

		break_down_expression();
		set_type_of_expr_container();

		if(type_of_expr_container == "SineContainer" || type_of_expr_container == "CosineContainer" || type_of_expr_container == "TangentContainer")
		{
			son_nodes.push_back( shared_ptr<MathExpressionNode>(new MathExpressionNode(token_list[0].substr(3, token_list[0].size()-3))) );
		}

		else if(type_of_expr_container == "NaturalLogarithmContainer")
		{
			son_nodes.push_back( shared_ptr<MathExpressionNode>(new MathExpressionNode("2.718281828")));//e number as base
			son_nodes.push_back( shared_ptr<MathExpressionNode>(new MathExpressionNode(token_list[0].substr(2, token_list[0].size()-2))) );
		}

		else if(type_of_expr_container == "LogarithmContainer")
		{ 	
			if(token_list.size() == 2) //log2(x) log(3-1)(x)
			{
				son_nodes.push_back( shared_ptr<MathExpressionNode>(new MathExpressionNode(token_list[0].substr(3, token_list[0].size()-3))) );
				son_nodes.push_back( shared_ptr<MathExpressionNode>(new MathExpressionNode(token_list[1])) );
			}
			else //log(x)
			{
				son_nodes.push_back( shared_ptr<MathExpressionNode>(new MathExpressionNode("10"))); //First node is de base numeric element
				son_nodes.push_back( shared_ptr<MathExpressionNode>(new MathExpressionNode(token_list[0].substr(3, token_list[0].size()-3))) );
			}
		}

		else
		{
			if(token_list.size() == 1){
				if(chr_is_num((token_list[0])[0]) || token_list[0] == "(-1)") type_of_expr_container = "PureNumber";//set the value
				if(token_list[0] == "x") type_of_expr_container = "UnknownValue";
				return;
			}

			for(int i = 0; i < token_list.size(); i++) //Replace the - by + (-1) *
			{
				if(is_symbol(token_list[i]) == true && token_list[i] == "-")
				{
					token_list[i] = "+";
					token_list.insert(token_list.begin() + i+1, {"(-1)", "*"});
				}
			}
			cout << "\n\nWithout minuses: \n";
			for(string s : token_list)
				cout << s << " | ";
			cout << "\n\n";

			string less_prioritary_simbol;
			if(type_of_expr_container == "AddendContainer")		   less_prioritary_simbol = "+";
			else if(type_of_expr_container == "FactorContainer")   less_prioritary_simbol = "*";
			else if(type_of_expr_container == "FractionContainer") less_prioritary_simbol = "/";
			else if(type_of_expr_container == "PowerContainer")	   less_prioritary_simbol = "^";

			string expr_token_buffer;

			for(int i = 0; i < token_list.size(); i++)
			{
				if(is_symbol(token_list[i]) == false)
				{

					if(i == token_list.size()-1){
						son_nodes.push_back( shared_ptr<MathExpressionNode>(new MathExpressionNode(expr_token_buffer + token_list[i])) );
						break;
					}

					if(is_symbol(token_list[i+1]) == false)
					{
						if(token_list[i].substr(0,3) != "log") token_list.insert(token_list.begin() + i+1, "*");
						else{
							son_nodes.push_back( shared_ptr<MathExpressionNode>(new MathExpressionNode(expr_token_buffer + token_list[i] + token_list[i+1])) );
							i++;
							expr_token_buffer = "";
						}
					}
					
					else if(is_symbol(token_list[i+1]) == true && token_list[i+1] == less_prioritary_simbol){
						son_nodes.push_back( shared_ptr<MathExpressionNode>(new MathExpressionNode(expr_token_buffer + token_list[i])) );
						expr_token_buffer = "";
					}

					else if(is_symbol(token_list[i+1]) == true && token_list[i+1] != less_prioritary_simbol)
					{
						expr_token_buffer += token_list[i] + " " + token_list[i+1];
						i++;
					}

					continue;
				}

			}
		}
		cout << "in " << math_expression << "  of type " << type_of_expr_container << "\n___________________\n";
		cin.get();

		for(shared_ptr<MathExpressionNode> son_node : son_nodes)
			son_node->make_tree();
	}

	NumericElement* to_NumericElement(){

		if(type_of_expr_container == "PureNumber")
		{
			return new PureNumber(stod( (math_expression == "(-1)")? "-1" : math_expression ));//<<<<<<<<<<<<<<<<<<<<<<<
		}

		else if(type_of_expr_container == "UnknownValue")
		{
			return new UnknownValue();
		}

		else if(type_of_expr_container == "AddendContainer")
		{
			vector<NumericElement*> addends;

			for(shared_ptr<MathExpressionNode> son_node : son_nodes)
				addends.push_back(son_node->to_NumericElement());

			return new AddendContainer(addends);
		}

		else if(type_of_expr_container == "FactorContainer")
		{
			vector<NumericElement*> factors;

			for(shared_ptr<MathExpressionNode> son_node : son_nodes)
				factors.push_back(son_node->to_NumericElement());

			return new FactorContainer(factors);
		}

		else if(type_of_expr_container == "FractionContainer")
		{
			return new FractionContainer(son_nodes[0]->to_NumericElement(), son_nodes[1]->to_NumericElement());
		}

		else if(type_of_expr_container == "PowerContainer")
		{
			return new PowerContainer(son_nodes[0]->to_NumericElement(), son_nodes[1]->to_NumericElement());
		}

		else if(type_of_expr_container == "LogarithmContainer")
		{
			return new LogarithmContainer(son_nodes[0]->to_NumericElement(), son_nodes[1]->to_NumericElement());
		}

		else if(type_of_expr_container == "SineContainer")
		{
			return new SineContainer(son_nodes[0]->to_NumericElement());
		}

		else return new PureNumber(1);
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
//sin[2x + log(x - 3x) - 5] / (3 - x) + 6*2 - log(x - 2)(x)
	MathExpressionNode m("x^2 + 4x + 4");
	m.make_tree();
	NumericElement* ne =  m.to_NumericElement();
	cout << ne->operate(-2);

	cin.get();
}