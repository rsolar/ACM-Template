//G++
//Windows
int main2() {

  exit(0);
}
int main() {
  int sz = 256 << 20; //256Mb
  char *p = (char *)malloc(sz) + sz;
  __asm__ __volatile__("movl %0, %%esp\n" "pushl $_exit\n" "call %1\n" :: "r"(p), "r"(main2));
}
//Linux
int main2() {

  exit(0);
}
int main() {
  int sz = 256 << 20; //256Mb
  char *p = (char *)malloc(sz) + sz;
  __asm__ __volatile__("movq %0, %%rsp\n" "pushq $exit\n" "call %1\n" :: "r"(p), "r"(main2));
}

//VC++
#pragma comment(linker, "/STACK:1024000000,1024000000")
