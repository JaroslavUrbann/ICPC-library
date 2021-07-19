/*
kombinační čísla atd:
nCk = (n-1)C(k-1) + (n-1)Ck // první prvek vyberu + nevyberu, takhle počítat pokud mam modulo
vandermondeho identita:
suma od 0 do k: (nCi)*(mC(k-i))=(m+n)Ck // rozdělim prvky na n a m, proiteruju kolik vyberu z n
lucas theorem (m je prime, ale jde to zkombinovat přes crt):
nCk mod m == (n0Ck0)*(n1Ck1)... mod m, kde ...n2n1n0 je číslo n napsaný v bázi m a k2k1k0 je k
// jde to použít pokud m je malý a n,k jsou velký



(x+y)^n = suma od 0 do n: (nCk) * x^k * y^(n-k)
pro m čísel:
suma přes všechna n_1+n_2+..+n_m == n: (x_1^n_1)*(x_2^n_2)...*n!/(n_1!*n_2!*...*n_m!)
// mám m závorek (x_1+x_2+...+x_m) a každou skupinku čísel chci nějak rozmístit,
// což jsou prostě kombinace s opakováním or whatever: n! / (a!*b!*c!..)

množina A má m prvků a B má n prvků, m>=n
počet totálních zobrazení
sum from 0 to n-1: (-1)^k * (n choose k) * (n - k)^m
k == počet obrazů na který se zaručeně nikdo nenamapoval

chceme rozdělit m různých objektů do n stejných krabiček aby žádná nebyla prázdná
je to stejný jako zobrazení, ale krabičky můžu libovolně promíchat, takže /n!
stirling numbers of the second kind:
S(m,n) = 1/n! *(sum from 0 to n-1: (-1)^k * (n choose k) * (n - k)^m)
S(m+1,n) = S(m,n-1) + n*S(m,n)  // do vlastní třídy nebo k někomu připlácnout

chceme rozdělit m různých objektů do n stejných krabiček
jako stirling numbers of the second kind ale jedu od 1 do m na second argumentu
(1 krabička bude plná, 2/3/4...)

kolika způsoby rozesadit m osob okolo n stejných kulatých stolů
stejný rozsazení jsou takový, kde má každej člověk ty samý vedle sebe
stirling numbers of the first kind:
s(m+1,n) = s(m,n-1) + m*s(m,n)  // posadit k novýmu stolu, nebo posadit vedle člověka

derrangements
počet permutací n různých objektů, které nezanechají žádný z objektů na svém místě
n! * (suma od 0 do n: (-1)^k/k!)

catalan numbers
počet validních bracket sekvencí, počet cest v n*n gridu bez překročení diagonály
n bodů na kružnici, kolika způsoby lze spojit dvojce bodů, aniž by se úsečky protly
(2n choose n)/(n+1)
celkovej počet bracket sekvencí je (2n choose n)
všechny nevalidní si můžu ozrcadlit po ose (x-y) po tom co překročej diagonálu
a vyjde mi že jich je (2n choose n-1). Takže to prostě odečtu.
- c_{n+1} = i=0..n: suma c_i * c_{n-i}
	- kde se sekvence závorek poprvý znovu dotkne země

De bruijn sequence
B(m,n) = cyklickej string ve kterym se vyskytujou všechny možný substringy délky n
nad abecedou o velikosti m. Má dýlku m^n, Dá se sestrojit jako euler tour grafu, ve kterym je m^(n-1) nodů a z každýho vede m edges do následnýho substringu.
010 -0-> 100, 010 -1-> 101


GROUP THEORY
Burnside's lemma:
když mám objekty, který můžu nějak rotovat (jsou nějak symetrický) a chci spočítat kolik jich celkově je.
(zkus si vzpomenout na 3x3 čtverec a jeho rotace flipování)
picture je zachycení objektu, objekt může mít víc pictures, získání celkovýho počtu pictures je triviální
objekt je něco na co můžu libovolně aplikovat akce a nikdy nebude jeho picture vypadat stejně jako picture jinýho objektu
akce jsou nějaký rotace etc který můžu aplikovat na objekt aniž abych tim získal nějakej jinej objekt
musí platit, že pro každý 2 akce existuje jiná akce, kterou jsem mohl aplikovat místo těch dvou
jak na to:
nejdřív si spočítám, kolik by existovalo objektů, když by existovala jen jedna konkrétní akce (should be ez)
bernsidovo lemma říká, že celkovej počet objektů = průměr těchhle čísel
příklad / důkaz:
vem si 3x3 kostku, kterou můžeš rotovat o 0,90,180,270 degs a nebo flipovat po 4 osách (máš teda 8 akcí).
vem objekt a aplikuj na něj všech 8 akcí, získáš tim 1 <= pictures <= 8. Stejný pictures postav do stejnýho sloupce.
Udělej 8 řádků, v prvním řádku budou všechny ty různý pictures (nulová rotace), v druhym budou ty samý pictures, pokud se
daj orotovat o 90 stupňů a zůstanou stejný, v 3. řádku bude další akce atd..
Teď máš pro tenhle objekt 8 čtverců, který jsou různě rozmístěný přes všechny ty řádky.
Tohle udělej pro každej objekt.
Celkovej počet čtverců na ploše bude 8 * počet objektů = počet prvků v první řadě + v druhý řadě etc...
Počet prvků v každý řadě je počet objektů který by existovaly kdyby byla povolená jen tahle jedna akce.
takže 8 * počet objektů = součet těch čísel pro každou akci.
počet objektů = průměrnej počet pictures přes každou akci
*/
