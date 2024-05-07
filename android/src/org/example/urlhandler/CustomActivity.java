package org.example.urlhandler;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.content.res.Configuration;
import android.util.Log;

import java.lang.String;
import java.lang.StringBuilder;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.qtproject.qt.android.bindings.QtActivity;
import org.qtproject.qt.android.bindings.QtApplication;

public class CustomActivity extends QtActivity
{
    /* Handle application launch from a hyperlink
     * e.g. custom://example.org/register/?label=Hello
     * If no instance of the app is running, onCreate() is called and we pass
     * the URL parameters as arguments to the app's main().
     * If the app is already running, onNewIntent() is called and the URL
     * parameters are sent as signals to the app via UrlHandler.
    */

    private static final String TAG = "custom";

    // Defined in urlhandler.cpp
    public static native void handleAndroidUrl(String url);

    @Override
    public void onCreate(Bundle savedInstanceState) {
        // Called when no instance of the app is running. Pass URL parameters
        // as arguments to the app's main()
        Intent intent = getIntent();

        Log.i(TAG, "onCreate");

        if (intent != null && intent.getAction() == Intent.ACTION_VIEW) {
            Uri uri = intent.getData();
            if (uri != null) {
                Log.i(TAG, intent.getDataString());

                Map<String, String> parameters = getQueryParameters(uri);

                // String.join() not available at runtime
                StringBuilder sb = new StringBuilder();

                String separator = "";
                for (Map.Entry<String, String> entry : parameters.entrySet()) {
                    String name = entry.getKey();
                    String value = entry.getValue();
                    if (value != null) {
                        sb.append(separator)
                            .append("--").append(name)
                            .append("=").append(value);

                        separator = "\t";
                    }
                }

                APPLICATION_PARAMETERS = sb.toString();
            } else {
                Log.i(TAG, "URI is NULL");
            }

        }

        super.onCreate(savedInstanceState);
    }

    @Override
    public void onNewIntent(Intent intent) {
        /* Called when the app is already running. Send the URL parameters
         * as signals to the app. If the user has already registered manually,
         * this will have no effect.
         */
        Log.i(TAG, "onNewIntent");

        super.onNewIntent(intent);

        sendUrlToApp(intent);
    }

    private void sendUrlToApp(Intent intent) {
        Log.i(TAG, "sendUrlToApp");

        String url = intent.getDataString();

        if (url != null) {
            Log.i(TAG, url);

            handleAndroidUrl(url);
        } else {
            Log.i(TAG, "URL is NULL");
        }
    }

    private Map<String, String> getQueryParameters(Uri uri) {
        List<String> names = Arrays.asList("label");

        Map<String, String> parameters = new HashMap<String, String>();

        for (String name : names) {
            String value = uri.getQueryParameter(name);
            if (value != null) {
                parameters.put(name, value);
            }
        }

        return parameters;
    }
}
