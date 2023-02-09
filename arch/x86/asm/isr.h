/* Est� � uma fun��o muito repetitiva... n�o � dif�cil, �
*  somente aborrecedor. Como voc� pode ver, n�s atribu�mos as 32 entradas
*  na IDT para as primeiras 32 ISRs. N�s n�o podemos usar um la�o for
*  para este, porque n�o a caminho de se obter os nomes das fun��es
*  que correspondem para cada entrada. N�s atribu�mos as flags de
*  entrada para 0x8E. Fazer que a entrada esteja presente, est�
*  rodando em ring 0 (n�vel kernel), e que os 5 bits inferiores
*  estejam atribu�dos para o requerido '14', que � representado por 'E' 
*  em hexadecimal. */
void isr_install();

/* Todas nossas exce��es tratadas pelas Rotinas de Servi�o de Interrup��o v�o
*  apontar para esta fun��o. Este vai nos dizer qual exce��o tem
*  ocorrido! Diretamente agora, n�s simplesmente vamos parar o sistema pelo usando um
*  la�o sem fim. Todas ISRs desabilitam interrup��es enquanto estes est�o sendo
*  servidos como um mecanismo de 'tranca' para prevenir que um IRQ
*  ocorra e perdendo as estruturas de dados do kernel */
void fault_handler(struct regs *r);

