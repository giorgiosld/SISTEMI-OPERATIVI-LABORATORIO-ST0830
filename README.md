# SISTEMI-OPERATIVI-LABORATORIO-ST0830
Progetto relativo al corso di Sistemi Operativi Laboratorio del corso di laurea in Informatica (L-31) all'Università di Camerino.
## SPECIFICA
L’obiettivo del progetto è sviluppare una semplice applicazione che consenta di cifrare file utilizzando una variante del Cifrario di Vernam, qui denominato bvernam. L’algoritmo proposto sfrutta una semplice proprietà dell’operatore binario XOR:

`(A XOR B) XOR B = A`

Data una sequenza di k-byte b0...bk-1 (detta chiave) la funzione di codifica di una sequenza di byte d0...dN la funzione di codifica/decodifica segue il seguente semplice procedimento. 

La sequenza d0...dN  viene per prima cosa suddivisa in Nk blocchi (divisione intera), D0,...,DNk-1 ognuno dei quali consiste di esattamente k byte (a parte l’ultima sequenza che, ovviamente, potrà contenere un numero inferiore di byte).

Successivamente ogni sequenza Dj=dj,0...dj,k-1viene trasformata nella sequenza D'j=d'j,0...d'j,k-1tale che per ogni i:

`d'j,i=b(j+i) mod k XOR dj,i`

Ossia il byte in posizione i del blocco j viene messo in XOR con il byte (j+i) mod k della chiave.

La sequenza di output verrà quindi ottenuta dalla giustapposizione delle sequenze D'0,...,D'Nk-1.
## ESECUZIONE
Sviluppare l’applicazione `bvernan` che riceve come parametri:
Il file usato come chiave (keyfile);
Il file da elaborare (inputfile);
Il file di output (outputfile).

Invocato con il seguenti parametri:

`bvernam keyfile inputfile outputfile`
## TEST
Uno script python è disponibile per testare il programma con differenti esempi. Lo script, chiamato `bvernamtest.py`, può essere trovato nella cartella `test`.
Per eseguire lo script usare il seguente comando:
`python3 bvernamtest.py`
