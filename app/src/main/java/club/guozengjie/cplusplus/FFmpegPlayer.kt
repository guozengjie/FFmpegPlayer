package club.guozengjie.cplusplus

import android.util.Log
import android.view.SurfaceHolder
import android.view.SurfaceView


class FFmpegPlayer {
    private lateinit var url: String
    val tag: String = "FFmpegPlayer"

    companion object {
        init {
            System.loadLibrary("native-lib")
        }
    }

    /**
     * 设置SurfaceView
     */
    fun setSurfaceView(surfaceView: SurfaceView) {
        surfaceView.holder.addCallback(object : SurfaceHolder.Callback {
            override fun surfaceChanged(
                holder: SurfaceHolder?,
                format: Int,
                width: Int,
                height: Int
            ) {
                Log.e(tag, "surfaceChanged:width:${width} height${height}")
            }

            override fun surfaceDestroyed(holder: SurfaceHolder?) {
                Log.e(tag, "surfaceDestroyed")
            }

            override fun surfaceCreated(holder: SurfaceHolder?) {
                Log.e(tag, "surfaceCreated")
            }

        })
    }

    external fun jniPrepare(url: String)

    /**
     * 准备播放
     */
    fun prepare(url: String) {
        this.url = url
        jniPrepare(url)
    }
}