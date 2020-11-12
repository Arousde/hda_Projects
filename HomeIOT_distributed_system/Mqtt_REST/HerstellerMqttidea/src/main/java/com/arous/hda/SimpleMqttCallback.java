package com.arous.hda;
import org.eclipse.paho.client.mqttv3.*;
import java.util.logging.*;
public class SimpleMqttCallback implements MqttCallback{

    private Logger log ;

    @Override
    public void connectionLost(Throwable cause) {
        log = Logger.getLogger(getClass().getName());
        log.severe(" the Connection to MQTT broker is lost!");
    }
    @Override
    public void messageArrived(String topic, MqttMessage message) throws Exception {
        log = Logger.getLogger(getClass().getName());

        log.info("Message received: "+ new String(message.getPayload()) +" "+ "Topic :"+" "+topic
        );

        MongoDbClient DB = new MongoDbClient();
        DB.pushToDb(new String(message.getPayload()));
    }
    @Override
    public void deliveryComplete(IMqttDeliveryToken token) {
        log = Logger.getLogger(getClass().getName());

        try {
            log.info("Delivery completed: " + token.getMessage());

        } catch (MqttException e) {
            log.severe("Failed to get delivery token message:  "+ e.getMessage());

        }
    }
}
