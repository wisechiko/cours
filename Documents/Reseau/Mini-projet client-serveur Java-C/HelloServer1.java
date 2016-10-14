import java.net.Socket;
import java.net.ServerSocket;
import java.io.*;
import java.util.*;
import java.net.*;


class HelloServer1 {
	public static void main(String argv[]) throws Exception
	{

		ServerSocket serversocket = new ServerSocket(1111);
		{
			Socket socket = serversocket.accept();
			PrintStream out = new PrintStream( socket.getOutputStream() );
			out.println( "Hello World!" );
			socket.close();
		}
	}
}

