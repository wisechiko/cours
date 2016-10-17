class ObjEmp{

	private float val = 0;

	public ObjEmp(float val)
	{
		this.val=val;
	}

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

	public float getVal()
	{
		return val;
	}


	public String toString(){
		return ""+val;
	}

}
