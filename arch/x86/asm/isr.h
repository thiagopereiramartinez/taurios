/* Está é uma função muito repetitiva... não é difícil, é
*  somente aborrecedor. Como você pode ver, nós atribuímos as 32 entradas
*  na IDT para as primeiras 32 ISRs. Nós não podemos usar um laço for
*  para este, porque não a caminho de se obter os nomes das funções
*  que correspondem para cada entrada. Nós atribuímos as flags de
*  entrada para 0x8E. Fazer que a entrada esteja presente, está
*  rodando em ring 0 (nível kernel), e que os 5 bits inferiores
*  estejam atribuídos para o requerido '14', que é representado por 'E' 
*  em hexadecimal. */
void isr_install();

/* Todas nossas exceções tratadas pelas Rotinas de Serviço de Interrupção vão
*  apontar para esta função. Este vai nos dizer qual exceção tem
*  ocorrido! Diretamente agora, nós simplesmente vamos parar o sistema pelo usando um
*  laço sem fim. Todas ISRs desabilitam interrupções enquanto estes estão sendo
*  servidos como um mecanismo de 'tranca' para prevenir que um IRQ
*  ocorra e perdendo as estruturas de dados do kernel */
void fault_handler(struct regs *r);

