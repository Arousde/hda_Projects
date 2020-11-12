package com.arous.hda;

import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import java.sql.Timestamp;

public class jsonclass {



    private JSONObject jsobj ;
    private JSONParser parser ;

    public jsonclass(){
        this.jsobj = new JSONObject();
        this.parser = new JSONParser();

    }


    /*functions to get correspond data from the JSON*/


    public String get__ID(String msg){
        try {
            this.jsobj = (JSONObject) parser.parse(msg);
        } catch (ParseException e) {
            e.printStackTrace();
        }

        String ID= (String) jsobj.get("_ID");
        return ID ;
    }

    public Long get__Temperatur(String msg){
        try {
            this.jsobj = (JSONObject) parser.parse(msg);
        } catch (ParseException e) {
            e.printStackTrace();
        }

        Long Temperatur = (Long) jsobj.get("Temperatur");
        return Temperatur ;
    }

    public Long get__Luftfeuchtigkeit(String msg){
        try {
            this.jsobj = (JSONObject) parser.parse(msg);
        } catch (ParseException e) {
            e.printStackTrace();
        }

        Long Luftfeuchtigkeit = (Long)  jsobj.get("Luftfeuchtigkeit");
        return Luftfeuchtigkeit ;
    }

    public Long get__DrehzahldesBadluefters(String msg){
        try {
            this.jsobj = (JSONObject) parser.parse(msg);
        } catch (ParseException e) {
            e.printStackTrace();
        }

        Long DrehzahldesBadluefters = (Long) jsobj.get("DrehzahldesBadluefters");
        return DrehzahldesBadluefters ;
    }

    public String get__Fensterzustend(String msg){
        try {
            this.jsobj = (JSONObject) parser.parse(msg);
        } catch (ParseException e) {
            e.printStackTrace();
        }

        String Fensterzustend = (String) jsobj.get("Fensterzustend");
        return Fensterzustend ;
    }


    public String messageToJsonObject(String message) {

        /* convert from JSON string to JSONObject */
        try {
            this.jsobj = (JSONObject) parser.parse(message);
        } catch (ParseException e) {
            e.printStackTrace();
        }


        /* get the elements from the jsobj */
        String __ID= (String) jsobj.get("_ID");
        Long Temperatur = (Long) jsobj.get("Temperatur");
        Long Luftfeuchtigkeit = (Long)  jsobj.get("Luftfeuchtigkeit");
        String Fensterzustend = (String) jsobj.get("Fensterzustend");
        Long DrehzahldesBadluefters = (Long) jsobj.get("DrehzahldesBadluefters");

        /* build the message to print */
        Timestamp t = new Timestamp(System.currentTimeMillis());
        String msg = new String();
        msg = msg.concat("SmartHome : "+ __ID +" | Temperature : " + Temperatur +
                " C " + " | Feuchtigkeit : " + Luftfeuchtigkeit
                + " | Fensterzustand : " + Fensterzustend + " | Drehzahl : " + DrehzahldesBadluefters +" | Received : "+ t.toString());


        return msg;
    }
    public String DBmsg(String message) {

        try {
            this.jsobj = (JSONObject) parser.parse(message);
        } catch (ParseException e) {
            e.printStackTrace();
        }
        Timestamp t = new Timestamp(System.currentTimeMillis());
        String __ID= (String) jsobj.get("_ID");
        String id = new String();
        id=id.concat(__ID+"__"+t.toString());
        this.jsobj.put("DbId",id);
        //convert from JSobj To String
        String jstext = this.jsobj.toJSONString();
        return jstext;
    }
}
