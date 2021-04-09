#include "VM.h"
#include "VM.cpp"
using namespace std;

void test(string filename) {
   
        VM *vm = new VM();
        try {
            vm->run(filename);
        }
        catch (exception& e) {
            cout << e.what();
        }
        delete vm;
}

int main(int argc, char **argv)
{
  test("C:/Booh/HCMUT/Sem 202/DSA/Asm1/initial/testcase/prog21.txt");

  return 0;
}