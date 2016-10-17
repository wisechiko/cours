import java.net.Socket;
import java.net.ServerSocket;
import java.io.*;
import java.util.*;
import java.net.*;


class HelloClient1 {
	public static void main(String argv[]) throws Exception
	{
		Socket socket = new Socket("localhost", 1111);//new Socket("127.0.0.1", 1111)
		BufferedReader input = new BufferedReader( new InputStreamReader( socket.getInputStream() ) );
                System.out.println(input.readLine());
		socket.close();
	}
}

