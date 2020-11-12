package com.arous.hda;
import java.net.UnknownHostException;
import java.util.logging.*;
import org.eclipse.paho.client.mqttv3.*;
public class Subscriber {

    private Logger log ;
    private String broker ;
    private interface brokerParams{
        /** The address of the broker. */
        String brokerAddress = "iot.eclipse.org";
        /** The port of the broker. */
        String brokerPort = "1883";
        /** The port of the protocol. */
        String brokerProtocol = "tcp";
        /** The topic. */
        String topic = "com/arous/hda";
    }

    public Subscriber() {
        log = Logger.getLogger(getClass().getName());
        /*create the broker
        String broker= "tcp://iot.eclipse.org:1883";
        */
        broker =brokerParams.brokerProtocol + "://" +
                brokerParams.brokerAddress + ":" +
                brokerParams.brokerPort;

    }


    public void run() {
        /* run the MQTT client */

        try {
            MqttClient client = new MqttClient(broker,MqttClient.generateClientId());
            client.setCallback(new SimpleMqttCallback());
            /* connect to the MQQT broker*/
            client.connect();
            log.info("Connected to MQTT broker: " + client.getServerURI());
            /* Subscribe to a topic */
            client.subscribe(brokerParams.topic);
            log.info("Subscribed to topic: " + client.getTopic(brokerParams.topic));
        } catch (MqttException e) {
            e.printStackTrace();
        }
    }

}