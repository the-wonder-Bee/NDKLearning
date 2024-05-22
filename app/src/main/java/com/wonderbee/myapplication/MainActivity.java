package com.wonderbee.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.wonderbee.baselib.MainClient;

import java.util.List;

public class MainActivity extends AppCompatActivity {
    private static final  String TAG  = "MainActivity";
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
//        TextView tv = findViewById(R.id.sample_text);
//        tv.setText(stringFormJNI());
//        tv.setText(getSum(1,3)+"");
//        for (char c : getChars('a', 'b')){
//            Log.d(TAG, "chars: "+ c);
//        }

//        for (byte b : getByteArray((byte)0, (byte)10)) {
//            Log.d(TAG, "bytes: "+ b);
//        }
//        for (boolean b : getBooleanArray(true, 10)) {
//            Log.d(TAG, "booleans: "+ b);
////        }
//        for (short b : getShortArray((short) 0, (short)10)) {
//            Log.d(TAG, "shorts: "+ b);
//        }

//        for (int i : getIntArray(0, 10)) {
//            Log.d(TAG, "ints: "+i);
//        }

//        for (float f : getFloatArray(1, 10, 1.5f)) {
//            Log.d(TAG, "onFloat: "+f);
//        }

//        for (double d : getDoubleArray(1, 10, 2.500)) {
//            Log.d(TAG, "onDouble: "+d);
//        }
//        for (String str : getStringArray(1, 10, "hello")) {
//            Log.d(TAG, "onString[]: "+str);
//        }

//        Log.d(TAG, "getStrudent: "+getStudent());

        MainClient client = new MainClient();
        Log.d(TAG, "onCreate: "+client.put("Hello", "World!"));

        testVoid();

        try {
            testThrowException();
        }catch (Exception e) {
            Log.d(TAG, "onCreate: "+e.getMessage());
            Log.d(TAG, "onCreate: "+e.getClass().getName());
        }

        List<Student> studentList = getStudentList(5);
        Log.d(TAG, "onCreate: "+studentList.getClass().getName());
        for (Student student : studentList) {
            Log.d(TAG, "onCreate: "+student);
        }

//        testThread();

        String json = testNet();
        TextView textView = findViewById(R.id.sample_text);
        textView.setText(json);

    }

    /**
     * 返回一个字符串
     * @return
     */
    public native String stringFormJNI();


    /**
     * 传入两个int 参数并返回他们的和
     * @param p
     * @param q
     * @return
     */
    public native int getSum(int p, int q);

    public native byte[] getByteArray(byte left, byte right);

    public native short[] getShortArray(short left, short right);

    public native char[] getChars(char p, char q);

    public native int[] getIntArray(int left, int right);

    public native boolean[] getBooleanArray(boolean isTrue, int size);

    public native float[] getFloatArray(int left, int right, float value);

    public native double[] getDoubleArray(int left, int right, double value);

    public native String[] getStringArray(int left, int right, String value);

    public native List<Student> getStudentList(int size);

    public native Student getStudent();

    public native void testVoid();

    public native void testThrowException();

    public native void testThread();
    public native String testNet();
}