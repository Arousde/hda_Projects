package com.company;

import org.json.simple.JSONObject;

public class jsonclass {

    private JSONObject jsobj ;


    public jsonclass(){
        this.jsobj = new JSONObject();

    }

    public String homeToJsonText(Home home) {

        //fenster zustand festlegen

        boolean F = home.isFensterzustend();
        String fenster = "";
        if (F){fenster = "OPEN";}
        if (!F){fenster = "CLOSED";}


        // initialize the jsobj
        jsobj.put("_ID", home.get__ID());
        jsobj.put("Temperatur", home.getTemperatur());
        jsobj.put("Luftfeuchtigkeit", home.getLuftfeuchtigkeit());
        jsobj.put("Fensterzustend", fenster);
        jsobj.put("DrehzahldesBadluefters", home.getDrehzahldesBadluefters());

        //conver from JSobj To String
        String jstext = jsobj.toJSONString();
        return jstext;
    }
}
