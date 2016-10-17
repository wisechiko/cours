import java.net.Socket;
import java.net.ServerSocket;
import java.io.*;
import java.util.*;
import java.net.*;


class HelloServer5 {
	public static void main(String argv[]) throws Exception
	{

		ServerSocket serversocket = new ServerSocket(1111);
                int i=0;
                while(true)
                {
	               Socket socket = serversocket.accept();
                       System.out.println(socket.getLocalPort());
                       ServiceThread1 service = new ServiceThread1(socket);
                       i++;
                }
	}
}

