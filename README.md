# Paralegrep

O comando **grep** é usado em ambientes UNIX para encontrar
padrões em arquivos. Por exemplo:
<p align="center">
**grep “sistemas” arquivo1.txt**
</p>
Retorna todas as ocorrências do termo “sistemas” em linhas do arquivo1.txt. Este comando se torna bastante útil quando temos uma coleção de arquivos de texto em uma pasta e precisamos encontrar alguma informação a partir de uma dada ocorrência de um determinado termo. Por exemplo:
<p align="center">
**grep “sistemas” *.txt**
</p>
Retorna todas as ocorrências de “sistemas” em linhas de todos os arquivos .txt da pasta corrente. Caso esteja fazendo uma pesquisa de quantas ocorrências de um termo ocorre em um dado arquivo (ou conjuntos de arquivos), basta adicionar o argumento -c (count) no grep

### Especificações do sistema paralegrep

O sistema paralegrep recebe como argumento de entrada uma palavra de interesse (sem espaços e apenas letras). Exemplo de chamada do sistema paralegrep via terminal:
<p align="center">
**./paralegrep sistemas**
</p>
Ao iniciar o sistema paralegrep, este deve verificar quantas ocorrências do termo “sistemas” (ou outro termo definido pelo usuário) aparece em cada arquivo do diretório “fileset” que se encontra dentro do
diretório corrente (que possui o programa ./paralegrep).

Além disso, deve-se imprimir na saída padrão (stdout) um ranking mostrando o top 10 arquivos com mais ocorrências do termo definido pelo usuário.

O programa deve permanecer em execução, pois, caso algum arquivo seja alterado ou incluído no diretório fileset, o ranking de quantidade de termos encontrados em cada arquivo deve ser atualizado.

Para fazer este sistema, deve-se usar 3 tipos de threads:
- Thread despachante;
- Threads operárias;
- Thread ranking.

A seguir são descritos as características e funcionalidades de cada tipo de thread.

#### Thread Despachante
- Deve monitorar o diretório "fileset" que deve estar armazenado dentro do diretório corrente;
 -  A cada 5 segundos o thread despachante deve verificar se houve alterações ou inclusões de arquivos no diretório;

- Caso haja novos arquivos ou arquivos alterados, deve, para
cada um desses arquivos, “acordar” alguma de suas 10 threads operárias e pedir a ela que conte quantas ocorrências do termo definido pelo usuário existem nestes
arquivos;
 - Caso todas as threads operárias estejam trabalhando, deve-se esperar até que uma thread operária esteja disponível.

#### Threads Operárias
- Recebem um arquivo da thread despachante e devem contar quantas ocorrências do termo definido pelo usuário existem neste arquivo;

- O resultado deve ser enviado junto com o nome de arquivo à thread ranking (por exemplo,  pode-se definir uma estrutura de dados que recebe este dado, sendo que esta estrutura de dados é monitorada pela thread ranking);

- Caso alguma thread operária não esteja trabalhando, esta deve ceder a sua vez (ou seja, não deve ficar em espera ocupada).

#### Thread Ranking
- Recebem das threads operárias a quantidade de ocorrências do termo definido pelo usuário;

- Após receber um novo dado, esta deve atualizar o ranking e imprimir em tela o atual top 10 de arquivos com mais ocorrências de um dado termo.


## Compilando
Pare compilar esse software é necessário o C++11 ou superior, e um sistema com base Linux.

##### Instalando G++ no Ubuntu:

------------
	sudo apt install g++

##### Compilando o Paralegrep
	g++ -pthread main.cpp -o parelegrep

##### Executando
	./paralegrep *palavradabusca*

## Alimentando Arquivos para Busca
para alimentar arquivos de busca, basta adicionar arquivos com extenção **".txt"** dentro da pasta fileset




## Desenvolvedores
[Luiz Gustavo Benicio Neves](http://github.com/LouisRiverstone "Luiz Gustavo Benicio Neves")
[Leonardo Soares Bastos](http://github.com/LeoSBastos "Leonardo Soares Bastos")
[Eloy Guimarães](https://github.com/Eloy31 "Eloy Guimarães")

Para a matéria de **Sistemas Operacionais** , Prof João Victor de A. Oliveira do Instituto Federal De Brasília - *Campus*  Taguatinga, ABI - Computação