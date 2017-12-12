Simple HTTP Server written in C language

This piece of program was developed as an assignment from the Computer networks 
programming course 2013 class at the Institute of mathematics and statistics from 
the University of São Paulo.

Developed by:<br>
André Mesquita Pereira<br>
Renato Scaroni<br>

- File organization:<br>
.src/http_main.c - a main file based on modified given sample code<br>
.src/http_methods.c - implementation of HTTP request methods (GET, POST, OPTIONS), and auxialiary methods<br>
.src/http_methods.h - Header header file for 'http_main.c'<br>
.trace/ - test trace directory<br>
.makefile - Make file<br>
.test.html - test file<br>
.test2.html - test file<br>
.test2.png - test file<br>
.test_post.html - test file<br>

- Compiling<br>
$ make<br>
$ make clean<br>

- Running server<br>
$ ./http_server {porta}

---------------------------------------------------------------------------------------------------------------------------

Servidor HTTP simples desenvolvido em linguagem C

Este programa foi entregue como parte do critério de avaliação da 
disciplina MAC448 - programação para redes de computadores do curso
de ciência da computação do IME-USP ministrada no segundo semestre de 2013

Desenvolvido por:<br>
André Mesquita Pereira<br>
Renato Scaroni<br>

- Organização de arquivos:<br>
.src/http_main.c - Uma versão modificada do código de exemplo fornecido<br>
.src/http_methods.c - Métodos para tratar as requisições (GET, POST, OPTIONS), além de métodos auxiliares<br>
.src/http_methods.h - Header com imports, defines e definições dos métodos utilizados no arquivo 'http_main.c'<br>
.trace/ - Diretório com traces para teste<br>
.makefile - Make padrão<br>
.test.html - Arquivo de teste<br>
.test2.html - Arquivo de teste<br>
.test2.png - Arquivo de teste<br>
.test_post.html - Arquivo de teste<br>

- Compilação<br>
$ make<br>
$ make clean<br>

- Execução<br>
$ ./http_server {porta}
