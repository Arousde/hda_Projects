package com.company;
import java.util.Random ;

public class Home {

    private int Temperatur ;
    private int Luftfeuchtigkeit ;
    private  boolean Fensterzustend ;
    private int DrehzahldesBadluefters ;
    private String __ID ;

  public  Home(String ID) {
      this.setTemperatur(0);
      this.setLuftfeuchtigkeit(0);
      this.setFensterzustend(false);
      this.setDrehzahldesBadluefters(0);
      this.set__ID(ID);
    }

    public int sensorTemperatur() {
        Random randomint = new Random();
        setTemperatur(randomint.ints(0, (30 + 1)).limit(1).findFirst().getAsInt());

        return getTemperatur();
    }

    public int sensorLuftfeuchtigkeit() {
        Random randomint = new Random();
        setLuftfeuchtigkeit(randomint.ints(10, (100 + 1)).limit(1).findFirst().getAsInt());

        return getLuftfeuchtigkeit();
    }

    public boolean sensorFensterzustend() {

        if (!isFensterzustend()){
            setFensterzustend(true);
            return isFensterzustend();
        }
        if (isFensterzustend()){
            setFensterzustend(false);
            return isFensterzustend();
        }
        // will never executed
        return isFensterzustend();
    }

    public int sensorDrehzahldesBadluefters() {
        setDrehzahldesBadluefters(getDrehzahldesBadluefters() + 10);
        return getDrehzahldesBadluefters();

    }

    public Home startSensoren() {

     int T = sensorTemperatur();
     int L = sensorLuftfeuchtigkeit();
     boolean F = sensorFensterzustend();
     int D = sensorDrehzahldesBadluefters();

     String fenster = "";
     if (F){fenster = "OPEN";}
     if (!F){fenster = "CLOSED";}

    //  String message = new String();
    //  message = message.concat("SmartHome : "+ this.__ID +"  Temperatur : " + T + " C " + " feuchtigkeit : " + F +
    //                           "Fensterzustend : " + fenster + " Drehzah " + D);
       return this ;
    }

    public int getTemperatur() {
        return Temperatur;
    }

    public void setTemperatur(int temperatur) {
        Temperatur = temperatur;
    }

    public int getLuftfeuchtigkeit() {
        return Luftfeuchtigkeit;
    }

    public void setLuftfeuchtigkeit(int luftfeuchtigkeit) {
        Luftfeuchtigkeit = luftfeuchtigkeit;
    }

    public boolean isFensterzustend() {
        return Fensterzustend;
    }

    public void setFensterzustend(boolean fensterzustend) {
        Fensterzustend = fensterzustend;
    }

    public int getDrehzahldesBadluefters() {
        return DrehzahldesBadluefters;
    }

    public void setDrehzahldesBadluefters(int drehzahldesBadluefters) {
        DrehzahldesBadluefters = drehzahldesBadluefters;
    }

    public String get__ID() {
        return __ID;
    }

    public void set__ID(String __ID) {
        this.__ID = __ID;
    }
}
