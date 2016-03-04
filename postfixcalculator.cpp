/*
  Program to implement an integer post-fix evaluator that supports +, -, *, / operators using STL stacks.
 */
#include<iostream>
#include<stack>
#include<unistd.h>
#include<string>
#include<algorithm>
#include<sstream>
#include<cstdlib>
#include<math.h>

using namespace std;

string evalExp(string exp, bool& success);

int main(int argc, char **argv){
    string expToEval = "";
    int c;
    bool success = true;
    while((c = getopt(argc,argv, "e:"))!= -1){
        switch (c){
            case 'e' :
                expToEval = optarg;
                break;
            case '?':
                if(optopt == 'e'){
                    cerr << "Expression to evaluate not found."<<endl;
                }
                return -1;
            default:
                abort();
        }
    }
    cout<<evalExp(expToEval, success)<<endl;
    if (success == true) {
        return 0;
    }
    else{
        return -1;
    }
    
}

/*
 Function to evaluate the expression being passed to it and returns the value
 */
string evalExp(string exp, bool& success){
    int count = 0;
    int operandCount = 0;
    int operatorCount = 0;
    stack<int> operands;
    int a;
    int b;
    int val;
    bool negVal = false;
    if (exp == "") {
        success = false;
        return "Expression to evaluate not found.";
    }
    for (int i = 0; i<exp.length(); i++) {
        if (exp[i]== ',') {
            i++;
        }
        if(exp[i] == '+'){
            operatorCount++;
            if (count<2) {
                success = false;
                return "Invalid operation.";
            }
            else{
                a = operands.top();
                operands.pop();
                b = operands.top();
                operands.pop();
                operands.push(b+a);
                operandCount++;
                switch (count) {
                    case 0:
                    case 1:
                        count++;
                        break;
                    case 2:
                        count=1;
                    default:
                        break;
                }
            }
            
        }
        else if(exp[i] == '-'){
            if(exp[i+1]>=48 && exp[i+1]<=57){
                negVal = true;
            }
            else if (!(count>=2 || exp[i+1] ==',' || i == exp.length()-1)) {
                success = false;
                return "Invalid operation.";
            }
            else{
                a = operands.top();
                operands.pop();
                b = operands.top();
                operands.pop();
                operands.push(b-a);
                operatorCount++;
                operandCount++;
                switch (count) {
                    case 0:
                    case 1:
                        count++;
                        break;
                    case 2:
                        count=1;
                    default:
                        break;
                }

            }
        }
        else if(exp[i] == '*'){
            operatorCount++;
            if (count<2) {
                success = false;
                return "Invalid operation.";
            }
            else{
                a = operands.top();
                operands.pop();
                b = operands.top();
                operands.pop();
                operands.push(b*a);
                operandCount++;
                switch (count) {
                    case 0:
                    case 1:
                        count++;
                        break;
                    case 2:
                        count=1;
                    default:
                        break;
                }

            }
        }
        else if(exp[i] == '/'){
            operatorCount++;
            if (count<2) {
                success = false;
              return "Invalid operation.";
            }
            else{
                a = operands.top();
                operands.pop();
                b = operands.top();
                operands.pop();
                if (a == 0) {
                    success = false;
                    return "Division by zero is not possible.";
                }
                else{
                    operands.push(b/a);
                    operandCount++;
                    switch (count) {
                        case 0:
                        case 1:
                            count++;
                            break;
                        case 2:
                            count=1;
                        default:
                            break;
                    }

                }
            }
        }
        else if ((exp[i]>=48 && exp[i]<=57)) {
            val = exp[i] - 48;
            int j;
            for (j=i+1; exp[j]!=','; j++) {
                if ((exp[j]>=48 && exp[j]<=57)) {
                    val = 10*val + exp[j] - 48;
                }
                else{
                    success = false;
                    return "Invalid operand.";
                }
            }
            i = j;
            if(negVal == true){
                val = val * -1;
                negVal = false;
            }
            operands.push(val);
            operandCount++;
            count++;
        }
        else{
            success = false;
            return "Invalid operand or operator.";
        }
    }
    if (operandCount-1 != operatorCount*2) {
        success = false;
        return "Incorrect number of operands.";
    }
    string retVal;
    stringstream out;
    out<<operands.top();
    retVal = out.str();
    return retVal;
}