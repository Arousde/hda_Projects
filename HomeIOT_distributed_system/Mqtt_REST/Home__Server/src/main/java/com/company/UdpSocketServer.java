package com.company;


import java.io.IOException;
import java.net.*;
import java.util.logging.Logger;
import java.util.Arrays;
public class UdpSocketServer {

    private DatagramSocket udpSocket ;
    private DatagramPacket updPacket ;

    private  Logger log ;

    private interface Destination {
         String adr = "localhost" ;
         int Port = 6543 ;
    }

    private interface message {
         int bufferSize = 256 ;
         byte[] buf = new byte[bufferSize];
    }


    UdpSocketServer() {
        this.log = Logger.getLogger(UdpSocketServer.class.getName());

    }

    public void run()  {

        // create the UDP DATAGRAM SOCKET
        try {
            this.udpSocket = new DatagramSocket(Destination.Port);
            log.info(new StringBuilder().append("Server listening on Port :").append(Destination.Port).toString());
        } catch (SocketException e) {
            e.printStackTrace();
        }
        // non stop recieving
        while (true){
            // create the Packet
            this.updPacket = new DatagramPacket(message.buf,message.buf.length);
            // receive the Packet

            try {
                this.udpSocket.receive(this.updPacket);
            } catch (IOException e) {
                e.printStackTrace();
            }

            // print received packet
            printPacketData(this.updPacket);
        }

    }



    private void printPacketData(DatagramPacket udpPacket) {
        // Get IP address and port.
        InetAddress address = udpPacket.getAddress();
        int port = udpPacket.getPort();
        // Get packet length.
        int length = udpPacket.getLength();
        // Get the payload from the buffer. Mind the buffer size and the packet length!
        byte[] playload = Arrays.copyOfRange(udpPacket.getData(), 0, length);

        // deserialize the json object
        jsonclass js = new jsonclass();
        String msg = js.messageToJsonObject(new String(playload));


        /*OPEN THE TCP CLIENT AND SEND THE MESSAGE*/
        try {
            TcpSocketClient tcpSocketClient = new TcpSocketClient();
            tcpSocketClient.sendTheMessage(new String(playload));
            log.info("SENDING MESSAGE OVER TCP");

        }catch (Exception e ){
            log.warning(e.getLocalizedMessage());
        }


        // Print the packet information.udpPacket
        System.out.println("Received a packet: IP:Port: " + address + ":" + port +
                ", length: " + length + ", payload: " + msg);

    }
}
