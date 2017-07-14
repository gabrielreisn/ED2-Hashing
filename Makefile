#MakeFile

#make all
all:
	 gcc -o imprimeHash imprimeHash.c hash.h -std=c11 -w
	 gcc -o buscaHash   buscaHash.c hash.h -std=c11 -w
	 gcc -o imprimeArvore imprimeArvore.c arvore.h -std=c11 -w
	 gcc -o buscaArvore buscaArvore.c arvore.h -std=c11 -w

#make run_indice_arvore
run_indice_arvore:
	 make && ./imprimeArvore keys text
#make run_indice_hash
run_indice_hash:
	 make && ./imprimeHash keys text
#make run_busca_arvore
run_busca_arvore:
	 make && ./buscaHash keys text	
#make run_busca_hash
run_busca_hash:
	 make && ./buscaHash keys text
#make clean
clean: 
	rm *.o
