#include "VM.h"

void add_code_memory (string content);
void VM::run(string filename)
{
	ifstream file(filename.c_str());
    if (!file)
    {
      cout<<"Cannot open file\n";
      return;
    }

    string temp;

    while(getline(file,temp)) {
        content +=temp;
        content.push_back('\n');
    }
  file.close();
  add_code_memory(content);
  execute_register(0);
}

void VM::add_code_memory (string init) {
  string input = init;
  int  i =0;
  size_t pos,pos_ = 0;
  string delimiter = "\n";
  string space = " ";
  string semi = ",";
  while ((pos = input.find(delimiter)) != std::string::npos) {
    mem[i] = input.substr(0, pos);
    temp[i] = input.substr(0, pos);
    i++;
    input.erase(0, pos + delimiter.length());
} 
  int k=0;
  while (k<i) {
    int count = 0;
    bool ok = false;
    pos_ = temp[k].find(space);
    temp[k].erase(0,pos_+1);
    for (size_t z = 0; z<temp[k].length(); z++)
    {
      if (temp[k][z] == ' ') {
        count++;
      }
      if (temp[k][z] == ',') {
          string tempp = temp[k].substr(0,z);
            for (int i = 0;i<15;i++) {
            if (tempp == addr->labels[i]) {
              ok = true;
            }
        }
          if (ok == false) {throw (InvalidOperand(k)); destroy_all(); exit(0);}
      }
    }
      if (count>1) {
        throw(InvalidInstruction(k));
        destroy_all();
        exit(0);
      }
        k++;
    }
  
  checker->num_ip = i;
}
//template<typename T>
void VM::execute_register(int i) {
    checker->ip = i;
    size_t pos = 0;
    string delimiter = " ";
    int number_instruction = checker->num_ip;
    while (checker->ip<number_instruction-1) {
      pos = mem[checker->ip].find(delimiter);
      checker->kind =  mem[checker->ip].substr(0,pos);
      if (checker -> kind == "Add") {
        action_add(temp[checker->ip]);
      }
      else if (checker -> kind == "Minus")
      {
        action_minus(temp[checker->ip]);
      }
      else if (checker -> kind == "Mul")
      {
        action_mul(temp[checker->ip]);
      }
      else if (checker -> kind == "Div")
      {
        action_div(temp[checker->ip]);
      }
      else if (checker -> kind == "CmpEQ")
      {
        action_CmpEQ(temp[checker->ip]);
      }
      else if (checker -> kind == "CmpNE")
      {
        action_CmpNE(temp[checker->ip]);
      }
      else if (checker -> kind == "CmpLT")
      {
        action_CmpLT(temp[checker->ip]);
      }
      else if (checker -> kind == "CmpLE")
      {
        action_CmpLE(temp[checker->ip]);
      }
      else if (checker -> kind == "CmpGT")
      {
        action_CmpGT(temp[checker->ip]);
      }
      else if (checker -> kind == "CmpGE")
      {
        action_CmpGE(temp[checker->ip]);
      }
      else if (checker -> kind == "Not")
      {
        action_not(temp[checker->ip]);
      }
      else if (checker -> kind == "And")
      {
        action_and(temp[checker->ip]);
      }
      else if (checker -> kind == "Or")
      {
        action_or(temp[checker->ip]);
      }
      else if (checker -> kind == "Move")
      {
        action_move(temp[checker->ip]);
      }
      else if (checker -> kind == "Load")
      {
        action_load(temp[checker->ip]);
      }
      else if (checker -> kind == "Store")
      {
        action_store(temp[checker->ip]);
      }
      else if (checker -> kind == "Jump")
      {
        action_jump(temp[checker->ip]);
      }
      else if (checker -> kind == "JumpIf")
      {
        action_jumpif(temp[checker->ip]);
       }
      else if (checker -> kind == "Call")
      {
        action_call(temp[checker->ip],i);
      }
      else if (checker -> kind == "Return")
      {
        action_return();
      }
      else if (checker -> kind == "Halt")
      {
        running = false;
        action_halt();
      }
      else if (checker -> kind == "Input")
      {
        action_input(temp[checker->ip]);
      }
      else if (checker -> kind == "Output")
      { 
        action_output(temp[checker->ip]);
      }
      else {
        throw(InvalidInstruction(checker->ip));
        destroy_all();
        exit(0);
      }
      checker->ip++;
    } 
};
void VM::action_input(string input) {
  bool ok = false;
  for (int i = 0; i<15;  i++) {
    if (addr->labels[i] == input) {
      ok = true;
    }
  }
  
    if (ok ==false) {
      throw(InvalidInput(checker->ip));
      exit(0);
    }
}
void VM::action_return() {  
  int t = pop();
  execute_register(t+1);
}
void VM::action_call (string input, int i) {
  int temp = stod(input);
  bool new_ip = push(i);
  if (new_ip) {execute_register(temp);}
}

