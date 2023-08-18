package com.example.prime

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import com.example.prime.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding
    private var nativeWrapper: Long = 0L;
    private val calculatingStatusHint: String = "Calculating..."

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        nativeWrapper = nativeCreatePrimeNumberHandle();

        binding.buttonClr.setOnClickListener {
            binding.editTextInput.text = null
            binding.outputText.text = null
        }

        binding.buttonRun.setOnClickListener {
            binding.buttonRun.isEnabled = false
            binding.buttonClr.isEnabled = false
            binding.outputText.text = calculatingStatusHint
            Thread {
                val output: String = if (nativeWrapper != 0L) {
                    nativeGetStringOfPrimeNumbers(nativeWrapper,
                        binding.editTextInput.text.toString())
                } else {
                    "Error: 100"
                }

                runOnUiThread {
                    binding.outputText.text = output
                    binding.buttonClr.isEnabled = true
                    binding.buttonRun.isEnabled = true
                }
            }.start()
        }


    }

    override fun onDestroy() {
        if (nativeWrapper != 0L) {
            nativeDestroyPrimeNumberHandle(nativeWrapper)
            nativeWrapper = 0L
        }
        super.onDestroy()
    }

    override fun onResume() {
        super.onResume()

        if (nativeWrapper != 0L)
            nativeResumeWorkers(nativeWrapper)
    }

    override fun onPause() {
        if (nativeWrapper != 0L)
            nativePauseWorkers(nativeWrapper)

        super.onPause()
    }

    /**
     * A native method that is implemented by the 'prime' native library,
     * which is packaged with this application.
     */
    external fun nativeCreatePrimeNumberHandle(): Long
    external fun nativeGetStringOfPrimeNumbers(nativeWrapper: Long, str: String): String
    external fun nativeDestroyPrimeNumberHandle(nativeWrapper: Long)
    external fun nativeResumeWorkers(nativeWrapper: Long)
    external fun nativePauseWorkers(nativeWrapper: Long)

    companion object {
        // Used to load the 'prime' library on application startup.
        init {
            System.loadLibrary("prime")
        }
    }
}