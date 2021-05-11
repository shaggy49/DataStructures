<!-- EDIT DISTANCE DYN (cane, pane) -->

        [0]  [1]  [2]  [3]  [4]
              e    n    a    p
[0]     -1 | -1 | -1 | -1 | -1 |
[1] e   -1 |  0 |  1 |  2 |  3 |
[2] n   -1 |  1 |  0 |  1 |  2 |
[3] a   -1 |  2 |  1 |  0 |  1 |
[4] c   -1 |  3 |  2 |  1 | -1 |

1.     
    cane = 4
    pane = 4
    dIns = memo (ane, pane) (1)         ==> 1
    dCanc = memo(pane, ane) (2)         ==> 1
    arr[4][4] = 1 + MIN (dIns, dCanc)   ==> 1 + min(1,1) == 2
    return 1 + MIN (dIns, dCanc)        ==> 2
1.2
    pane = 4
    ane = 3
    dIns = memo (ane, ane) (1)          ==> 0
    dCanc = memo(pane, ne) (2)          ==> 2
    arr[4][3] = 1 + MIN (dIns, dCanc)   ==> 1 + min(0,2) == 1
    return 1 + MIN (dIns, dCanc)        ==> 1
1.2.1
    ane = 3
    ane = 3
    //già calcolato
    arr[3][3] = 0;
    return arr[3][4];
1.2.2
    pane = 4
    ne = 2
    dIns = memo (ane, ne) (1)           ==> 1
    dCanc = memo(pane, e) (2)           ==> 3
    arr[4][2] = 1 + MIN (dIns, dCanc)   ==> 1 + min(1,3) == 2
    return 1 + MIN (dIns, dCanc)        ==> 2
1.2.2.2
    pane = 4
    e = 1
    dIns = memo (ane, e) (1)           ==> 2
    dCanc = memo(pane, ) (2)           ==> 4
    arr[4][1] = 1 + MIN (dIns, dCanc)  ==> 1 + min(2,4) == 3
    return 1 + MIN (dIns, dCanc)       ==> 3
1.2.2.2.2
    pane = 4
    "" = 0
    return 4;
1.2.2.2.1
    ane = 3
    e = 1
    arr[3][1] = 2
    return arr[3][1];
1.2.2.1
    ane = 3
    ne = 2
    dIns = memo (ne, ne) (1)            ==> 0
    dCanc = memo(ane, e) (2)            ==> 2
    arr[3][2] = 1 + MIN (dIns, dCanc)   ==> 1 + min(0,2) == 1
    return 1 + MIN (dIns, dCanc)        ==> 1
1.2.2.1.1
    ne = 2
    ne = 2
    arr[2][2] = 0
    return arr[2][2]
1.2.2.1.2
    ane = 3
    e = 1
    dIns = memo (ne, e) (1)             ==> 1
    dCanc = memo(ane, ) (2)             ==> 3
    arr[3][1] = 1 + MIN (dIns, dCanc)   ==> 1 + min(1,3) == 2
    return 1 + MIN (dIns, dCanc)        ==> 2
1.2.2.1.2.2
    ane = 3
    "" = 0
    return 3;
1.2.2.1.2.1
    ne = 2
    e = 1
    dIns = memo (e, e) (1)              ==> 0
    dCanc = memo(ne, ) (2)              ==> 2
    arr[2][1] = 1 + MIN (dIns, dCanc)   ==> 1 + min(0,2) == 1
    return 1 + MIN (dIns, dCanc)
1.2.2.1.2.1.1
    e = 1
    e = 1
    //già calcolato
    arr[1][1] = 0
    return arr[1][1];
1.2.2.1.2.1.2
    ne = 2
    "" = 0
    return 2;
1.1 
    ane = 3
    pane = 4 
    dIns = memo (ne, pane) (1)         ==> 2
    dCanc = memo(ane, ane) (2)         ==> 0
    arr[3][4] = 1 + MIN (dIns, dCanc)  ==> 1 + min(2,0) == 1
    return 1 + MIN (dIns, dCanc)       ==> 1