void VM::action_not(string input) {
  size_t pos = 0;
  string delimiter = ",";
  string temp;
  pos = input.find(delimiter);
  string des = input.substr(0,pos);
  for (int i = 0; i <15; i++)
  {
    if (addr->labels[i] == des)
    { addr->compare_check[i] = !addr->compare_check[i];
      break;
    }
}
}
void VM::action_and(string input) {
  size_t pos = 0;
  string delimiter = ",";
  string temp;
  bool x,y;
  pos = input.find(delimiter);
  int order_des  = 0;
  string des = input.substr(0,pos);
  string source = input.substr(pos+2,input.length()-1);
  if (source == "true") { y = true;} 
  else if (source == "false") { y= false;}
  else {
      for (int i = 0 ; i<15; i++ ) {
          if (addr->labels[i] == des ){
            x = addr->compare_check[i];
            order_des = i;}
          if (addr->labels[i] == source)
          {
            y = addr->compare_check[i];
            };
  }
  }
  x = x&&y;
  addr->compare_check[order_des] = x;
}
void VM::action_or(string input) {
  size_t pos = 0;
  string delimiter = ",";
  string temp;
  bool x,y;
  pos = input.find(delimiter);
  int order_des  = 0;
  string des = input.substr(0,pos);
  string source = input.substr(pos+2,input.length()-1);
  for (int i = 0 ; i<15; i++ ) {
          if (addr->labels[i] == des )
          {
            x = addr->compare_check[i];
            order_des = i;
            break;
          }
      }
  if (source == "true") { y = true;} 
  else if (source == "false") { y= false;}
  else {
      for (int i = 0; i<15; i++) 
      {
          if (addr->labels[i] == source)
          {
            y = addr->compare_check[i];
            break;
            };
      }
  }
  if (x) {
    x = x||y;
    addr->compare_check[order_des] = x;}
  else {
    throw(TypeMismatch(checker->ip));
    destroy_all();
    exit(0);
  }
  
}
void VM::action_jumpif(string input) {
  size_t pos = 0;
  string delimiter = ",";
  int vt;
  pos = input.find(delimiter);
  string des = input.substr(0,pos);
  string source = input.substr(pos+2,input.length()-1);

  for (int i = 0; i <15; i++)
  {
    if (addr->labels[i] == des)
    {
      vt = i;
      break;
      }
    }
  if (addr->compare_check[vt] == true) {
      int x = stoi(source);
      if ( x > checker->num_ip) { 
        
        throw (InvalidDestination(checker->ip));
        destroy_all();
     }
      else {
        checker->ip = x;
        execute_register(x);
      }     
}
}
void VM::action_jump(string input) {
    int x = stoi(input);
      if ( x > checker->num_ip) { 
        
        throw (InvalidDestination(checker->ip));
        destroy_all();
     }
      else {
        checker->ip = x;
        execute_register(x);
}
}

