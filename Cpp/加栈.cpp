//G++
void Main() {

}
int main() {
  int sz = 100 << 20; //100MB
  char *p = (char *)malloc(sz) + sz;
  __asm__ __volatile__(
#if __x86_64__ || __ppc64__ || _WIN64 //64-bit
    "movq %0, %%rsp\n pushq $_exit\n"
#else //32-bit
    "movl %0, %%esp\n pushl $_exit\n"
#endif
    :: "r"(p));
  Main();
  exit(0);
}
//VC++ 100MB
#pragma comment(linker, "/STACK:102400000,102400000")
