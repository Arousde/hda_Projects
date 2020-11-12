package com.arous.hda;
import java.sql.Timestamp;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.logging.Logger;
import java.net.*;

// Apache
import org.apache.http.client.*;
import org.apache.http.client.methods.*;
import org.apache.http.impl.client.BasicResponseHandler;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import java.io.*;


public class TcpSocketServer {

    private Logger log ;
    /* Url from spark */
    private interface sparkUrl{
        String Turl = "http://localhost:1212/germany/temp";
        String Hurl = "http://localhost:1212/germany/humidity";
        String Purl = "http://localhost:1212/germany/pressure";

    }

    /* DATA for Apache*/
    private ResponseHandler<String> handler ;
    private   CloseableHttpClient httpclient ;
    private   HttpGet method ;
    private   CloseableHttpResponse response ;
    /*body data from Spark*/
    private   String temperature ;
    private   String pressure ;
    private   String humidity ;
    /* DATA LISTS */
    private ArrayList<String> Fensterzustend ;
    private ArrayList<String> Temperatur ;
    private ArrayList<String> DrehzahldesBadluefters ;
    private ArrayList<String> Luftfeuchtigkeit ;

    private String storedLine ;

    /* MESSAGE FROM UDP */
    private String message ;
    private String line  ;
    private ArrayList<String> History ;

    /* JAVA NET*/
    private ServerSocket tcpServerSocket ;
    private ServerSocket tcpServerSocketBrowser ;
    private Socket connectionSocket ;
    private Socket connectionSocketForHome ;

    /* INPUT OUTPUT READER WRITER*/
    private PrintWriter pw ;
    private BufferedReader br ;

    /* CONNECTS TO*/
    private interface Destination {
        String adr = "localhost" ;
        int Port = 3341 ;
    }
    private interface BrowserDestination {
        String adr = "localhost" ;
        int Port = 3345 ;
    }



