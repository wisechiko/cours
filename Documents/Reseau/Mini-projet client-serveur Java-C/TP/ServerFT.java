import java.net.Socket;
import java.net.ServerSocket;
import java.io.*;
import java.util.*;
import java.net.*;

class ServerFT {
	public static void main(String argv[])
	{
		//args chec
		if (argv.length==0)
		{
			System.out.println("Usage : java ServeurFT.java <outfile>");
			System.exit(1);
		}

		//declarations
		FileOutputStream out = null; //les FileStream écrivent en raw, alors que les Buffered prennent tout pour du texte.
		InputStream in = null;
		int c;
		ServerSocket serversocket = null;
		Socket socket = null;

		//opening file
		try
		{
			out = new FileOutputStream(argv[0]);
		}
		catch (FileNotFoundException e)
		{
			System.out.println("Couldn't open/create/access to file");
			System.exit(1);
		}

		//setting and binding socket
		try
		{
			serversocket = new ServerSocket(2000);
			socket = serversocket.accept();
			in = socket.getInputStream();

			while ((c=in.read()) > 0)
			{
				out.write(c);
			}

			in.close();
			out.close();
			socket.close();
		}
		catch (IOException e)
		{
			System.out.println("Couldnt set+bind socket / put port on listen. Port already used ?");
			System.exit(1);
		}
	}
}
