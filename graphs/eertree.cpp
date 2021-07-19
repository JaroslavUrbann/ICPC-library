/*
počet distinktních palindromickejch substringů je max n:
přidání x mi nepřidá víc než 1 novej palindromickej suffix,
protože ten menší můžu otočit a je ve stringu

je to basically upravenej aho corasick.
máš 2 kořeny kde jeden je pro lichý polynomy a jeden pro sudý.
z každýho nodu jde hrana x pokud xpalx je největší palindromickej suffix.
stejně tak jde link pokud paxlx je největší palindromickej sufix

můžeš uchovávat suffix link hloubku, pokud chceš získat počet palindromů

*/