void VM::action_CmpEQ(string input) {
  size_t pos = 0;
  string delimiter = ",";
  string temp;
  pos = input.find(delimiter);
  string des = input.substr(0,pos);
  string source = input.substr(pos+2,input.length()-1);
  int pos1,pos2 = 0;
  bool ok = false;
  for (int i = 0; i <15; i++)
  {
    if (addr->labels[i] == des || addr->value[i]==des) 
    {
        pos1=i;
        break;
    }
  }
  for (int i = 0; i <15; i++)
  {
    if (addr->labels[i] == source || addr->value[i]==source)
    {
        pos2=i;
        ok = true;
        break;
    } 
  }
  if (ok== true)
      if (stod(addr->value[pos1]) == stod(addr->value[pos2]))
        addr->compare_check[pos1] = true;
      else {
        addr->compare_check[pos1] = false;
      }
  else {
    if (stod(addr->value[pos1]) == stod(source))
       addr->compare_check[pos1] = true;
    else {
        addr->compare_check[pos1] = false;
    }
  }
}
void VM::action_CmpNE(string input) {
  size_t pos = 0;
  string delimiter = ",";
  string temp;
  pos = input.find(delimiter);
  int pos1, pos2  = 0;
  bool ok =false;
  string des = input.substr(0,pos);
  string source = input.substr(pos+2,input.length()-1);
  for (int i = 0; i <15; i++)
  {
    if (addr->labels[i] == des || addr->value[i]==des) 
    {
        pos1=i;
        break;
    }
  }
  for (int i = 0; i <15; i++)
  {
    if (addr->labels[i] == source || addr->value[i]==source)
    {
        pos2=i;
        ok = true;
        break;
    } 
  }
  if (ok== true )
      if (stod(addr->value[pos1]) != stod(addr->value[pos2]))
        addr->compare_check[pos1] = true;
      else {
        addr->compare_check[pos1] = false;
      }
  else {
    if (stod(addr->value[pos1]) != stod(source))
       addr->compare_check[pos1] = true;
    else {
        addr->compare_check[pos1] = false;
    }
  }
}
void VM::action_CmpLT(string input) {
 size_t pos = 0;
  string delimiter = ",";
  string temp;
  pos = input.find(delimiter);
  string des = input.substr(0,pos);
  string source = input.substr(pos+2,input.length()-1);
  int pos1,pos2 = 0;
  bool ok = false;
  for (int i = 0; i <15; i++)
  {
    if (addr->labels[i] == des || addr->value[i]==des) 
    {
        pos1=i;
        break;
    }
  }
  for (int i = 0; i <15; i++)
  {
    if (addr->labels[i] == source || addr->value[i]==source)
    {
        pos2=i;
        ok = true;
        break;
    } 
  }
  if (ok== true)
      if (stod(addr->value[pos1]) < stod(addr->value[pos2]))
        addr->compare_check[pos1] = true;
      else {
        addr->compare_check[pos1] = false;
      }
  else {
    if (stod(addr->value[pos1]) < stod(source) )
       addr->compare_check[pos1] = true;
    else {
        addr->compare_check[pos1] = false;
    }
  }
}
void VM::action_CmpLE(string input) {
 size_t pos = 0;
  string delimiter = ",";
  string temp;
  pos = input.find(delimiter);
  string des = input.substr(0,pos);
  string source = input.substr(pos+2,input.length()-1);
  int pos1,pos2 = 0;
  bool ok = false;
  for (int i = 0; i <15; i++)
  {
    if (addr->labels[i] == des || addr->value[i]==des) 
    {
        pos1=i;
        break;
    }
  }
  for (int i = 0; i <15; i++)
  {
    if (addr->labels[i] == source || addr->value[i]==source)
    {
        pos2=i;
        ok = true;
        break;
    } 
  }
  if (ok== true)
      if (stod(addr->value[pos1]) <= stod(addr->value[pos2]))
        addr->compare_check[pos1] = true;
      else {
        addr->compare_check[pos1] = false;
      }
  else {
    if (stod(addr->value[pos1]) <= stod(source) )
       addr->compare_check[pos1] = true;
    else {
        addr->compare_check[pos1] = false;
    }
  }
}
void VM::action_CmpGT(string input) {
 size_t pos = 0;
  string delimiter = ",";
  string temp;
  pos = input.find(delimiter);
  string des = input.substr(0,pos);
  string source = input.substr(pos+2,input.length()-1);
  int pos1,pos2 = 0;
  bool ok = false;
  for (int i = 0; i <15; i++)
  {
    if (addr->labels[i] == des || addr->value[i]==des) 
    {
        pos1=i;
        break;
    }
  }
  for (int i = 0; i <15; i++)
  {
    if (addr->labels[i] == source || addr->value[i]==source)
    {
        pos2=i;
        ok = true;
        break;
    } 
  }
  if (ok== true)
      if (stod(addr->value[pos1]) > stod(addr->value[pos2]))
        addr->compare_check[pos1] = true;
      else {
        addr->compare_check[pos1] = false;
      }
  else {
    if (stod(addr->value[pos1]) > stod(source) )
       addr->compare_check[pos1] = true;
    else {
        addr->compare_check[pos1] = false;
    }
  }
}
void VM::action_CmpGE(string input) {
 size_t pos = 0;
  string delimiter = ",";
  string temp;
  pos = input.find(delimiter);
  string des = input.substr(0,pos);
  string source = input.substr(pos+2,input.length()-1);
  int pos1,pos2 = 0;
  bool ok = false;
  for (int i = 0; i <15; i++)
  {
    if (addr->labels[i] == des || addr->value[i]==des) 
    {
        pos1=i;
        break;
    }
  }
  for (int i = 0; i <15; i++)
  {
    if (addr->labels[i] == source || addr->value[i]==source)
    {
        pos2=i;
        ok = true;
        break;
    } 
  }
  if (ok== true)
      if (stod(addr->value[pos1]) >= stod(addr->value[pos2]))
        addr->compare_check[pos1] = true;
      else {
        addr->compare_check[pos1] = false;
      }
  else {
    if (stod(addr->value[pos1]) >= stod(source) )
       addr->compare_check[pos1] = true;
    else {
        addr->compare_check[pos1] = false;
    }
  }
}
void VM::action_store(string input) {
  size_t pos = 0;
  string delimiter = ",";
  pos = input.find(delimiter);
  int order_des  = 0;
  string vt,value;
  string des = input.substr(0,pos);
  string source = input.substr(pos+2, input.length()-1);
  for (int i=0; i<15; i++)
    {
      if (addr->labels[i] == source) {
          vt = addr->id[i];
          value = addr->value[i];
          break;
      }
      else {
        value = source;
        break;
      }
    }
  for (int i=0; i<15; i++){
    if (addr->labels[i] == des){
      {order_des = i;
      break;}
    }
  }
  if (addr->id[order_des]!=""){
      addr->value[order_des] = value;
  }
  else {
    throw(TypeMismatch(checker->ip));
    destroy_all();
    exit(1);
  }
  
 
  //cout<<order_des<<endl;
    
}
void VM::action_load (string input) {
  size_t pos = 0;
  string delimiter = ",";
  string temp;
  pos = input.find(delimiter);
  string des = input.substr(0,pos);
  string source = input.substr(pos+2,input.length()-1);
  string vt,value;
  for (int i = 0; i<15; i++)
  { 
    if (addr->labels[i] == source) {
      vt = addr->id[i];
      value = addr->value[i];
  }
  }
  for (int i = 0; i<15; i++) {
    if (des == addr->labels[i]) {
      addr->value[i] = value;
      addr->id[i] = vt;
  }
 }
  }
