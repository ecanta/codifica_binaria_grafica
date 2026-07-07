<h1>Codifica Binaria Visiva</h1>

Questo programma converte una stringa di testo in una rappresentazione binaria visiva, utilizzando pixel colorati (accesi) e pixel di sfondo (spenti),
ed esporta i dati sia come **bitstream**, sia in **formato esadecimale**.
È possibile anche invertire il processo, decodificando una stringa esadecimale per rigenerare l'immagine originale.

Oltre alla semplice codifica automatica del testo, il programma offre un'**interfaccia di disegno pixel per pixel**, con supporto
a scorciatoie personalizzate, alias da tastiera, strumenti di disegno ed esportazione/importazione dei dati.

<h2>Requisiti</h2>

Il programma è scritto per **console Windows** e fa uso di API specifiche (`Windows.h`, `conio.h`) per gestire input
da tastiera, posizionamento del cursore e colori del testo. Non è quindi multipiattaforma: pur avendo un fallback
grafico in puro ASCII (`O`/`_`) per i terminali che non supportano colori avanzati, richiede comunque un ambiente
Windows per funzionare correttamente.

<h2>Funzionalità</h2>

+ Conversione da **stringa di testo** a:
  + **Bitstream** (0 e 1)
  + **Immagine binaria** (rappresentata cambiando il colore di sfondo di ogni pixel)
  + **Stringa esadecimale**
+ Durante la codifica automatica di una stringa di testo (non tramite disegno manuale), il testo viene sempre
  interpretato **senza distinzione tra maiuscole e minuscole**
+ Se la stringa da codificare contiene un carattere non presente tra quelli supportati, questo viene semplicemente
  rappresentato come uno spazio vuoto nella griglia, senza generare errori
+ Ricostruzione dell'immagine a partire da una stringa esadecimale, con supporto a **decodifiche multiple** quando la dimensione
  della griglia non è specificata (il programma prova tutte le dimensioni compatibili)
