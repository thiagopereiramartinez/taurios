/* Este instala um tratador de IRQ de costume para um IRQ dado */
//void irq_install_handler(int irq, void (*handler)(struct regs *r));

#include <include/regs.h>

/* Este limpa o tratador para um IRQ dado */
void irq_uninstall_handler(int irq);

/* Normalmente, IRQs 0 at� 7 s�o mapeados para as entradas 8 at� 15. Este
*  � um problema no modo protegido, porque a entrada IDT 8 � uma
*  Double Fault! Sem remapeamento, a todo tempo que o IRQ0 dispara,
*  voc� obter� uma Exce��o Double Fault, que N�O � realmente
*  o que queremos. N�s enviamos para o Controle Program�vel de
*  Interrup��es (PICs - tamb�m chamado de 8259's) o comando
*  para fazer IRQ0 at� 15 ser remapeado para as entradas IDT 32 at�
*  47 */
void irq_remap(void);

/* N�s primeiramente remapeamos o controle de interrup��es, e ent�o instalamos
*  os ISRs apropriados para as entradas corretas na IDT. Este � justamente
*  parecido com a instala��o dos tratamentos de exce��es */
void irq_install();

/* irq_enabled */
int irq_enabled(void);

/* irq_install_handler */
void irq_install_handler(int irq, void (*handler)(struct regs *r));
