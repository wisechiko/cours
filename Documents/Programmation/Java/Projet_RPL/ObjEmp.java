class ObjEmp{

	private long val = 0;

	public ObjEmp(long val)
	{
		this.val=val;
	}


	/*
	   public void add(ObjEmp o)
	   {
	   val += o.getVal();
	   }*/

	public void operations(ObjEmp o, char c)
	{
		switch (c) {
			case '+': val += o.getVal();
				  break;
			case '-': val -= o.getVal();
				  break;
			case '*': val *= o.getVal();
				  break;
			case '/': val /= o.getVal();
		}
	}

	public long getVal()
	{
		return val;
	}


	public String toString(){
		return ""+val;
	}

}
