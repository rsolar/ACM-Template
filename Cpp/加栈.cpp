//G++
//ver.1
int sz = 256 << 20; //256MB
char *p = (char *)malloc(sz) + sz;
__asm__("movl %0, %%esp\n" :: "r"(p));

//ver.2
__asm__("movl %%esp, (%%eax);\n"::"a"(my_stack):"memory");
__asm__("movl %%eax, %%esp;\n"::"a"(my_stack + sizeof(my_stack) - main_stack):"%esp");
MAIN();
__asm__("movl (%%eax), %%esp;\n"::"a"(my_stack):"%esp");


//VS C++
#pragma comment(linker, "/STACK:1024000000,1024000000")
