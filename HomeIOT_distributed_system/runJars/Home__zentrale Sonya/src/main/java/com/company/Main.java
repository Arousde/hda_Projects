package com.company;
import java.util.logging.Logger;
public class Main {

    private static Logger log ;

    public static void main(String[] args) {

       
        Home SmarthomeSigma = new Home("Sigma");
        Home SmarthomeDelta = new Home("Delta") ;

       log = Logger.getLogger(Main.class.getName());
        // alpha home start

       
        // beta home start

      
        // Sigma home start

        new Thread(new Runnable() {
            @Override
            public void run() {
            log.info("Thread Sigma Start");
                while (true){

                    jsonclass myJs = new jsonclass();

                    Home myhome =  SmarthomeSigma.startSensoren();
                    //Serialize
                    String message = myJs.homeToJsonText(myhome);

                    UdpSocketClient client = new UdpSocketClient();
                    client.sendmessage(message);

                    try {
                        Thread.sleep(10000) ;
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        }).start();

        // Delta home start

        new Thread(new Runnable() {
            @Override
            public void run() {
            log.info("Thread Delta Start");
                while (true){

                    jsonclass myJs = new jsonclass();

                    Home myhome =  SmarthomeDelta.startSensoren();
                    //Serialize
                    String message = myJs.homeToJsonText(myhome);

                    UdpSocketClient client = new UdpSocketClient();
                    client.sendmessage(message);

                    try {
                        Thread.sleep(10000) ;
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        }).start();

    }
}
