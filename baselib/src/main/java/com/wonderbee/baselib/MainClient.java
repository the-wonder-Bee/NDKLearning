package com.wonderbee.baselib;

public class MainClient {

    static {
        System.loadLibrary("testlib");
    }

    public native String getString(String value);

    public native String put(String key, String value);

}