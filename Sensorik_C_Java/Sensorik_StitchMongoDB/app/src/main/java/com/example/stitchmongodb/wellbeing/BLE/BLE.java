package h_da.wellbeing.BLE;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCallback;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothManager;
import android.bluetooth.BluetoothProfile;
import android.bluetooth.le.BluetoothLeScanner;
import android.bluetooth.le.ScanCallback;
import android.bluetooth.le.ScanFilter;
import android.bluetooth.le.ScanResult;
import android.bluetooth.le.ScanSettings;
import android.content.Context;
import android.content.Intent;
import android.os.Handler;

import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.UUID;

/************************************************************
 * This class handles the BLE functionality
 ************************************************************/

public class BLE {
    /****************************************************************************************
     * CONSTANTS
     ****************************************************************************************/
    // BLE Settings
    private final int BLE_SCAN_PERIOD = 5000;

    // Request Codes
    public final static int REQUEST_ENABLE_BT = 1;
    public static final String BROADCAST_BLE_DISCOVERY_COMPLETE = "ble.DISCOVERY_COMPLETE";
    public static final String BROADCAST_BLE_STATUS_CONNECTED = "ble.STATUS_CONNECTED";
    public static final String BROADCAST_BLE_CHARACTERISTIC_HELLO_WORLD = "ble.CHARACTERISTIC_HELLO_WORLD";

    /****************************************************************************************
     * DEFINITION
     ****************************************************************************************/
    private Context activityContext;
    private BluetoothAdapter bleAdapter;
    private boolean bleScanning = false;
    private boolean bleConnected = false;
    private HashMap<String, BluetoothDevice> bleScanResults;
    private BleScanCallback bleScanCallback;
    private BluetoothLeScanner bleScanner;
    private Handler btHandler;
    private BluetoothGatt bleGatt;
    private List<BluetoothGattCharacteristic> bleCharacteristics = new ArrayList<>();

    private String bleCharacteristic = "";

    /*****************************************************************************************
     * GETTER / SETTER
     *****************************************************************************************/
    public HashMap<String, BluetoothDevice> getBleScanResults() {
        return bleScanResults;
    }
    public String getBleCharacteristic() {
        return bleCharacteristic;
    }

    /******************************************************************************************
     * Constructor+
     * @param activityContext - Context of the activity which uses the BLE functionality
     ******************************************************************************************/
    public BLE(Context activityContext) {
        BluetoothManager btManager = (BluetoothManager) activityContext.getSystemService(Context.BLUETOOTH_SERVICE);
        bleAdapter = btManager.getAdapter();
        this.activityContext = activityContext;
    }

    /*******************************************************************************************
     * FUNCTIONS
     *******************************************************************************************/

    /**
     * Starts the BLE device discovery and signals the activity when the scan is complete
     */
    public void startScan() {
        if (hasBluetoothPermissions() || !bleScanning) {
            List<ScanFilter> filters = new ArrayList<>();
            // Scan in ble mode
            ScanSettings settings = new ScanSettings.Builder()
                    .setScanMode(ScanSettings.SCAN_MODE_LOW_POWER)
                    .build();
            bleScanResults = new HashMap<>();
            bleScanCallback = new BleScanCallback();
            bleScanner = bleAdapter.getBluetoothLeScanner();
            bleScanner.startScan(filters, settings, bleScanCallback);
            bleScanning = true;
            // Handler stops the scan after X (= BLE_SCAN_PERIOD) ms
            btHandler = new Handler();
            btHandler.postDelayed(this::stopScan, BLE_SCAN_PERIOD);
        }
    }

    /**
     * Stops the BLE device discovery.
     */
    private void stopScan() {
        if (bleScanning && bleAdapter != null && bleAdapter.isEnabled() && bleScanner != null) {
            bleScanner.stopScan(bleScanCallback);
            scanComplete();
        }
        bleScanCallback = null;
        bleScanning = false;
        btHandler = null;
    }

    /**
     * This function handles everything that happens after a ble device discovery is complete
     */
    private void scanComplete() {
        // Broadcast signal so the activity can update the UI with the scan result
        Intent intent = new Intent();
        intent.setAction(BROADCAST_BLE_DISCOVERY_COMPLETE);
        activityContext.sendBroadcast(intent);
    }

