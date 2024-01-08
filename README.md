

1. Per creare una nuova system call, la prima cosa fatta è stata aggiungerla nel file **syscall.h**, con il suo nome e il suo numero:
	```c
 	#define SYS_ptm 22;
	```

	Successivamente, abbiamo aggiunto il prototipo della system call nel file **defs.h**: 
	```c
	int ptm(void);
	```

	Il passo successivo è stato aggiungere il prototipo anche nel file **user.h**:
	```c
	int ptm(void);
	```

	In **sysproc.c**, abbiamo aggiunto il wrapper di questa funzione: 
	```c
	int sys_ptm(void){

		return ptm();
	}
	```

	In **usys.S** abbiamo aggiunto la syscall:
	```c
	SYSCALL(ptm)
	```

	Abbiamo inoltre aggiunto nel file **syscall.c** il riferimento alla systemcall creata:
	```c
	extern int sys_ptm(void);

	[SYS_ptm]	sys_ptm
	```

	Infine, nel file **proc.c** abbiamo scritto il codice effettivo della systemcall che ne determina l'effettivo funzionamento:
	```c
	int cps() {
  		struct proc *pr;

  		//Abilita gli interrupts sul processo
  		sti();

  		acquire(&ptable.lock);
  		cprintf("name \t pid \t state \t\t ram \n---------------------------------------------------\n");
  		for (pr = ptable.proc; pr<&ptable.proc[NPROC]; pr++){  
    		switch(pr->state){
      			case SLEEPING:
        			cprintf("%s \t %d \t SLEEPING \t %d bytes \t\n", pr->name, pr->pid, pr->sz);
        			break;
      			case RUNNING:
        			cprintf("%s \t %d \t RUNNING \t %d bytes \t\n", pr->name, pr->pid, pr->sz);
        			break;
      			case RUNNABLE:
        			cprintf("%s \t %d \t RUNNABLE \t %d bytes \t\n", pr->name, pr->pid, pr->sz);
        			break;
      			case ZOMBIE:
        			cprintf("%s \t %d \t ZOMBIE \t %d bytes \t\n", pr->name, pr->pid, pr->sz);
        			break;
       
      			default:
        			break;     
    		}
  		}

  		release(&ptable.lock);
  		return 22;
	}
	```

	Il file **tm.c** contiene il main, che effettivamente chiamerà la systemcall appena creata.

	Come ultimo passo, abbiamo modificato il file **Makefile**, aggiungendo:
	 - In UPROGS :  _tm
	 - In EXTRA : tm.c

2. La systemcall che abbiamo creato ha la funzione di un mostrare un task manager semplificato: essa mostra , per ogni processo, il suo nome, il suo pid (id 	del processo), il suo stato (SLEEPING, RUNNING, RUNNABLE o ZOMBIE) e la quantità di memoria utilizzata espressa in byte.
Alla fine, viene visualizzato a console un piccolo menu che consente di fare 3 tipi di opzioni:
 	1. Aggiungere un processo
 	2. Killare un processo
 	3. Fare exit

	Al fine di mostrare il funzionamento della systemcall, abbiamo creato un'ulteriore systemcall (**test**), che crea un processo che sostanzialmente non fa nulla. Il procedimento che abbiamo seguito per la creazione di questa seconda systemcall è il medesimo.

3. Per far funzionare il tutto, sono necessari 2 semplici comandi:
	- make -> compila il codice sorgente e genera l'immagine del kernel eseguibile
	- make qemu-nox -> avvia e testa il kernel

	Per terminare l'esecuzione del kernel, premere **Ctrl** + **a** seguito da **x**.
