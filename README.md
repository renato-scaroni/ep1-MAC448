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
