import java.net.Socket;
import java.net.ServerSocket;
import java.io.*;
import java.util.*;
import java.net.*;


class HelloServer2 {
	public static void main(String argv[]) throws Exception
	{

                int i=0;
		ServerSocket serversocket = new ServerSocket(1111);
		Socket socket = serversocket.accept();
                while(i != 5)
		{
			PrintStream out = new PrintStream( socket.getOutputStream() );
			out.println( "Hello World!" );
                        i++;
		}
	        socket.close();
	}
}

