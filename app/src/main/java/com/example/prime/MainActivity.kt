package com.example.prime

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import com.example.prime.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = nativeGetStringOfPrimeNumbers(" 30 -123456 16.7 ,, 8 9 -10 --== +22 34 45 56 67 78 89 90")
        binding.buttonClr.isEnabled = false
    }

    /**
     * A native method that is implemented by the 'prime' native library,
     * which is packaged with this application.
     */
    external fun nativeGetStringOfPrimeNumbers(str: String): String

    companion object {
        // Used to load the 'prime' library on application startup.
        init {
            System.loadLibrary("prime")
        }
    }
}