void VM::action_output(string input) {

  bool ok = true;
  int order_des=0;
  for (int i=0; i<15; i++)
  {
    if (addr-> labels[i] == input)
    {
      order_des  = i;
      ok = false;
      break;
    }
  }
  if (ok == true) { cout <<input;}
  else 
    {cout<<addr->value[order_des];}
}
void VM:: action_move(string input) {
  size_t pos = 0;
  string delimiter = ",";
  pos = input.find(delimiter);
  int order_des  = 0;
  string des = input.substr(0,pos);
  for (int i=0; i<15; i++)
  {
    if (addr-> labels[i] == des ) {
      order_des  = i;
    }
  }
  
  if (input[input.length()-1] == 'A') {
      string temp = input.substr(pos+2,input.length()-1);
      addr->id[order_des] = temp;
      addr->value[order_des] = addr->value[order_des];
  } 
  else {
    string source = input.substr(pos+2,input.length()-1);
    int  order_source = 0;
    for (int i=0; i<15; i++)
    {
      if (addr-> labels[i] == source ) {
        order_source  = i;
        addr->value[order_des] =addr->value[order_source];
        break;
      }
      else {
        addr->value[order_des] = source;
        break;
    }
  }
  }
};
void VM::action_add(string input){

  size_t pos = 0;
  string delimiter = ",";
  pos = input.find(delimiter);
  string a,b;
  int order_des,j = 0;
  bool ok= false;
  double x;
  string des = input.substr(0,pos);
  string source = input.substr(pos+2, input.length()-1);

  for (int i = 0; i<15; i++)
  { 
    if (des == addr->labels[i]) {
      a = addr->value[i];
      order_des=i;
      break;
    }
  }
  while (j<15){
    if (addr->labels[j] == source) {
      b = addr->value[j];
      ok = true;
      break;
    }
    else j++;
  }
  if (ok == false) {
    b = source;
  }
  x = stod(a) + stod(b);
  stringstream ss;
  ss << x;
  string str = ss.str();
  addr->value[order_des] = str;
}
void VM::action_minus(string input){
  size_t pos = 0;
  string delimiter = ",";
  pos = input.find(delimiter);
  double a,b;
  bool ok = false;
  int order_des,j=0;
  string des = input.substr(0,pos);
  string source = input.substr(pos+2, input.length()-1);
  for (int i = 0; i<15; i++)
  { 
    if (des == addr->labels[i]) {
      a = stod(addr->value[i]);
      order_des=i;
      break;
    }
  }

  while (j<15){
    if (addr->labels[j] == source) {
      b = stod(addr->value[j]);
      ok = true;
      break;
    }
    else j++;
  }
  if (ok == false) {
    b = stod(source);
  }
  a = a-b;
  stringstream ss;
  ss << a;
  string str = ss.str();
  addr->value[order_des] = str;
}
//
void VM::action_mul(string input){
  size_t pos = 0;
  string delimiter = ",";
  pos = input.find(delimiter);
  double a,b=1;
  int j = 0;
  int order_des;
  bool ok = false;
  string des = input.substr(0,pos);
  string source = input.substr(pos+2, input.length()-1);
  for (int i = 0; i<15; i++)
  { 
    if (des == addr->labels[i]) {
      a = stod(addr->value[i]);
      order_des = i;
      break;
    }
  }

  while (j<15){
    if (addr->labels[j] == source) {
      b = stod(addr->value[j]);
      ok = true;
      break;
    }
    else j++;
    }
    if (ok == false) {
      b = stod(source);
  }
  a = a*b;
  stringstream ss;
  ss << a;
  string str = ss.str();
  addr->value[order_des] = str;
}
void VM::action_div(string input){
  size_t pos = 0;
  string delimiter = ",";
  pos = input.find(delimiter);
  double a,b  = 1;
  int j = 0;
  int order_des;
  bool ok = false;
  string des = input.substr(0,pos);
  string source = input.substr(pos+2, input.length()-1);
  for (int i = 0; i<15; i++)
  { 
    if (des == addr->labels[i]) {
      a = stod(addr->value[i]);
      order_des=i;
      break;
    }
  }

  while (j<15){
    if (addr->labels[j] == source) {
      b = stod(addr->value[j]);
      ok = true;
      break;
    }
    else j++;
  }
  if (ok == false) {
    b = stod(source);
  }
  if (b == 0 || b == 0.0) {
    
    throw(DivideByZero(checker->ip));
    destroy_all();
  }
  a = a/b;
  stringstream ss;
  ss << a;
  string str = ss.str();
  addr->value[order_des] = str;
  
}
void VM::action_halt() {
  if (running == false) {
    destroy_all();
  exit(0);
}
}
