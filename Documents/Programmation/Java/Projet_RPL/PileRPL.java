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
		if(index==tailleMax)
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	public ObjEmp[] getPile()
	{
		return pileTab;
	}

	

	public void operations(char c)
	{
		ObjEmp temp;

		try{
				temp = pop();
				temp.operations(pop(),c);
				this.push(temp);
		}
		catch (IndexOutOfBoundsException e)
		{
			System.out.println("Add failed ! Probably pop failed because the stack is empty");
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
