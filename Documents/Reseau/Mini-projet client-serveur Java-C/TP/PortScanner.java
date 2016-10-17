import java.net.Socket;
import java.io.*;

public class PortScanner
{
        public static void main(String args[])
	{

		if(args.length != 1)
		{
			System.out.println("Usage : jave PortScanner <targetIP>");
			System.exit(1);
		}

 	        for(int i=0; i <= 65535; i++)
		{
                	try
			{
				Socket socket = new Socket(args[0],i);
				System.out.println("Port in use: " + i );
			}
	                catch (IOException ioe)
			{
			}
		}
	}
}
