// *mex is in micelaneous*
/*
grundy number of a state is the mex of grundy numbers that the state can reach.
you want to use grundy numbers, because you can isolate independent games and just take the xor of their grundy numbers.
that's basically all there is to it;
take the states and do a bottom-up-like dp where you calculate the grundy numbers of states

when you want to prove a solution to a combinatoric game theory problem, you have to prove:
1) all terminal states are losing states
2) from a winning state, you have to be able to get to at least 1 losing state
3) from a losing state, you have to be able to get to only winning states

proof for nim/grundy numbers:
loosing state is when grundy number is 0:
1) loosing state is when all piles have 0: xor is also 0, grundy is also 0, since it's the starting state;
2) for single game:
		your mex is bigger than 0, so you have to be able to get to a state with 0
	 for multiple games:
	 	let's have the xor of 3 games:
			01010100
			01101101
			00010111
			--------
			00101110
		take one of the numbers that has the biggest bit of the xor, and erase that bit. then you can
		set rest of the bits as you want, since you can reach all smaller numbers. so you can change that number so that the total xor
		becomes 0.
3) if you have xor of AxBxC=0, then you can't lower one variable and make it equal to 0 again:
		AxBxC=AxDxC // you can xor all the other numbers and you get B=D, which is a contradiction, since D<B

so essentially you want to isolate separate games, calculate grundy numbers for each state of one game and then xor all the games together.
if you also prove your solution with these 3 things, then that would be great.
*/