    /**
     * Checks if the app has permissions for bluetooth
     *
     * @return boolean
     */
    public boolean hasBluetoothPermissions() {
        if (bleAdapter == null || !bleAdapter.isEnabled()) {
            return false;
        }
        return true;
    }

    /**
     * Creates an intent for bluetooth permission. Call this in your activity which implements the ble functionality
     *
     * @return Intent
     */
    public Intent requestBluetoothEnable() {
        return new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
    }

    /**
     * Disables bluetooth on the device
     */
    public void disableBluetooth() {
        bleAdapter.disable();
    }

    /**
     * Connect to discovered ble device
     *
     * @param device
     */
    public void connectDevice(BluetoothDevice device) {
        GattClientCallback gattClientCallback = new GattClientCallback();
        bleGatt = device.connectGatt(activityContext, false, gattClientCallback);
    }

    /**
     * Cancles connection between paired bluetooth devices
     */
    public void disconnectGattServer() {
        bleConnected = false;
        if (bleGatt != null) {
            bleGatt.disconnect();
            bleGatt.close();
        }
    }

    /*******************************************************************************************
     * INNER CLASSES
     *******************************************************************************************/

    /**
     * Inner Class
     * CallBack for BLE scan
     */
    private class BleScanCallback extends ScanCallback {
        @Override
        public void onScanResult(int callbackType, ScanResult result) {
            addScanResult(result);
        }

        @Override
        public void onBatchScanResults(List<ScanResult> results) {
            for (ScanResult result : results) {
                addScanResult(result);
            }
        }

        @Override
        public void onScanFailed(int errorCode) {
            // ToDo: handle failed scan
        }

        private void addScanResult(ScanResult result) {
            BluetoothDevice device = result.getDevice();
            String deviceAddress = device.getAddress();
            bleScanResults.put(deviceAddress, device);
        }
    }

    /**
     * Inner Class
     * Callback for GattClient
     */
    private class GattClientCallback extends BluetoothGattCallback {
        @Override
        public void onConnectionStateChange(BluetoothGatt gatt, int status, int newState) {
            super.onConnectionStateChange(gatt, status, newState);
            if (status == BluetoothGatt.GATT_FAILURE) {
                disconnectGattServer();
                return;
            } else if (status != BluetoothGatt.GATT_SUCCESS) {
                disconnectGattServer();
                return;
            }
            if (newState == BluetoothProfile.STATE_CONNECTED) {
                bleConnected = true;
                Intent intent = new Intent();
                intent.setAction(BROADCAST_BLE_STATUS_CONNECTED);
                activityContext.sendBroadcast(intent);
                gatt.discoverServices();
            } else if (newState == BluetoothProfile.STATE_DISCONNECTED) {
                disconnectGattServer();
            }
        }

        @Override
        public void onCharacteristicRead(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic, int status) {
            super.onCharacteristicRead(gatt, characteristic, status);
            try {
                byte[] messageBytes = characteristic.getValue();
                String messageString = new String(messageBytes, StandardCharsets.UTF_8);
                System.out.println("Characteristic: " + messageString);
                bleCharacteristic = messageString;

                // signal UI that characteristic was read
                Intent intent = new Intent();
               // intent.putExtra("actualmsg",bleCharacteristic);
                intent.setAction(BROADCAST_BLE_CHARACTERISTIC_HELLO_WORLD);
                activityContext.sendBroadcast(intent);

            } catch (Exception e) {
                e.printStackTrace();
            }
        }


        public void onServicesDiscovered(BluetoothGatt gatt, int status) {
            super.onServicesDiscovered(gatt, status);
            if (status != BluetoothGatt.GATT_SUCCESS) {
                return;
            }

            UUID uuid1 = UUID.fromString("00001802-0000-1000-8000-00805F9B34FB");
            UUID uuid2 = UUID.fromString("00002A06-0000-1000-8000-00805F9B34FB");
            BluetoothGattService service = gatt.getService(uuid1);
            // System.out.println("Service: " + service.getCharacteristics().size());
            //BluetoothGattCharacteristic characteristic = service.getCharacteristic(uuid2);
            gatt.readCharacteristic(service.getCharacteristics().get(0));
        }

        public void onCharacteristicChanged(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic) {
            super.onCharacteristicChanged(gatt, characteristic);

        }
    }
}