1.1.2
    ane = 3
    ane = 3
    arr[3][3] = memo(ne, ne) (1)       ==> 0
    return memo(ne, ne)                ==> 0
1.1.2.1
    ne = 2
    ne = 2
    arr[2][2] = 0;
    return arr[2][2];

1.1.1
    ne = 2
    pane = 4
    dIns = memo (e, pane) (1)           ==> 3
    dCanc = memo(ne, ane) (2)           ==> 1
    arr[2][4] = 1 + MIN (dIns, dCanc)   ==> 1 + min(3,1) == 2
    return 1 + MIN (dIns, dCanc)        ==> 2
1.1.1.2
    ne = 2
    ane = 3
    dIns = memo (e, ane) (1)            ==> 2
    dCanc = memo(ne, ne) (2)            ==> 0
    arr[2][3] = 1 + MIN (dIns, dCanc)   ==> 1 + min(0,2) = 1
    return 1 + MIN (dIns, dCanc)        ==> 1
1.1.1.2.1
    e = 1
    ane = 3
    //già calcolato quindi si può restituire
    arr[1][3] = 2
    return arr[1][3];
1.1.1.2.2
    ne = 2
    ne = 2
    //già calcolato 
    arr[2][2] = memo(e,e) (1)           ==> 0
    return arr[2][2];
1.1.1.2.2.1
    e = 1
    e = 1
    //già calcolato
    arr[1][1] = 0;
    return arr[1][1];

1.1.1.1
    e = 1
    pane = 4
    dIns = memo (, pane) (1)            ==> 4 *
    dCanc = memo(e, ane) (2)            ==> 2
    arr[1][4] = 1 + MIN (dIns, dCanc)   ==> 1 + min(4,2) == 3
    return 1 + MIN (dIns, dCanc)        ==> 3
1.1.1.1.1   
    "" = 0
    pane = 4
    return 4; *
1.1.1.1.2
    e = 1
    ane = 3
    dIns = memo (, ane) (1)             ==> 3 **
    dCanc = memo(e, ne) (2)             ==> 1
    arr[1][3] = 1 + MIN (dIns, dCanc)   ==> 1 + min(3,1) == 2
    return 1 + MIN (dIns, dCanc)        ==> 2 
1.1.1.1.2.1
    "" = 0
    ane = 3
    return 3; **
1.1.1.1.2.2
    e = 1
    ne = 2
    dIns = memo (, ne) (1)              ==> 3
    dCanc = memo(e, e) (2)              ==> 0
    arr[1][2] = 1 + MIN (dIns, dCanc)   ==> 1 + min(3,0) == 0+1 == 1
    return 1 + MIN (dIns, dCanc)        ==> 1
1.1.1.1.2.2.2
    e = 1
    e = 1
    arr[1][1] = memo ( , ) (1)          ==> 0
    return arr[1][1];
1.1.1.1.2.2.2.1
    "" = 0
    "" = 0
    return 0;

        [0]  [1]  [2]  [3]  [4]
              e    n    a    p
[0]     -1 | -1 | -1 | -1 | -1 |
[1] e   -1 |  0 |  1 |  2 |  3 |
[2] n   -1 |  1 |  0 |  1 |  2 |
[3] a   -1 |  2 |  1 |  0 |  1 |
[4] c   -1 |  3 |  2 |  1 |  2 |





<!-- EDIT DISTANCE DYN (matto, mattia) -->

        [0]  [1]  [2]  [3]  [4]  [5]  [6]
              a    i    t    t    a    m
