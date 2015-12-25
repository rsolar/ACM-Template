//G++
void Main() {

}
int main() {
  int sz = 256 << 20; //256Mb
  char *p = (char *)malloc(sz) + sz;
  //Windows
  __asm__ __volatile__("movl %0, %%esp\n" "pushl $_exit\n" :: "r"(p));
  //Linux
  //__asm__ __volatile__("movq %0, %%rsp\n" "pushq $exit\n" :: "r"(p));
  Main();
  exit(0);
}
//VC++
#pragma comment(linker, "/STACK:1024000000,1024000000")
