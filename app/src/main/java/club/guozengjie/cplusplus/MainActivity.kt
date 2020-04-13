package club.guozengjie.cplusplus

import android.os.Bundle
import android.view.View
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {
    private lateinit var player: FFmpegPlayer
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        //初始化播放器
        initFFmpegPlayer()
    }

    private fun initFFmpegPlayer() {
        player = FFmpegPlayer().apply {
            setSurfaceView(surfaceView)
        }
    }

    fun start(view: View) {
        Toast.makeText(this, "播放", Toast.LENGTH_LONG).show()
        player.prepare("http://cbnlive.cbchot.com/live/yt_chc_h_1.m3u8?123")
    }
}
