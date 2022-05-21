Implementarea temei a durat aproximativ 15 ore.

In functia main se construieste graful pe baza inputului dupa care se citeste fiecare cerinta pe rand si se apeleaza functia respectiva acesteia.

Functia "e1" citeste nodul sursa si apoi ia pe rand fiecare nod destinatie. Pentru a calcula si afisa fiecare distanta si path se apeleaza functia "DjikstraPRO" ce este practic algoritmul lui Djikstra modificat pentru a salva si un vector in care pe pozitia i, se va afla nodul "parinte" al acestuia. Afisarea acestui vector se face cu functia printPath care este apelata recursiv pana cand nu mai exista un "parinte". Distanta minima in cadrul algoritmului Dijkstra este calculata cu ajutorul functiei minDist ce returneaza indexul celui mai apropiat nod. La final se afiseaza toate informatiile necesare.

Functia "e2" se bazeaza pe algoritmul lui Kosaraju. Pentru a folosi acest algoritm este nevoie de calculul transpusei grafului ce se face folosind functia transpose, si a parcurgerii in adancime, folosind functia DFS dar excluzand nodurile depozit. Pe baza algoritmului, execut DFS astfel incat sa acopar toate nodurile din graf, dupa care pentru fiecare nod din stack-ul rezultat anterior execut DFS pe graful transpus rezultand in grupuri tare conexe pe care le salvez intr-un vector de stackuri, iar fiecare stack il sortez folosind functia de sort din stack.c care se foloseste de inca un stack pentru a da swap si a compara elementele. Inainte de afisare sortez vectorul in functie de primul element folosind bubble sort.

Functia "e3" incepe prin a construi o matrice cu toate distantele folosind Dijkstra (ceea ce ajuta la eficienta mai tarziu...) dupa care construiesc un vector zona cu nodurile ce compun zona iar capetele acestuia vor fi nodurile depozit de unde pleaca ce sunt determinate de functia bestDeposit ce calculeaza distanta cea mai mica de la fiecare depozit la oricare din nodurile din zona. Dupa aceea este apelata functia de permutari care calculeaza toate permutarile posibile cu nodurile din zona dar verifica daca costul permutarii pana la pasul respectiv a depasit minimul precedent, caz in care ma opresc (ceea ce ajuta la eficienta again). Daca a ajuns la o permutare completa se va apela functia checkDistance care verifica daca distanta permutarii este mai mica decat minimul, caz in care se actualizeaza minimul. La final se afiseaza costul minim.

Fisierul stack.c constine functii basic pentru stackuri cat si functia de sort descrisa anterior.

Fisierul graph_adj_matrix.c contine 2 functii pentru grafuri similare cu cele din laborator.