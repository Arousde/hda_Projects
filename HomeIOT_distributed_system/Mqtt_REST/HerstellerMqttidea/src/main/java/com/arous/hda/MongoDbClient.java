package com.arous.hda;

import com.mongodb.*;

import java.net.UnknownHostException;

public class MongoDbClient {


   private MongoClient mongoClient;
   private DB myMongoDb ;
   private DBCollection collection;
   private DBObject homeobj ;
   private Home home ;
   /*Connect to Db at localhost and default port*/
    MongoDbClient() throws UnknownHostException {
        this.mongoClient = new MongoClient(new MongoClientURI("mongodb://Arousde:sanymany1992@ds159782.mlab.com:59782/homezentrale"));
      //  System.out.println(this.mongoClient.getDatabaseNames());
    }

    public void createDBandColections() {
        this.myMongoDb = this.mongoClient.getDB("homezentrale");
        this.collection = myMongoDb.getCollection("Home");

    }
    public DBObject createDBObject(Home home) {
        DBObject homeObj = new BasicDBObject("_id",home.ID)
                                   .append("Name",home.Name)
                                   .append("Temperature",home.Temperatur)
                                   .append("Luftfeuchtigkeit",home.Luftfeuchtigkeit)
                                   .append("DrehzahldesBadluefters",home.DrehzahldesBadluefters)
                                   .append("Fensterzustend",home.Fensterzustend);
        return homeObj;
    }
    public void jsonToHome(String msg) {

        jsonclass js = new jsonclass();
        this.home =  js.jsonforDB(msg);

    }
    public void pushToDb(String Jsmsg) {
        createDBandColections();
        jsonToHome(Jsmsg);
        this.homeobj = createDBObject(this.home);
        try{
            this.collection.insert(this.homeobj);
            System.out.println("PUSHED !!!!");

        }catch (Exception e){
           System.out.println("ID EXIST");

        }

    }

}
