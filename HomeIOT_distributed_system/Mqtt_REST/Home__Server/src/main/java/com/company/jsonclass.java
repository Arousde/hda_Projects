package com.company;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;
public class jsonclass {



    /*private interface Home {
         int Temperatur = 0;
         int Luftfeuchtigkeit = 0 ;
         boolean Fensterzustend = true;
         int DrehzahldesBadluefters = 0;
         String __ID ="" ;
    }*/

    private JSONObject jsobj ;
    private JSONParser parser ;

    public jsonclass(){
        this.jsobj = new JSONObject();
        this.parser = new JSONParser();

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
          String msg = new String();
          msg = msg.concat("SmartHome : "+ __ID +"  Temperatur : " + Temperatur +
                  " C " + " feuchtigkeit : " + Luftfeuchtigkeit
                + "  Fensterzustend : " + Fensterzustend + " Drehzah " + DrehzahldesBadluefters);


        return msg;
    }
}
