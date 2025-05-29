package com.pushpen.myopenglshader.view

import android.content.Context
import android.opengl.GLSurfaceView
import com.pushpen.myopenglshader.renderer.MyRenderer

class MyGLSurfaceView(context: Context) : GLSurfaceView(context) {
    private val renderer: MyRenderer

    init {
        setEGLContextClientVersion(2)
        renderer = MyRenderer()
        setRenderer(renderer)
    }
}
