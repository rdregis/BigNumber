Esta solution tem por finalidade o calculo de operacoes matematicas em numeros cuja a quantidade de digitos nao tem limites, podendo ser muito grandes (exemplo numeros na ordem de 50 ou mais digitos).

Para a execucao dos calculos eles devem ser informados utilizando a notacao infix, possibilitando o encadeamento de complexas expressoes matematicas, atraves do uso de parenteses, determinando a prioridades das operacoes 

As seguintes operacoes sao suportadas:
[+] Adicao
[-] Subtracao
[*] Multiplicacao
[/] Divisao
[%] Divisao modular 

Ha duas formas de execucao destes calculos

1 Forma

Utiliza-se o script Run_BNCalculator.bat o qual ira utilizar um arquivo de entrada (DataCalculator.txt) que deve conter as expressoes matematica. Esse arquivo sera lido pelo BNCalculatorClient.exe e enviado ao BNCalculatorServer.exe que calcula o valor das expressoes e retorna o resultado ao BNCalculatorClient.exe que gravara esse resutado no arquivo de saida (DataCalculatorOut.txt), no seguinte formato:
[sss.mmm.uuu];<expressao>=<resultado>;

2 Forma

Usando a interface grafica UIBigNumber.exe, que utiliza a estrutura da Forma 1 sem a necessidade de arquivos, pode-se digitar a expressao desejada e clicar no botao correspondente para que seja calculado o seu valor.
Deve-se primeiramente executar o server, e antes de comecar os calculos deve se conectar a ele.

Consideracoes:
- A primeira vez que se executar o script Run_BNCalculator.bat ele automaticamente compilara a solution.
- Todos os parametros para execucao acima descritos podem ser alterados no script de execucao ou na interface grafica
- Testes unitarios sao executados sempre que o Run_BNCalculator.bat for executados
- Ao final da execucao do script Run_BNCalculator.bat ele irar mostrar o conteudo do arquivo de saida.

Caracteristicas adicionais
- Testes unitarios
- Interface grafica escrito em C++
- Implementacao do operador de divisao modular
- Script de compilacao e execucao

Projetos da solution
- BigNumber: Todo algoritimo de calculo das expressoes mtematicas usando Big Number
- BNCalculatorClient: Rotina de leitura, envio e recepcao de mensagens ao server e gravacao do resultado em arquivo
- BNCalculatorServer: Rotina para receber as expressoes e enviar o resultado ao client, bem como operacionando o calculo
- GoogleTest: Famework da Google para realizacao de testes unitarios
- Network: Todo algoritmo efetuar a conexao e troca de mensagens entre o client e o server
- TestBigNumber: Descricao e execucao dos testes unitarios (para o projeto BigNumber)
- UIBigNumber: Formulario grafico para a descricao e envio das expressoes ao server e o seu retorno. 

BIgNumber Class
- BigNumber: Rotina de tratamento de string contida que forma um big number
- MathBigNumber: Rotina par tratamento de numero matematico no formato de big number
- BNOperatorMath<MOperator> ...: Algoritimo de calculo de operacoes matematicas
- BNExecutor: Rotina para coordenar a execucao das operacoes matematicas 
- BNNotationMath: Algoritimo para fazer o parse das expressoes e converte-los para notacao postfix
- 