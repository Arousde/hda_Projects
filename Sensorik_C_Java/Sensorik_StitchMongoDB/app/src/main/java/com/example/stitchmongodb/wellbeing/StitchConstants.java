package h_da.wellbeing;

import com.mongodb.stitch.android.core.Stitch;
import com.mongodb.stitch.android.core.StitchAppClient;
import com.mongodb.stitch.android.services.mongodb.remote.RemoteMongoCollection;

import org.bson.Document;

public class StitchConstants {

    private RemoteMongoCollection<Document> collection;
    private final static StitchAppClient mongoClient1 = Stitch.initializeDefaultAppClient("sensor-wvlwp");

    public static StitchAppClient getMongoClient1() {
        return mongoClient1;
    }


    public RemoteMongoCollection<Document> getCollection() {
        return collection;
    }
}
