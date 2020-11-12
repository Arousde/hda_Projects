package com.example.stitchmongodb;


import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;


import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.OnSuccessListener;
import com.google.android.gms.tasks.Task;
import com.mongodb.stitch.android.core.Stitch;
import com.mongodb.stitch.android.core.StitchAppClient;
import com.mongodb.stitch.android.core.auth.StitchUser;
import com.mongodb.stitch.android.services.mongodb.remote.RemoteMongoClient;
import com.mongodb.stitch.android.services.mongodb.remote.RemoteMongoCollection;
import com.mongodb.stitch.core.auth.providers.anonymous.AnonymousCredential;
import com.mongodb.stitch.core.services.mongodb.remote.RemoteInsertOneResult;

import org.bson.Document;
/**
* <b>class to send fake data to the Db for testing .</b>
* <br><b>fake data are generated.</b>
* 
* @author Arous Oussema
* @version 1.0
*/
public class MainActivity extends AppCompatActivity {
/**
* the mongo db Collection
*/
    private RemoteMongoCollection<Document> collection;
/**
* the mongo db Client
*/
    private StitchAppClient mongoClient1;
/**
* the send Button
*/
    private Button send;

/**
* this is the main function for this programm
*/

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        this.send = findViewById(R.id.Send);
        this.mongoClient1 = Stitch.initializeDefaultAppClient("sensor-wvlwp");
        send.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                PostData();
            }
        });

    }

/**
* this function will create fake data and store it in a bson data
@return bson object contain fake data 
*/
    public Document createDBObject() {
        Document sensor = new Document("Name", "sensor")
                .append("Temperature", "Temperatur")
                .append("Luftfeuchtigkeit", "Luftfeuchtigkeit")
                .append("Feinstaub Prozentsatz", "Feinstaub Prozentsatz")
                .append("Fensterzustend", "Fensterzustend");
        return sensor;
    }
/**
* this function connects to mongo db with the client 
*<br> recive data from the {@link #createDBObject() createDBObject} method.
*<br> send the data to the database
*<br> return a msg to confirm state of the data 
*/
   public void PostData() {
        this.mongoClient1.getAuth().loginWithCredential(new AnonymousCredential()).addOnSuccessListener(new OnSuccessListener<StitchUser>() {
            @Override
            public void onSuccess(StitchUser stitchUser) {
                try {

                    /*
* connect
*/ 
                    RemoteMongoClient remoteMongoClient =
                            mongoClient1.getServiceClient(RemoteMongoClient.factory, "mongodb-atlas");
                    /*
* Set up the atlas collection
*/
                    collection = remoteMongoClient.getDatabase("PSocSensors").getCollection("Sensors");
                } catch (Exception e) {
                    e.getMessage();
                }
                Log.v("OnConnect", "successfully connected");

                /*
* post
*/

                Document Sensor = createDBObject();
                Sensor.append("user_id", stitchUser.getId());

                final Task<RemoteInsertOneResult> insertTask = collection.insertOne(Sensor);
                insertTask.addOnCompleteListener(new OnCompleteListener<RemoteInsertOneResult>() {
                    @Override
                    public void onComplete(@NonNull Task<RemoteInsertOneResult> task) {
                        if (task.isSuccessful()) {
                            Log.d("app", String.format("successfully inserted item with id %s",
                                    task.getResult().getInsertedId()));
                            Toast.makeText(MainActivity.this,"successfully Posted",Toast.LENGTH_LONG).show();
                        } else {
                            Log.e("app", "failed to insert document with: ", task.getException());
                        }
                    }
                });

                /*
*endPost
*/

            }
        });
    }
                /**
*@param none 
*/
  public void init() {
        Log.v("OnSuccess", "success");
    }
}
