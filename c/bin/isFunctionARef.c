#include <stdio.h>

void* dummyFunc();

void fun() {
  printf("FUN");
}

int main(int argc, char** argv) {
  printf("Function by val: %p\n", fun); 
  printf("Function by ref: %p\n", &fun);

  printf("DummyFunc by val: %p\n", dummyFunc);
  printf("DummyFunc by ref: %p\n", &dummyFunc);
}

void* dummyFunc() {

}
