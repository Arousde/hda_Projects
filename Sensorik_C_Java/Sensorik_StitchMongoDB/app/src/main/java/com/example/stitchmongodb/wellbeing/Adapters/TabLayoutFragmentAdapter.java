
package h_da.wellbeing.Adapters;

import android.content.Context;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;

import h_da.wellbeing.Fragments.fragment_Humidity;
import h_da.wellbeing.Fragments.fragment_Particulates;
import h_da.wellbeing.Fragments.fragment_co2;
import h_da.wellbeing.Fragments.fragment_pressure;
import h_da.wellbeing.Fragments.fragment_temperature;
import h_da.wellbeing.R;

/*>
    This class is the AdapterClass for the Tablayout
 */
public class TabLayoutFragmentAdapter extends FragmentPagerAdapter {

    private Context mContext;

    public TabLayoutFragmentAdapter(Context context, FragmentManager fm) {
        super(fm);
        mContext = context;
    }

    /*
        This Class returns the fragment which is selected
     */
    @Override
    public Fragment getItem(int i) {

        switch (i)
        {
            case 0: //Temperature Sensor
            {
                return new fragment_temperature();
            }
            case 1: //pressure Sensor
            {
                return new fragment_pressure();
            }
            case 2: //humidty sensor
            {
                return new fragment_Humidity();
            }
            case 3://CO2 sensor
            {
                return new fragment_co2();
            }
            case 4://Partiiculates Sensor
            {
                return new fragment_Particulates();
            }
            default:
            {
                return  null;
            }
        }

    }
    /*
        Returns the amount of tabs
     */
    @Override
    public int getCount() {
        return 5;
    }

    @Nullable
    @Override
    public CharSequence getPageTitle(int position) {

        switch (position)
        {
            case 0:
            {
                return mContext.getString(R.string.Temperature);
            }
            case 1:
            {
                return mContext.getString(R.string.pressure);
            }
            case 2:
            {
                return mContext.getString(R.string.humidty);
            }
            case 3:
            {
                return mContext.getString(R.string.Gas);
            }
            case 4:
            {
                return mContext.getString(R.string.particulate);
            }
            default:
            {
                return null;
            }
        }

    }
}