+ **Interfaccia di disegno interattiva**, accessibile scrivendo `/` seguito dall'altezza della griglia (un numero primo tra
  `3, 5, 7, 11, 13, 17`), che permette di:
  + Muovere il cursore con **WASD** (con Bloc Maiusc attivo)
  + Colorare/decolorare un pixel con **Spazio**/**Backspace**, oppure invertirlo con **C**
  + Disegnare lettere, numeri e simboli tramite **scorciatoie**, richiamabili sia scrivendo `/nome_scorciatoia` sia premendo
    un tasto alfabetico associato (**alias**)
  + Rimuovere l'ultima scorciatoia inserita con **CTRL+Backspace**
  + Espandere automaticamente la griglia su più righe quando il cursore esce dai limiti del terminale
+ **Comandi da interfaccia** (digitabili con `/`):
  + `/help` — elenca tutti i comandi disponibili
  + `/list_shortcuts` — elenca tutte le scorciatoie salvate
  + `/void` — non fa nulla (utile per annullare un comando digitato per errore)
  + `/clear` — cancella l'intera griglia
  + `/save` — salva la scorciatoia attualmente disegnata
  + `/savemany` — salva più scorciatoie di seguito senza dover ripetere `/save`; si esce con `/resume`
  + `/alias [scorciatoia] [tasto]` — associa a una scorciatoia un tasto alfanumerico
  + `/rename [nome_vecchio] [nome_nuovo]` — rinomina una scorciatoia
  + `/edit [scorciatoia]` — modifica una scorciatoia esistente, aggiornando automaticamente tutte le sue occorrenze nella griglia
  + `/horizontal [lunghezza]` — disegna una linea orizzontale piena
  + `/rubber [lunghezza]` — cancella una linea orizzontale
  + `/erase_col` — rimuove la colonna corrente
  + `/export` — trascrive l'intera griglia (immagine, scorciatoie e loro posizione) in un formato testuale copiabile
  + `/paste [codice]` — carica una griglia esportata in precedenza, ripristinando immagine, scorciatoie e alias
  + `/[scorciatoia] nospace` — usa una scorciatoia senza lasciare lo spazio automatico prima di essa

+ Scorciatoie predefinite per tutte le lettere (A-Z), le cifre (0-9) e i principali simboli (punteggiatura, operatori,
  parentesi angolari, valuta, ecc.), già disegnate su una griglia 5×5 e richiamabili anche solo digitando il carattere
  corrispondente (alias di default)

+ Possibilità di **ridefinire completamente il font di default**: usando `/edit` su una qualsiasi scorciatoia
  predefinita (lettere, cifre, simboli) se ne può ridisegnare la forma da zero, sostituendo così il carattere
  originale con uno personalizzato. Questo permette di creare un intero set di caratteri "custom" mantenendo gli
  stessi alias e nomi, per la massima flessibilità grafica

+ **Adattamento automatico delle scorciatoie**: passando a una dimensione di griglia diversa, tutte le scorciatoie già
  disegnate vengono riscalate automaticamente
+ Uso dei **numeri primi dispari** come dimensioni valide della griglia (`3, 5, 7, 11, 13, 17`, limitati perché una griglia troppo
  alta non entrerebbe comunque nella finestra del terminale): una lunghezza totale di bitstream, se fattorizzata per
  un'altezza prima, dà un'unica scomposizione possibile in righe/colonne, così la decodifica risulta il più possibile
  univoca. Quando la stessa lunghezza è compatibile con più altezze prime candidate, il programma calcola **tutte** le
  decodifiche possibili e le mostra una per una, lasciando all'utente scegliere quella corretta
+ Funziona anche su terminali che non supportano colori ANSI complessi, rappresentando comunque l'immagine con
  caratteri ASCII (`O` per acceso, `_` per spento)

> ⚠️ **Attenzione:** non ridimensionare la finestra del terminale mentre si è in una fase critica del programma
> (in particolare durante l'interfaccia di disegno). Il posizionamento del cursore e della griglia si basa sulle
> dimensioni della console calcolate all'inizio di ogni fase, quindi un ridimensionamento a metà causa disallineamenti
> e un pasticcio visivo sullo schermo.

> ⚠️ **Attenzione:** la finestra della console deve anche essere sufficientemente **alta** per la dimensione di
> griglia scelta: se l'altezza del terminale non è almeno pari a `2 × dimensione + 4` righe, il programma non riesce
> ad avviare l'interfaccia di disegno e segnala un errore. Dimensioni di griglia elevate (come 17) richiedono quindi
> una finestra proporzionalmente più grande.

<h2>Formato di esportazione</h2>

Il comando `/export`, disponibile dall'interfaccia di disegno, produce una stringa nel formato:

```
dim=11&hex=1c1dffdc1dff07f1c1c7ff83bffb83bfe0fe3838fff077ff7877ff7ff7077ffe0e0e0f8ee0ee0ee0ee01c9c1c1f9dc1dc1dc9dfe3bb8383bbb83b83bbb8fe7ff07073f7077077ff0fffbe0e0e3ee0ee0efbe00fe3dffdc3dffdffde3dfff83bffb83bfe0fe383bfe7077ff7077fc1fc7077fc&shortcuts={a/07f0fe7ffe0fffffffffe0fc1f83f07}{b/1ff3fe7ffe0fffffe7ffe0fffffe7fc}{c/07fcfffffe01c0380700e01ffcff9ff}{d/1ff3fe7ffe0fc1f83f07e0fffffe7fc}{e/1ffffffffe01fe3fe7f8e01ffffffff}{f/1ffffffffe01fe3fe7f8e01c0380700}{g/07fcfffffe01c3f8ff0fe0fffcff9ff}{h/1c1f83f07e0fffffffffe0fc1f83f07}{i/1ffffffff0e01c0380700e1ffffffff}{j/007c0f80f00e01c03e07e0fffcfe1fc}{k/1c1f83f0fe39fe3f87f8e39c3f83f07}{l/1c0380700e01c0380700e01ffffffff}{m/1c1f83f8ffbffffbbf27e0fc1f83f07}{n/1c1f83f87f8ff9fbbf3fe3fc3f83f07}{o/07f0fe7ffe0fc1f83f07e0fffcfe1fc}{p/1ff3fe7ffe0fffffe7f8e01c0380700}{q/07f0fe7ffe0fc1f83f0fe3fffcff9ff}{r/1ff3fe7ffe0fffffe7f8ee1ce38e71c}{s/07fcfffffe01fe0fe0ff00fffffe7fc}{t/1ffffffff0e01c0380700e01c038070}{u/1c1f83f07e0fc1f83f07e0fffcfe1fc}{v/1c1f83f07e0fc1f83f8f3b83e038070}{w/1c1f83f07e0fc9fbbffffbfe3f83f07}{x/1c1f83f8f3b83e0380f83b9e3f83f07}{y/1c1f83f8f3b83e0380700e01c038070}{z/1ffffffff0380e0380e0381ffffffff}{0/07f0fe7ffeefddfbbf77eefffcfe1fc}{1/01c0380f03e03c0380700e1ffffffff}{2/07f0fe7ffe0f83c0e0380e1ffffffff}{3/07f0fe7ffe0f8fc3e63fe0fffcfe1fc}{4/1c738e71ce39ffffffff0380700e01c}{5/1ffffffffe01fe3fe7ff00fffffe7fc}{6/07f0fe7f8e01fe3fe7ffe0fffcfe1fc}{7/1ffffffff00e03c0e0380e01c038070}{8/07f0fe7ffe0fffcfe7ffe0fffcfe1fc}{9/07f0fe7ffe0fffcff8ff00e3fcfe1fc}{dot/000000000000000000000000200e01c}{comma/000000000000000000080380e038070}{semicolon/000000008038020000080380e038070}{colon/0000000080380200000803802000000}{dash/0000000000003e0fe0f800000000000}{plus/0000000200e03e0fe0f80e008000000}{sp/0000000000000000000000000000000}{vertical_bar/0700e01c0380700e01c0380700e01c0}{left_angle_bracket/001c0380f0380e03803803803c03807}{equal/0000000f83f83e0000f83f83e000000}{right_angle_bracket/1c0380780380380380e0381e0380700}{exclamation_mark/01c0380700e01c03802000008038070}{question_mark/07f0fe7ffe0f83c0e0380e01c038070}{ampersand/07f0fe7f8e01fe0fe7fce39ffcfb9f7}{pound/07fcff9ff381f83f87e0381ffffffff}{hash/0770ee7fffffffcee7fffffffcee1dc}{percentage/1c1f83e0f0380e0380e0381e0f83f07}{dollar/07fcfffffe39fe0f80f30efffffe7fc}{caret/01c0380f83b9e3f83e0300000000000}{underscore/00000000000000000000001ffffffff}{backslash/1c03807803803803803803803c03807}{forwardslash/001c0380f0380e0380e0381e0380700}&disp={w,0/10/0}{i,11/22/1}{n,23/34/1}{d,35/46/1}{o,47/58/1}{w,59/70/1}{s,71/82/1}
```

Analizzando questo esempio, il codice esportato si divide in quattro parti, separate da `&`:

+ **`dim=11`** — l'altezza della griglia con cui è stata disegnata l'immagine (in questo caso 11 pixel)
+ **`hex=...`** — l'esadecimale dell'intera griglia così come appare visivamente, comprese le scorciatoie già
  posizionate al suo interno
+ **`shortcuts={nome/esadecimale}...`** — l'elenco di tutte le scorciatoie disponibili in quella dimensione al momento
  dell'esportazione, ciascuna con il proprio nome e il proprio esadecimale individuale (indipendente da dove/se
  compaiono nella griglia)
+ **`disp={nome,fine/inizio/spazio}...`** — la disposizione delle scorciatoie effettivamente utilizzate all'interno
  del testo disegnato, cioè in quali colonne della griglia si trova ciascuna occorrenza (`inizio` e `fine`) e se
  prima di essa era stato lasciato lo spazio automatico (`1`) o no (`0`)

Reincollando l'intero codice con `/paste`, il programma ricostruisce fedelmente sia l'immagine sia tutte le
scorciatoie usate per generarla, comprese le loro posizioni esatte nel testo.

<h2>Esempio di utilizzo</h2>

Inserendo la stringa `windows`, si ottiene l'immagine

```
O   O  OOOOO  O   O  OOOO    OOO   O   O   OOOO 
O   O    O    OO  O  O   O  O   O  O   O  O     
O O O    O    O O O  O   O  O   O  O O O   OOO  
OO OO    O    O  OO  O   O  O   O  OO OO      O 
O   O  OOOOO  O   O  OOOO    OOO   O   O  OOOO  
```

(Qui i caratteri `_` sono stati rimossi per una migliore leggibilità)

Il bitstream è `100010111110100010111100011100100010011110100010001000110010100010100010100010100000101010001000101010100010100010101010011100110110001000100110100010100010110110000010100010111110100010111100011100100010111100`

L'esadecimale ottenuto è **`/22fa2f1c89e888ca28a282a22a8a2a9cd889a28b60a2fa2f1c8bc/`**

Questo esadecimale può essere reinserito nel programma per decodificarlo in immagine (le due barre a inizio e fine sono
**fondamentali** per far sì che il programma riconosca l'esadecimale)

> ℹ️ **Nota:** decodificando un esadecimale generato dal programma, può capitare di vedere qualche riga in più
> rispetto al messaggio originale in fondo alla griglia. Non è un errore: è un **padding** aggiunto in fase di
> codifica per allungare la lunghezza totale del bitstream fino al valore primo più vicino per eccesso, così da
> renderla compatibile con un'altezza di griglia valida. Per evitare che questo padding produca una lunga sequenza
> di zeri (esteticamente sgradevole una volta convertita in esadecimale), viene riempito con un **pattern a
> diagonali** anziché lasciarlo vuoto.

In alternativa, scrivendo `/` sequito da un numero primo `p` tra `3, 5, 7, 11, 13, 17` si accede all'interfaccia di disegno su una griglia di altezza `p`, dove è possibile disegnare manualmente lo stesso messaggio pixel per pixel, o usando le lettere come scorciatoie rapide.