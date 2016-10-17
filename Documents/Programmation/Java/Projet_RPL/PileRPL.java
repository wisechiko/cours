class PileRPL{

	private int tailleMax = 0;
	private int index = 0;
	private ObjEmp[] pileTab;


	public PileRPL (int tailleMax)
	{
		this.tailleMax=tailleMax;
		pileTab = new ObjEmp[tailleMax];
	}


	public void push (ObjEmp o) throws IndexOutOfBoundsException
	{
		if(this.isFull())
			throw new IndexOutOfBoundsException();
		pileTab[index]=o;
		index++;
	}


	public ObjEmp pop() throws IndexOutOfBoundsException
		//ICI IL FAUT PROPAGER L'EXCEPTION. parce que celui qui appelera pop demandera quand même un retour ; il doit lui faire un try/catch
	{
		ObjEmp temp;

		if(index==0)
			throw new IndexOutOfBoundsException();

		temp=pileTab[index-1];
		pileTab[index-1]=null;
		index--;

		return temp;
	}


	public boolean isFull()
	{
		return index==tailleMax;
	}


	public void operations(char c)
	{
		ObjEmp temp = null;

		try{
			temp = pop();
			try{
				temp.operations(pop(),c);
			}
			catch (IndexOutOfBoundsException e2)
			{
				System.out.println("Operation failed ! Probably pop failed because the stack had just one element. We're putting back the stack in the way it was before.");
			}
			this.push(temp);

		}
		catch (IndexOutOfBoundsException e1)
		{
			System.out.println("Operation failed ! Probably pop failed because the stack is empty");
			System.exit(1);
		}

	}


	public String toString()
	{
		String temp="";

		for( int i=index-1 ; i>=0 ; i-- )
		{
			temp += pileTab[i].toString();
			temp += "\n---\n";
		}

		return temp;
	}

}