[0]     -1 | -1 | -1 | -1 | -1 | -1 | -1 | 
[1] o   -1 |  2 |  3 | -1 | -1 | -1 | -1 | 
[2] t   -1 | -1 | -1 |  3 | -1 | -1 | -1 | 
[3] t   -1 | -1 | -1 | -1 |  3 | -1 | -1 | 
[4] a   -1 | -1 | -1 | -1 | -1 |  3 | -1 | 
[5] m   -1 | -1 | -1 | -1 | -1 | -1 |  3 | 


        [0]  [1]  [2]  [3]  [4]  [5]
         a    i    t    t    a    m
[0] o    2 |  3 | -1 | -1 | -1 | -1 | 
[1] t   -1 | -1 |  3 | -1 | -1 | -1 | 
[2] t   -1 | -1 | -1 |  3 | -1 | -1 | 
[3] a   -1 | -1 | -1 | -1 |  3 | -1 | 
[4] m   -1 | -1 | -1 | -1 | -1 |  3 | 

<!-- 
    si va verso l'alto per calcolare il dIns 
    si va verso sinistra per calcolare il dCanc
    si va in diagonale se i primi caratteri della stringa sono uguali
    
    per prima cosa se si può si va in diagonale
    se non si può andare in diagonale si va verso l'alto
    se non si può più andare verso l'alto si va verso sinistra
    quando si arriva alla prima riga o prima colonna si ritorna verso il fondo della matrice sommando ogni volta 1
-->

<!--
    Number of recursive calls (dynamic programming) between matto mattia == 9
    EDIT_DYN == 3
    Number of recursive calls (classic programming) between matto mattia == 2100
    EDIT_CLASS == 3
-->

1.
    matto = 5
    mattia = 6
    arr[5][6] = memo(atto, attia) (1)     ==> 3
    return arr[5][6]                      ==> 3
1.1
    atto = 4
    attia = 5
    arr[4][5] = memo(tto, ttia) (1)       ==> 3
    return arr[4][5]                      ==> 3
1.1.1
    tto = 3
    ttia =4
    arr[3][4] = memo(to, tia) (1)         ==> 3
    return arr[3][4]                      ==> 3
1.1.1.1
    to = 2
    tia = 3
    arr[2][3] = memo(o, ia) (1)           ==> 3
    return arr[2][3]                      ==> 3
1.1.1.1.1
    o = 1
    ia = 2
    dIns = memo (, ia) (1)              ==> 2
    dCanc = memo(o, a) (2)              ==> 2
    arr[1][2] = 1 + MIN (dIns, dCanc)   ==> 1 + min(2,2) == 3
    return 1 + MIN (dIns, dCanc)        ==> 3
1.1.1.1.1.1
    "" = 0
    ia = 2
    return 2;
1.1.1.1.1.2
    o = 1
    a = 1
    dIns = memo (, a) (1)               ==> 1
    dCanc = memo(o, ) (2)               ==> 1
    arr[1][1] = 1 + MIN (dIns, dCanc)   ==> 1 + min(1,1) == 2
    return 1 + MIN (dIns, dCanc)        ==> 2
1.1.1.1.1.2.1
    "" = 0
    a = 1
    return 1;
1.1.1.1.1.2.2
    o = 1
    "" = 0
    return 1;
    
<!--
    Number of recursive calls (dynamic programming) between parmigiano parmigiano == 11
    EDIT_DYN == 0
    Number of recursive calls (classic programming) between parmigiano parmigiano == 1622311
    EDIT_CLASS == 0
-->

0 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | 
-1 | 0 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | 
-1 | -1 | 0 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | 
-1 | -1 | -1 | 0 | -1 | -1 | -1 | -1 | -1 | -1 | 
-1 | -1 | -1 | -1 | 0 | -1 | -1 | -1 | -1 | -1 | 
-1 | -1 | -1 | -1 | -1 | 0 | -1 | -1 | -1 | -1 | 
-1 | -1 | -1 | -1 | -1 | -1 | 0 | -1 | -1 | -1 | 
-1 | -1 | -1 | -1 | -1 | -1 | -1 | 0 | -1 | -1 | 
-1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | 0 | -1 | 
-1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | 0 | 

