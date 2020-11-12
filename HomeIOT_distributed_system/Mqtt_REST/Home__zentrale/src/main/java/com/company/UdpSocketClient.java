package com.company;

import java.io.IOException;
import java.net.*;
import java.util.logging.Logger;

public class UdpSocketClient {



    private interface Destination {
         String adr = "localhost" ;
         int Port = 6543 ;
    }

    private InetAddress adress ;
    private DatagramSocket udpDatagramSocket;

    public UdpSocketClient() {

        try {
            this.adress = InetAddress.getByName(Destination.adr);
        } catch (UnknownHostException e) {
            e.printStackTrace();
        }
    }


    public void sendmessage(String msg) {

        // Create the UDP DATAGRAM SOCKET
        try {
            this.udpDatagramSocket = new DatagramSocket();

        } catch (SocketException e) {
            e.printStackTrace();
        }

        //convert the message into a byte array
        byte[] buffer = msg.getBytes();

        //create a UDP PACKET
        DatagramPacket packet = new DatagramPacket(buffer,buffer.length,adress,Destination.Port);
        
        // send the packet over the UDP Socket
        try {
            this.udpDatagramSocket.send(packet);
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}
