package com.pushpen.myopenglshader.renderer

import android.opengl.EGLConfig
import android.opengl.GLSurfaceView
import javax.microedition.khronos.opengles.GL10

class MyRenderer : GLSurfaceView.Renderer {
    external fun nativeInit()
    external fun nativeRender(width: Int, height: Int)

    override fun onSurfaceCreated(gl: GL10?, config: javax.microedition.khronos.egl.EGLConfig?) {
        nativeInit()
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        nativeRender(width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
        nativeRender(0, 0)
    }

    companion object {
        init {
            System.loadLibrary("native-lib")
        }
    }
}
