/*
jak najít všechny orientovaný kružnice v orientovanym grafu:
O((n+e)*(c+1)) (víc než O(2^n))

rozdělim na silně souvislý komponenty.
pro každej vrchol najdu cykly ve kterejch se vyskytuje a pak ho odstranim:
	udržuju si stack vrcholů který jsou otevřený
	udržuju si zablokovaný vrcholy který jsem navštívil
		- zablokovaný vrcholy se odblokujou když ze stacku odstranim nejhlubší vrchol se kterym sousedili
			(přes kterej jsem se nemohl dostat dál)
	když ze stacku odstranim vrchol kterej je součástí nějakýho nalezenýho cyklu, tak ho odblokuju.

*/
