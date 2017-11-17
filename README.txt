Membros do grupo:
	Igor Fratel Santana 9793565
	Renan Costa Laíz 9779089
	Renan Tiago dos Santos Silva 9793606

--------------------------------------------------------------------------------------------------------------------------------------------------------------------
PRIMEIRA FASE:
Detalhes importantes:
 >No comando SAVE, o novo rbp vai apontar para a posição da pilha onde o antigo rbp está guardado (topo - 1)
 >A ordem esperada de comandos rotineiros para chamar uma função com variáveis locais seria: CALL -> SAVE -> ALC -> FRE -> REST -> RET
 	*No entanto, como a função fatorial recursiva passada para nós como teste não utiliza os comandos SAVE e REST, incluímos o SAVE no CALL e o REST no RET.
 	*Portanto, a ordem fica CALL -> ALC -> FRE -> RET.
 >Estavamos usando o numero de intruções a serem executadas pela maquina virtual como o numero de instruções no programa recebido. Isso não é o suficiente para
  programas com loop, portanto fixamos o número 100000

Como executar:
	python montador < programa.txt > motor.c
	make
	./motor
--------------------------------------------------------------------------------------------------------------------------------------------------------------------



SEGUNDA FASE:

Nosso programa ainda não está executável. Apenas escrevemos as funções pedidas e pretendemos organizar tudo até a terceira fase.

*gerador_terreno.c:
	programa criado com o intuito de inicializar os atributos da arena, de forma randômica, especificando localização das bases dos exércitos, dos repositórios de cristais (e quantidade de cada repositório), de cada robô e do tipo de terreno que cada célula deve ter.

O mapa é inicializado a partir de um arquivo gerado pelo gerador_terreno.c, mas as posições dos robôs são aleatórias