SUMMARY = "A free implementation of the OpenGL API"
DESCRIPTION = "Mesa is an open-source implementation of the OpenGL specification - \
a system for rendering interactive 3D graphics.  \
A variety of device drivers allows Mesa to be used in many different environments \
ranging from software emulation to complete hardware acceleration for modern GPUs. \
Mesa is used as part of the overall Direct Rendering Infrastructure and X.org \
environment."

HOMEPAGE = "http://mesa3d.org"
BUGTRACKER = "https://bugs.freedesktop.org"
SECTION = "x11"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://docs/license.html;md5=03ccdc4c379c4289aecfb8892c546f67"

INC_PR = "r4"
PE = "2"

DEPENDS = "libxml2-native makedepend-native flex-native bison-native"

PROVIDES = "virtual/libgl virtual/libgles1 virtual/libgles2 virtual/egl"

# for mesa-dri and mesa-xlib
FILESEXTRAPATHS_append := "${THISDIR}/mesa:"

inherit autotools pkgconfig pythonnative

EXTRA_OECONF = "--disable-glu \
                --disable-glw \
                --disable-glut \
                --enable-shared-glapi"

PACKAGECONFIG ??= "${@base_contains('DISTRO_FEATURES', 'x11', 'x11', '', d)}"
PACKAGECONFIG_append_x86 = " gles egl"

X11_DEPS = "xf86driproto glproto virtual/libx11 libxext libxxf86vm libxdamage libxfixes"
PACKAGECONFIG[x11] = "--enable-glx-tls,--disable-glx,${X11_DEPS}"

# Multiple virtual/gl providers being built breaks staging
EXCLUDE_FROM_WORLD = "1"

# ie mesa-dri could be empty and mesa-dri-dev RDEPENDS on it
ALLOW_EMPTY_${PN} = "1"

PACKAGES =+ "libegl libegl-dev libegl-dbg \
             libosmesa libosmesa-dev \
             libgl libgl-dev \
             libglapi libglapi-dev \
             libgbm libgbm-dev \
             libgles1 libgles1-dev \
             libgles2 libgles2-dev \
            "

do_install_append () {
    # GLU is now in libglu (this shouldn't be required in Mesa 9.x)
    rm -f ${D}${includedir}/GL/glu*
}

FILES_libegl = "${libdir}/libEGL.so.* ${libdir}/egl/*.so"
FILES_libgbm = "${libdir}/libgbm.so.*"
FILES_libgles1 = "${libdir}/libGLESv1*.so.*"
FILES_libgles2 = "${libdir}/libGLESv2.so.*"
FILES_libgl = "${libdir}/libGL.so.*"
FILES_libglapi = "${libdir}/libglapi.so.*"
FILES_libosmesa = "${libdir}/libOSMesa.so.*"

FILES_libegl-dev = "${libdir}/libEGL.* ${includedir}/EGL ${includedir}/KHR ${libdir}/pkgconfig/egl.pc"
FILES_libgbm-dev = "${libdir}/libgbm* ${libdir}/pkgconfig/gbm.pc ${includedir}/gbm.h"
FILES_libgl-dev = "${libdir}/libGL.* ${includedir}/GL ${libdir}/pkgconfig/gl.pc"
FILES_libglapi-dev = "${libdir}/libglapi.*"
FILES_libgles1-dev = "${libdir}/libGLESv1*.* ${includedir}/GLES ${libdir}/pkgconfig/glesv1*.pc"
FILES_libgles2-dev = "${libdir}/libGLESv2.* ${includedir}/GLES2 ${libdir}/pkgconfig/glesv2.pc"
FILES_libosmesa-dev = "${libdir}/libOSMesa.* ${includedir}/osmesa.h"

FILES_${PN}-dbg += "${libdir}/dri/.debug/*"
FILES_libegl-dbg += "${libdir}/egl/.debug/*"
