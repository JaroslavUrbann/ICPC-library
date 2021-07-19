/*
stable matching
you have boys and girls, and want to make pairs st. there is no boy b and girl g,
where they aren't matched but both prefer each other over their spouses.

n rounds:
each boy proposes to the girl on top of his list and each girl rejects all proposals except one
all rejected boys cross the girl off their list.

proof is easy:
if there were a b&g, b would propose to g first & and g wouldn't then later reject him for her current spouse

boy dominant:
there isn't any other stable matching where any b would get a more preffered girl than they now have

each girls pair gets weakly better every day
everyone is married bcs if b's list is empty, all girls got a better matching => there are n pairs
*/
