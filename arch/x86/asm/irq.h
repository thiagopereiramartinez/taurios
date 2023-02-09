/* Este instala um tratador de IRQ de costume para um IRQ dado */
//void irq_install_handler(int irq, void (*handler)(struct regs *r));

#include <include/regs.h>

/* Este limpa o tratador para um IRQ dado */
void irq_uninstall_handler(int irq);

/* Normalmente, IRQs 0 até 7 são mapeados para as entradas 8 até 15. Este
*  é um problema no modo protegido, porque a entrada IDT 8 é uma
*  Double Fault! Sem remapeamento, a todo tempo que o IRQ0 dispara,
*  você obterá uma Exceção Double Fault, que NÃO é realmente
*  o que queremos. Nós enviamos para o Controle Programável de
*  Interrupções (PICs - também chamado de 8259's) o comando
*  para fazer IRQ0 até 15 ser remapeado para as entradas IDT 32 até
*  47 */
void irq_remap(void);

/* Nós primeiramente remapeamos o controle de interrupções, e então instalamos
*  os ISRs apropriados para as entradas corretas na IDT. Este é justamente
*  parecido com a instalação dos tratamentos de exceções */
void irq_install();

/* irq_enabled */
int irq_enabled(void);

/* irq_install_handler */
void irq_install_handler(int irq, void (*handler)(struct regs *r));
