package com.company;

import java.io.DataOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.*;

public class TcpSocketClient {

    private interface Destination {
        String adr = "localhost" ;
        int Port = 3341 ;
    }

    private Socket tcpClient ;
    private InetAddress ipAdress ;

    public TcpSocketClient() {
        try {
            ipAdress = InetAddress.getByName("localhost");
        } catch (UnknownHostException e) {
            e.printStackTrace();
        }
        try {
            tcpClient = new Socket(Destination.adr,Destination.Port);
        } catch (IOException e) {
            System.out.println("CONNECTION WITH THE HTTP SERVER REFUESED");
        }

    }

    public void sendTheMessage(String message) {
       /* try {
            DataOutputStream packet = new DataOutputStream(this.tcpClient.getOutputStream());
            packet.writeChars(message + "\n");
            packet.flush();

        } catch (IOException e) {
            e.printStackTrace();
        }*/

        try {
            PrintWriter writer = new PrintWriter(new OutputStreamWriter(this.tcpClient.getOutputStream()));
            writer.write(message);
            writer.flush();
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}
