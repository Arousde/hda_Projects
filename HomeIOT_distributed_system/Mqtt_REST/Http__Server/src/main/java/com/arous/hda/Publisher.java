package com.arous.hda;
import java.util.logging.*;
import org.eclipse.paho.client.mqttv3.*;
import org.eclipse.paho.client.mqttv3.persist.*;
public class Publisher {

    private Logger log ;
    private interface QOS {
        /** The at-most-once QoS parameter of MQTT: */
         int QOS_AT_MOST_ONCE = 0;
        /** The at-least-once QoS parameter of MQTT: */
         int QOS_AT_LEAST_ONCE = 1;
        /** The exactly-once QoS parameter of MQTT: */
         int QOS_EXACTLY_ONCE = 2;
    }
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
    private String broker ;
    MemoryPersistence persistence;

    public Publisher() {
        log = Logger.getLogger(getClass().getName());

        broker =brokerParams.brokerProtocol + "://" +
                brokerParams.brokerAddress + ":" +
                brokerParams.brokerPort;
    }

    public void run(String msg) {
        /* Create some MQTT connection options*/
        MqttConnectOptions mqttConnectOptions = new MqttConnectOptions();
        mqttConnectOptions.setCleanSession(true);
        persistence = new MemoryPersistence();

        try {
            MqttClient client = new MqttClient(broker,MqttClient.generateClientId(),persistence);

            /*Connect to the MQTT broker using the connection options */
            client.connect(mqttConnectOptions);
            log.info("Connected to MQTT broker: " + client.getServerURI());
            /*Create the message and set a quality-of-service parameter */
            MqttMessage message = new MqttMessage(msg.getBytes());
            message.setQos(QOS.QOS_EXACTLY_ONCE);
            /*Publish the message*/
            client.publish(brokerParams.topic,message);
            log.info("Published message: " + message);
            /*Disconnect from the MQTT broker*/
            client.disconnect();
            log.info("Disconnected from MQTT broker");



        } catch (MqttException e) {
            log.severe("An error occurred: " + e.getMessage());
        }

    }
}
