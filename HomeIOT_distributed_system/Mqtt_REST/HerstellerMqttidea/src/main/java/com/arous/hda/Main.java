package com.arous.hda;

public class Main {

    public static void main(String[] args) {

                Subscriber s = new Subscriber();
                s.run();


                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        WeatherSpark w = new WeatherSpark();
                        w.sparkApi();
                    }
                }).start();
    }
}
