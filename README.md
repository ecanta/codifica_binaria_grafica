<h1>Codifica Binaria Visiva</h1>

Questo programma converte una stringa di testo in una rappresentazione binaria visiva, utilizzando pixel verdi (1) e bianchi (0),
ed esporta i dati sia come **bitstream**, sia in **formato esadecimale**.
È possibile anche invertire il processo, decodificando la stringa da esadecimale per rigenerare l'immagine originale.

<h2>Funzionalità</h2>

+ Conversione da **stringa di testo** a:
  + **Bitstream** (0 e 1)
  + **Immagine binaria** (rappresentata cambiando il colore di sfondo di ogni pixel)
  + **Stringa esadecimale**
+ Ricostruzione dell'immagine a partire da una stringa esadecimale
+ Funziona anche su terminali che non supportano ANSI, in questo caso l'immagine è rappresentata con **caratteri ASCII**

<h2>Esempio di utilizzo</h2>

Inserendo la stringa `windows`, si ottiene l'immagine

```
O   O  OOOOO  O   O  OOOO    OOO   O   O   OOOO 
O   O    O    OO  O  O   O  O   O  O   O  O     
O O O    O    O O O  O   O  O   O  O O O   OOO  
OO OO    O    O  OO  O   O  O   O  OO OO      O 
O   O  OOOOO  O   O  OOOO    OOO   O   O  OOOO  
```

Il bitstream è `100010111110100010111100011100100010011110100010001000110010100010100010100010100000101010001000101010100010100010101010011100110110001000100110100010100010110110000010100010111110100010111100011100100010111100`

L'esadecimale ottenuto è **`/22fa2f1c89e888ca28a282a22a8a2a9cd889a28b60a2fa2f1c8bc/`**

Questo esadecimale può essere reinserito nel programma per decodificarlo in immagine (le due barre a inizio e fine sono
**fondamentali** per far sì che il programma riconosca l'esadecimale)

