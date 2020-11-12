package com.arous.hda;

import static java.lang.Math.round;
import static spark.Spark.*;

import net.aksingh.owmjapis.core.OWM;
import net.aksingh.owmjapis.api.APIException;
import net.aksingh.owmjapis.model.CurrentWeather;

public class WeatherSpark {


    private  double def = 273.15;
    private double roundmin;
    private double roundmax;
    private  double celciusMin;
    private double celciusMax;
    private double humidity;
    private double pressure;
    private double groundLevel;
    private double SeaLevel;




    private  OWM owm ;
    private  CurrentWeather cwd ;

    public void getWeatherData() throws APIException {
        // declaring object of "OWM" class

         this.owm = new OWM("92a42bacb64d989212d3ee50ab3875f9");


        // getting current weather data for the "London" city
        this.cwd = this.owm.currentWeatherByCityName("Germany");

        //printing city name from the retrieved data
        System.out.println("City: " + this.cwd.getCityName());


        this.roundmin = this.cwd.getMainData().getTempMin() - this.def;
        this.roundmax = this.cwd.getMainData().getTempMax() - this.def;
        this.celciusMin = round(this.roundmin);
        this.celciusMax = round(this.roundmax);
        this.humidity = this.cwd.getMainData().getHumidity();
        this.pressure = this.cwd.getMainData().getPressure();
       // this.groundLevel = this.cwd.getMainData().getGroundLevel();
      //  this.SeaLevel = this.cwd.getMainData().getSeaLevel();


    }

    public void sparkApi() {
        try {
            getWeatherData();
        } catch (APIException e) {
            e.printStackTrace();
        }
        port(1212);

        get("/germany/temp", (req, res) -> {
            return "City: " + this.cwd.getCityName() + "  Temperature: " + "Max : " + this.celciusMax + " \'C" + "  Min : " + this.celciusMin + " \'C";
        });

        get("/germany/humidity", (req, res) -> {
            return "City: " + this.cwd.getCityName() + "  Humidity: " + this.humidity;
        });

        get("/germany/pressure", (req, res) -> {
            return "City: " + this.cwd.getCityName() + "  Pressure: " + this.pressure;
        });


    }


}
