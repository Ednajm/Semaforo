1. Descrizione del progetto
Questo progetto implementa la logica di controllo di un semaforo tramite una **Finite State Machine (FSM)**.
Il sistema controlla tre uscite:

* RED LED
* YELLOW LED
* GREEN LED 

Il comportamento del semaforo viene simulato in due ambienti:

1. CoDeSys - Structured Text (ST)**
   Utilizzando un PLC virtuale e il timer TON.
2. C++ - Visual Studio Code**
   Utilizzando la console per simulare l'accensione dei LED.
L'obiettivo principale è progettare prima la macchina a stati e successivamente implementarla in linguaggi diversi.
2. Analisi del problema

Un semaforo è un sistema sequenziale perché il comportamento dipende dallo stato precedente.

La sequenza richiesta è:

| Stato | Red | Yellow | Green | Tempo |
| ----- | --- | ------ | ----- | ----- |
| S0    | ON  | OFF    | OFF   | 5s    |
| S1    | ON  | ON     | OFF   | 2s    |
| S2    | OFF | OFF    | ON    | 5s    |
| S3    | OFF | ON     | OFF   | 2s    |

Dopo lo stato S3 il sistema ritorna allo stato iniziale S0.
invece in il codice di c++ ho utilizzato solo 3 stati 
 3. Progettazione FSM
  Che cosa è una FSM

FSM significa Finite State Machine
È un modello che descrive un sistema attraverso:
State (stati) → condizioni possibili del sistema.
Transition (transizioni) → passaggi tra stati.
Action (azioni)→ operazioni eseguite nello stato.
 4. Diagramma FSM 
 in codesys


                     5s
             +----------------+
             |                |
             v                |
          +------+            |
          | S0   |            |
          | RED  |            |
          +------+            |
             |
             | 2s
             v
       +-------------+
       | S1          |
       | RED+YELLOW  |
       +-------------+
             |
             | 5s
             v
          +------+
          | S2   |
          |GREEN |
          +------+
             |
             | 2s
             v
          +-------+
          | S3    |
          |YELLOW |
          +-------+
             |
             |
             +-------------> S0



 in vscode (c++)


                     +----------------+
                    |                |
                    |  5 s           |
                    |                |
                    v                |
              +-----------+          |
              |   RED     |          |
              | Red ON    |          |
              | Yellow OFF|          |
              | Green OFF |          |
              +-----------+          |
                    |                |
                    | state = GREEN  |
                    |                |
                    v                |
              +-----------+          |
              |  GREEN    |          |
              | Red OFF   |          |
              | Yellow OFF|          |
              | Green ON  |          |
              +-----------+          |
                    |                |
                    | state = YELLOW |
                    |                |
                    v                |
              +-----------+          |
              | YELLOW    |          |
              | Red OFF   |          |
              | Yellow ON |          |
              | Green OFF |          |
              +-----------+          |
                    |                |
                    | state = RED    |
                    +----------------+            
6. Perché non separare State Function e Machine Function?
La separazione è utile in sistemi molto grandi, con molti stati e funzioni complesse.
Per questo progetto invece è stata scelta una FSM integrata perché:
 1. Il numero di stati è limitato
Il semaforo possiede solo 4 stati in codesys.
e in vs code 3 stati 
Creare funzioni separate aumenterebbe la complessità senza vantaggi reali.
  2. Le transizioni sono semplici
Ogni cambio stato dipende solamente dal timer.

 3. Maggiore leggibilità

Con una sola struttura:
Stato
 |
 +-- Uscite
 |
 +-- Timer
 |
 +-- Transizione
è possibile vedere tutta la logica del sistema in un unico punto.

 4. Più simile alla programmazione PLC

Nei PLC industriali è comune utilizzare:

CASE state OF

per implementare macchine sequenziali.

Questa struttura è facile da verificare durante il debug.

7. Implementazione CoDeSys ST

La macchina a stati è realizzata con:
   pascal
CASE state OF

Esempio:

 pascal
0:
    Red := TRUE;
    Yellow := FALSE;
    Green := FALSE;

    t(IN:=TRUE, PT:=T#5S);

    IF t.Q THEN
        state := 1;
        t(IN:=FALSE);
    END_IF

Spiegazione:
 Stato 0 attiva il rosso.
 Il timer TON conta 5 secondi.
 Quando Q diventa TRUE viene eseguita la transizione verso lo stato successivo.

 8. Implementazione C++

In C++ la stessa FSM viene rappresentata tramite:

## Enum degli stati
  cpp
enum State
{
    RED,
    GREEN,
    YELLOW
};

L'enum permette di assegnare nomi agli stati invece di usare numeri.
Switch
   cpp
switch(state)
{
    case RED:
        break;
    case GREEN:
        break;
}

Lo switch svolge lo stesso ruolo del CASE in ST.
  Timer

In C++ viene usato:
  cpp
this_thread::sleep_for(
chrono::seconds(5)
);

che simula la temporizzazione del TON PLC.
9. Confronto ST e C++

| Concetto       | CoDeSys ST | C++            |
| -------------- | ---------- | -------------- |
| Macchina stati | CASE       | switch         |
| Stato          | INT        | enum           |
| Timer          | TON        | sleep_for      |
| Uscite         | BOOL       | stampa console |
| Cambio stato   | state :=   | state =        |

10. Test del progetto
C++ su VS Code
Compilazione:
  bash
g++ main.cpp -o semaforo
./semaforo
Dove si trova la FSM nel codice?
La FSM è rappresentata dalla variabile `state` e dalla struttura `CASE/switch`. Ogni valore dello stato identifica una configurazione del semaforo.

NOTA : Entrambe le implementazioni utilizzano lo stesso principio di progettazione basato su una Finite State Machine.La versione CoDeSys è più completa perché rappresenta tutte le fasi del semaforo reale.La versione C++ è una versione semplificata utilizzata per dimostrare il funzionamento della FSM su un normale computer.

in vs code :
Librerie usate
- iostream → serve per stampare sul terminale (`cout`)
- thread → permette di usare `sleep_for` (pausa del programma)
- chrono→ gestisce il tempo (secondi, millisecondi, ecc.)
Namespace
usingnamespacestd; 
