package com.arous.hda;

public class Home {
    Home(String id , String name , Long temperature , Long luftfeuchtigkeit , String fensterzustend , Long drehzahldesBadluefters){
        this.ID = id ;
        this.Name = name ;
        this.Temperatur = temperature;
        this.Luftfeuchtigkeit = luftfeuchtigkeit ;
        this.Fensterzustend = fensterzustend ;
        this.DrehzahldesBadluefters = drehzahldesBadluefters ;
    }
     String ID ;
     String Name ;
     Long Temperatur;
     Long Luftfeuchtigkeit;
     String Fensterzustend ;
     Long DrehzahldesBadluefters ;
}
