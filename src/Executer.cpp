#include "Executer.hpp"

#include <stack>
#include <iostream>

using namespace std;

template <class T, class T_EL>
void from_stack(T& st, T_EL& i) {
    i = st.top(); st.pop();
}

void Executer::execute(vector<Lex>& poliz) {
    cout << "OUTPUT: " << endl;
    Lex pc_el;
    stack<int> args;
    int i, j, index = 0, size = poliz.size();
    while (index < size) {
        pc_el = poliz[index];
        switch (pc_el.get_type()) {
            case LEX_TRUE:
            case LEX_FALSE:
            case LEX_NUM:
            case POLIZ_ADDRESS:
            case POLIZ_LABEL:
                args.push(pc_el.get_value());
                break;
            case LEX_ID:
                i = pc_el.get_value();
                if (TID[i].get_assign()) {
                    args.push(TID[i].get_value());
                    break;
                } else if(TID[i].get_type()==LEX_RECORD){
                    // for(Ident x:TID){
                    //     if(x.get_namespace()==TID[i].get_name()){
                    //         args.push(x.get_value());
                    //     }
                    // }
                    throw "Record functions undefined";
                }else{
                    throw "POLIZ: indefinite identifier";                    
                }
 
            case LEX_NOT:
                from_stack(args, i);
                args.push(!i);
                break;
            case LEX_OR:
                from_stack(args, i); 
                from_stack(args, j);
                args.push(j || i);
                break;
            case LEX_AND:
                from_stack(args, i);
                from_stack(args, j);
                args.push(j && i);
                break;
            case POLIZ_GO:
                from_stack(args, i);
                index = i - 1;
                break;
            case POLIZ_FGO:
                from_stack(args, i);
                from_stack(args, j);
                if (!j) {
                    index = i - 1;
                }
                break;
            case LEX_WRITE:
                while(!args.empty()){
                    from_stack(args, j);
                    cout << j << endl;
                }
                break;
            case LEX_READ:
                int k;
                from_stack(args, i);
                if (TID[i].get_type () == LEX_INT) {
                    cout << "Input int value for " << TID[i].get_name () << endl;
                    cin >> k;
                }
                else {
                    string j;
                    while (1) {
                        cout << "Input boolean value (true or false) for" << TID[i].get_name() << endl;
                        cin >> j;
                        if (j != "true" && j != "false") {
                            cout << "Error in input:true/false" << endl;
                            continue;
                        }
                        k = (j == "true") ? 1 : 0;
                        break;
                    }
                }
                TID[i].put_value(k);
                TID[i].put_assign();
                break;
            case LEX_PLUS:
                from_stack(args, i);
                from_stack(args, j);
                args.push(i + j);
                break;
            case LEX_TIMES:
                from_stack(args, i);
                from_stack(args, j);
                args.push(i * j);
                break;
            case LEX_MINUS:
                from_stack(args, i);
                from_stack(args, j);
                args.push(j - i);
                break;
            case LEX_SLASH:
                from_stack(args, i);
                from_stack(args, j);
                if (i) {
                    args.push (j / i);
                    break;
                }
                else {
                    throw "POLIZ:divide by zero";                    
                }
            case LEX_EQ:
                from_stack(args, i);
                from_stack(args, j);
                args.push(i == j);
                break;
            case LEX_LSS:
                from_stack(args, i);
                from_stack(args, j);
                args.push(j < i);
                break;
            case LEX_GTR:
                from_stack(args, i);
                from_stack(args, j);
                args.push(j > i);
                break;
            case LEX_LEQ:
                from_stack(args, i);
                from_stack(args, j);
                args.push(j <= i);
                break;
            case LEX_GEQ:
                from_stack(args, i);
                from_stack(args, j);
                args.push(j >= i);
                break;
            case LEX_NEQ:
                from_stack(args, i);
                from_stack(args, j);
                args.push(j != i);
                break;
            case LEX_ASSIGN:
                from_stack(args, i);
                from_stack(args, j);
                TID[j].put_value (i);
                TID[j].put_assign (); 
                break;
            default:
                throw "POLIZ: unexpected elem";
        }
        ++index;
    }
}