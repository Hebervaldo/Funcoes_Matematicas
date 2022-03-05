#!/bin/bash

usuario="Hebervaldo"
token="$(`cat /home/usuario/Documentos/git/$usuario/Token_Git_Hebervaldo.txt`)"
nome_repositorio="Funcoes_Matematicas"

for n in *.c
do
	git add $n
done

for n in *.sh
do
	git add $n
done

git commit -m "Funcoes_Matematicas: Enviando arquivos atualizados *.c"
git push https://$token@github.com/$usuario/$nome_repositorio.git
