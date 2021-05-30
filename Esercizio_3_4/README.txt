***COMPILAZIONE***

---PER COMPILARE TUTTI I FILE DI TUTTI I PACKAGE---
1) posizionarsi in .../Esercizio_3_4
2) ant all (o ant)

----PER COMPILARE SOLO IL PACKAGE unionfindset CHE CONTIENE LA STRUTTURA DATI UnionFindSet E I TEST ASSOCIATI ALLA STRUTTURA DATI---
1) posizionarsi in .../Esercizio_3_4
2) ant allUnion

---PER COMPILARE SOLO IL PACKAGE graphs E CREARE tutti I .jar DEL PACKAGE graphs---
1) posizionarsi in .../Esercizio_3_4
2) ant allGraphPackage

---PER COMPILARE SOLO IL PACKAGE graphs E CREARE I .jar: STRUTTURA DATI Graph e TEST ASSOCIATI ALLA STRUTTURA DATI Graph---
1) posizionarsi in .../Esercizio_3_4
2) ant allGraph

---PER COMPILARE SOLO IL PACKAGE graphs E CREARE I.jar: STRUTTURA DATI UnionFindSet, STRUTTURA DATI Graph, ALGORITMO DI Kruskal e TEST ASSOCIATI ALL'ALGORITMO DI Kruskal---
1) posizionarsi in .../Esercizio_3_4
2) ant allKruskal

---PER COMPILARE SOLO IL PACKAGE graphs E CREARE I .jar: STRUTTURA DATI UnionFindSet, STRUTTURA DATI Graph, ALGORITMO DI Kruskal e MAIN CHE PRENDE IN INPUT UN FILE---
1) posizionarsi in .../Esercizio_3_4
2) ant allMain


***ESECUZIONE***

---PER ESEGUIRE .../Esercizio_3_4/src/unionfindset/UnionFindSetTestsRunner---
1) posizionarsi in .../Esercizio_3_4/build
2) java -jar UnionFindSetTestsRunner.jar

---PER ESEGUIRE .../Esercizio_3_4/src/graphs/GraphTestsRunner---
1) posizionarsi in .../Esercizio_3_4/build
2) java -jar GraphTestsRunner.jar

---PER ESEGUIRE .../Esercizio_3_4/src/graphs/KruskalAlgorithmTestsRunner---
1) posizionarsi in .../Esercizio_3_4/build
2) java -jar KruskalAlgorithmTestsRunner.jar

---PER ESEGUIRE .../Esercizio_3_4/src/graphs/GraphKruskalMain---
1) posizionarsi in .../Esercizio_3_4/build
2) java -jar GraphKruskalMain.jar


***ELIMINAZIONE***

---PER ELIMINARE QUALSIASI PRODOTTO DELLA COMPILAZIONE E/O ESECUZIONE---
1) posizionarsi in .../Esercizio_3_4
2) ant clean
