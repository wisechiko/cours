import java.net.Socket;
import java.net.ServerSocket;
import java.io.*;
import java.util.*;
import java.net.*;


class HelloServer3 {
	public static void main(String argv[]) throws Exception
	{

		ServerSocket serversocket = new ServerSocket(1111);
	        Socket socket = serversocket.accept();
                ServiceThread service = new ServiceThread(socket);
		//	PrintStream out = new PrintStream( socket.getOutputStream() );
	//		out.println( "Hello World!" );
	//		socket.close();
		
	}
}