    public TcpSocketServer() {
        this.log = Logger.getLogger(TcpSocketServer.class.getName());

        try {
            tcpServerSocket = new ServerSocket( Destination.Port);
            log.info(new StringBuilder().append("Http Server for Home is listening on Port :").append(Destination.Port).toString());

            tcpServerSocketBrowser = new ServerSocket( BrowserDestination.Port);
            log.info(new StringBuilder().append("Http Server for Browser is listening on Port :").append(BrowserDestination.Port).toString());

        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public void getSparkBodytemp() {
        this.handler = new BasicResponseHandler();
         // create an instance of HttpClient
        this.httpclient = HttpClients.createDefault();
        // crate methode instance
        this.method = new HttpGet(sparkUrl.Turl);

        // execute the response and get data from body
        try {
            this.response = httpclient.execute(this.method);
            this.temperature = this.handler.handleResponse(this.response);
            response.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public void getSparkBodypress() {
        this.handler = new BasicResponseHandler();
        // create an instance of HttpClient
        this.httpclient = HttpClients.createDefault();
        // crate methode instance
        this.method = new HttpGet(sparkUrl.Purl);

        // execute the response and get data from body
        try {
            this.response = httpclient.execute(this.method);
            this.pressure = this.handler.handleResponse(this.response);
            response.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void getSparkBodyhumidity() {
        this.handler = new BasicResponseHandler();
        // create an instance of HttpClient
        this.httpclient = HttpClients.createDefault();
        // crate methode instance
        this.method = new HttpGet(sparkUrl.Hurl);

        // execute the response and get data from body
        try {
            this.response = httpclient.execute(this.method);
            this.humidity = this.handler.handleResponse(this.response);
            response.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    public String runServerForHome() {
        /*Open a new connection  with Home and return the client */
        try {
            this.connectionSocketForHome = this.tcpServerSocket.accept();
        } catch (IOException e) {
            e.printStackTrace();
        }

        BufferedReader br = null;
        try {
            br = new BufferedReader(new InputStreamReader(this.connectionSocketForHome.getInputStream()));
            String line ;
            this.message = "";
            while ((line = br.readLine()) != null) {
                StringBuilder strbuld = new StringBuilder();
                strbuld.append(this.message).append(line);
                this.message = strbuld.toString();
            }


        } catch (IOException e) {
            e.printStackTrace();
        }
        try {
            br.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        try {
            this.connectionSocketForHome.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
     return this.message;
    }

    public String concatMsgForStorageTpr(String ID , String Property) {
        Timestamp t = new Timestamp(System.currentTimeMillis());
        String msg = new String();
        msg = msg.concat("SmartHome : "+ ID +" | Temperature : " + Property + " C " + " | Received : "+ t.toString());
        return msg;

    }
    public String concatMsgForStoragefenstr(String ID , String Property) {
        Timestamp t = new Timestamp(System.currentTimeMillis());
        String msg = new String();
        msg = msg.concat("SmartHome : " + ID + " | Fensterzustand : " + Property +" | Received : "+ t.toString());
        return msg;

    }
    public String concatMsgForStoragedreh(String ID , String Property) {
        Timestamp t = new Timestamp(System.currentTimeMillis());
        String msg = new String();
        msg = msg.concat("SmartHome : "+ ID + " | Drehzah " + Property + " | Received : "+ t.toString());
        return msg;

    }
    public String concatMsgForStoragefeuch(String ID , String Property) {
        Timestamp t = new Timestamp(System.currentTimeMillis());
        String msg = new String();
        msg = msg.concat("SmartHome : "+ ID + " | feuchtigkeit : " + Property + " | Received : "+ t.toString());
        return msg;

    }

     public void storeData() {
        message = runServerForHome();


        /* GET JSON DATA FROM MESSAGE*/

        jsonclass js = new jsonclass();
        String id = js.get__ID(message);
        String fenstr = js.get__Fensterzustend(message);
        Long tpr = js.get__Temperatur(message);
        Long drehzahl = js.get__DrehzahldesBadluefters(message);
        Long feuch = js.get__Luftfeuchtigkeit(message);

        String tprmsg = concatMsgForStorageTpr(id,tpr.toString());
        this.Temperatur.add(tprmsg);

        String feuchmsg = concatMsgForStoragefeuch(id,feuch.toString());
        this.Luftfeuchtigkeit.add(feuchmsg);

        String drehmsg = concatMsgForStoragedreh(id,drehzahl.toString());
        this.DrehzahldesBadluefters.add(drehmsg);

        String fnstrhmsg = concatMsgForStoragefenstr(id,fenstr);
        this.Fensterzustend.add(fnstrhmsg);
        String msg = js.messageToJsonObject(message);
        History.add(msg);
        /*PUBLISH MSG */
         String pubMsg = js.DBmsg(message);
         Publisher p = new Publisher();
         p.run(pubMsg);


    }

    public void printTemp(PrintWriter pw) {
        for (String s : this.Temperatur) {
            pw.write("<h1 style=\"color:blue;text-align:center\">"+s+"</h1>");
            pw.write("\r\n");
        }
    }

    public void printFeucht(PrintWriter pw) {
        for (String s : this.Luftfeuchtigkeit) {
            pw.write("<h1 style=\"color:blue;text-align:center\">"+s+"</h1>");
            pw.write("\r\n");
        }
    }

    public void printFenster(PrintWriter pw) {
        for (String s : this.Fensterzustend) {
            pw.write("<h1 style=\"color:blue;text-align:center\">"+s+"</h1>");
            pw.write("\r\n");
        }
    }

    public void printLufter(PrintWriter pw) {
        for (String s : this.DrehzahldesBadluefters) {
            pw.write("<h1 style=\"color:blue;text-align:center\">"+s+"</h1>");
            pw.write("\r\n");
        }
    }

    public void printHistory(PrintWriter pw) {
        for (String s : this.History) {
            pw.write("\r\n");
            pw.write("<h1 style=\"color:blue;text-align:center\">"+s+"</h1>");
            pw.write("\r\n");
            pw.write("<h3 style=\"color:red;text-align:center\">"+"********************************"+"</h3>");
            pw.write("\r\n");
        }
    }
    public void printsparktemp(PrintWriter pw) {

            pw.write("\r\n");
            pw.write("<h1 style=\"color:blue;text-align:center\">"+this.temperature+"</h1>");
            pw.write("\r\n");
            pw.write("<h3 style=\"color:red;text-align:center\">"+"********************************"+"</h3>");
            pw.write("\r\n");

    }
    public void printsparkpress(PrintWriter pw) {

        pw.write("\r\n");
        pw.write("<h1 style=\"color:blue;text-align:center\">"+this.pressure+"</h1>");
        pw.write("\r\n");
        pw.write("<h3 style=\"color:red;text-align:center\">"+"********************************"+"</h3>");
        pw.write("\r\n");

    }
    public void printsparkhumidity(PrintWriter pw) {

        pw.write("\r\n");
        pw.write("<h1 style=\"color:blue;text-align:center\">"+this.humidity+"</h1>");
        pw.write("\r\n");
        pw.write("<h3 style=\"color:red;text-align:center\">"+"********************************"+"</h3>");
        pw.write("\r\n");

    }
    public void runlists() {
        this.History = new ArrayList<>();
        this.Temperatur = new ArrayList<>();
        this.Luftfeuchtigkeit = new ArrayList<>();
        this.DrehzahldesBadluefters = new ArrayList<>();
        this.Fensterzustend = new ArrayList<>();
    }

    public void getTheHTTPGetNoun() {
        br = null;
        storedLine = "";
        try {
            br = new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));
            line = br.readLine() ;
            if(line !=null){
                String[] arrayLine = line.split("\\s+");
                line = "" ;
                if (!arrayLine[1].equals("/favicon.ico")){
                    line = arrayLine[1];
                }
                if (!line.equals("")){
                    storedLine = line;
                }
            }


        } catch (IOException e) {
            e.printStackTrace();
        }
        /*try {
            br.close();
        } catch (IOException e) {
            e.printStackTrace();
        }*/
    }

    public void connectToBrowser() {
        try {
            connectionSocket = tcpServerSocketBrowser.accept();

        } catch (IOException e) {
            e.printStackTrace();

        }
    }

  synchronized  public void run() {
        runlists();
        /* connect to the Home server in a separate thread*/
        /* get the message and push it to the History Array*/
        new Thread(new Runnable() {
            @Override
            public void run() {
                while (true){
                    storeData();
                }

            }
        }).start();
        /*get data from spark*/
         getSparkBodytemp();
         getSparkBodypress();
         getSparkBodyhumidity();

        while (true) {

            /*Open a new TCP connection and return the client Socket */
              connectToBrowser();
            /* Read the HTTP req and store the Get method noun in storedLine */
              getTheHTTPGetNoun();

            /* modify the socket output stream HTTP CONFORM*/
            try {
                this.pw = new PrintWriter(this.connectionSocket.getOutputStream());
                this.pw.write("  HTTP/2.0 200 OK\r\n");
                this.pw.write("Accept: text/plain, text/html, text/*\\r\\n");
                this.pw.write("Host: localhost \r\n");
                this.pw.write("\r\n");
                this.pw.write("<TITLE>Smart Home Zentrale</TITLE>");
                this.pw.write("<P>refresh to receive new Data</P>");

                if (this.storedLine.equals("/temperature")){
                    printTemp(this.pw);

                }
                else if (this.storedLine.equals("/luftfeuchtigkeit")){
                    printFeucht(this.pw);

                }
                else if (this.storedLine.equals("/fensterzustand")){
                    printFenster(this.pw);

                }
                else if (this.storedLine.equals("/drehzahl")){
                    printLufter(this.pw);

                }
                else if (this.storedLine.equals("/history")){
                    printHistory(this.pw);

                }
                else if (this.storedLine.equals("/germany/temperature")){
                    printsparktemp(this.pw);

                }
                else if (this.storedLine.equals("/germany/pressure")){
                    printsparkpress(this.pw);

                }
                else if (this.storedLine.equals("/germany/humidity")){
                    printsparkhumidity(this.pw);

                }

                else {
                    this.pw.write("<h1 style=\"color:blue;text-align:center\">"+"temperature"+"</h1>");
                    this.pw.write("<h1 style=\"color:blue;text-align:center\">"+"luftfeuchtigkeit"+"</h1>");
                    this.pw.write("<h1 style=\"color:blue;text-align:center\">"+"fensterzustand"+"</h1>");
                    this.pw.write("<h1 style=\"color:blue;text-align:center\">"+"drehzahl"+"</h1>");
                    this.pw.write("<h1 style=\"color:blue;text-align:center\">"+"history"+"</h1>");
                    this.pw.write("<h1 style=\"color:blue;text-align:center\">"+"germany/temperature"+"</h1>");
                    this.pw.write("<h1 style=\"color:blue;text-align:center\">"+"germany/pressure"+"</h1>");
                    this.pw.write("<h1 style=\"color:blue;text-align:center\">"+"germany/humidity"+"</h1>");




                }


                this.pw.flush();





            } catch (IOException e) {
                e.printStackTrace();
            }

            try {
                this.br.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
           /* pw.close();

            try {
                connectionSocket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }*/

        }
    }

}
