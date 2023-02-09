/* Este define qual pilha estamos olhando depois de um ISR estar rodando */
struct regs
{
    unsigned int ds, es, fs, gs;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;    
};

