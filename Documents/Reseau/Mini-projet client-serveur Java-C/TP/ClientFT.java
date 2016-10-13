import java.net.Socket;
import java.net.ServerSocket;
import java.io.*;
import java.util.*;
import java.net.*;

class ClientFT {
	public static void main(String argv[])
	{
		//args check
		if (argv.length==0)
		{
			System.out.println("Usage : java ClientFT.java <infile>");
			System.exit(1);
		}

		//declarations
		String line;
		FileInputStream in = null; // pour ouvrir le fichier
			//les FilesStream écrivent en raw, alors que les Buffered prennent tout pour du texte
		OutputStream os = null;	// pour le mettre sur le réseau
		int c;	//octet lu en cours
		Socket socket = null;

		//opening file
		try 
		{

			in = new FileInputStream(argv[0]);
		}


		catch (FileNotFoundException e)
		{
			System.out.println("file not found");
			System.exit(1);
		}

		//setting and binding socket
		try
		{
			socket = new Socket("localhost",2000);
		}
		catch (UnknownHostException e)
		{
			System.out.println("Unknown Host. Address or port problem");
			System.exit(1);
		}
		catch (IOException e)
		{
			System.out.println("Couldnt connect to server");
			System.exit(1);
		}

		//writing to the network
		try
		{
		os = socket.getOutputStream();

			while ((c=in.read()) > 0)
			{
				os.write(c);
			}

			in.close();
			os.close();
			socket.close();
		}

		catch (IOException ex)
		{
			System.out.println("Couldnt getOutputStream / write to it");
			System.exit(1);
		}

	}
}
