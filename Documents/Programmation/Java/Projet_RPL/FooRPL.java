class FooRPL{
	public static void main (String[] args){
		PileRPL pile = new PileRPL(5);

		System.out.println("Pile vide : \n");
		System.out.println(pile);

		ObjEmp o1 = new ObjEmp(3);
		ObjEmp o2 = new ObjEmp(2);
		ObjEmp o3 = new ObjEmp(4);
		
		pile.push(o1);
		pile.push(o2);
		pile.push(o3);

		System.out.println("Pile contenant les éléments : \n");
		System.out.println(pile);
		
		
		pile.operations('*');
		System.out.println("Pile après ajout : \n");
		System.out.println(pile);

		pile.operations('/');
		System.out.println("Pile après ajout : \n");
		System.out.println(pile);
	}
}
