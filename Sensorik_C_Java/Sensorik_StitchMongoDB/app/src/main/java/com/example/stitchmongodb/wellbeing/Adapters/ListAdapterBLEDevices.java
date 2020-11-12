package h_da.wellbeing.Adapters;

import android.bluetooth.BluetoothDevice;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.Map;

import h_da.wellbeing.R;

public class ListAdapterBLEDevices extends BaseAdapter {
    private final ArrayList mData;

    public ListAdapterBLEDevices(Map<String, BluetoothDevice> map) {
        mData = new ArrayList();
        mData.addAll(map.values());
    }

    @Override
    public int getCount() {
        return mData.size();
    }

    @Override
    public BluetoothDevice getItem(int position) {
        return (BluetoothDevice) mData.get(position);
    }

    @Override
    public long getItemId(int position) {
        // TODO implement you own logic with ID
        return 0;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        final View result;
        BluetoothDevice item = getItem(position);
        String deviceName = "";
        String deviceAddress = item.getAddress();

        if (convertView == null) {
            result = LayoutInflater.from(parent.getContext()).inflate(R.layout.list_item_ble_device, parent, false);
        } else {
            result = convertView;
        }

        if (item.getName() == null) {
            deviceName = "N/A";
        } else {
            deviceName = item.getName();
        }

        ((TextView) result.findViewById(android.R.id.text1)).setText(deviceName);
        ((TextView) result.findViewById(android.R.id.text2)).setText(deviceAddress);

        return result;
    }
}