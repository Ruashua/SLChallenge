{
"targets": [
{
"target_name": "hello",
"cflags!": ["-fPIC"],
"cflags_cc!": ["-fPIC"],
"ldflags" : ["-Wl,-static"],
"sources": ["hello.cc"],
"libraries": [
	"<(module_root_dir)/obs/obs-studio/build/libobs/Release/obs.lib"
],
"include_dirs": [
"<!@(node -p \"require('node-addon-api').include\")",
"<(module_root_dir)/obs/obs-studio/libobs",
],
"copies": [
              {
                "destination": "<(module_root_dir)/build/Release/",
                "files": [ 
                    "<(module_root_dir)/obs/obs-studio/build/rundir/Release/bin/64bit/avcodec-61.dll",
                    "<(module_root_dir)/obs/obs-studio/build/rundir/Release/bin/64bit/avdevice-61.dll",
                    "<(module_root_dir)/obs/obs-studio/build/rundir/Release/bin/64bit/avfilter-10.dll",
                    "<(module_root_dir)/obs/obs-studio/build/rundir/Release/bin/64bit/avformat-61.dll",
                    "<(module_root_dir)/obs/obs-studio/build/rundir/Release/bin/64bit/avutil-59.dll",
                    "<(module_root_dir)/obs/obs-studio/build/rundir/Release/bin/64bit/datachannel.dll",
                    "<(module_root_dir)/obs/obs-studio/build/rundir/Release/bin/64bit/libcurl.dll",
                    "<(module_root_dir)/obs/obs-studio/build/rundir/Release/bin/64bit/libobs-d3d11.dll",
                    "<(module_root_dir)/obs/obs-studio/build/rundir/Release/bin/64bit/libobs-opengl.dll",
                    "<(module_root_dir)/obs/obs-studio/build/rundir/Release/bin/64bit/libobs-winrt.dll",
                    "<(module_root_dir)/obs/obs-studio/build/rundir/Release/bin/64bit/librist.dll",
                    "<(module_root_dir)/obs/obs-studio/build/rundir/Release/bin/64bit/libx264-164.dll",
                    "<(module_root_dir)/obs/obs-studio/build/rundir/Release/bin/64bit/lua51.dll",
                    "<(module_root_dir)/obs/obs-studio/build/rundir/Release/bin/64bit/obs.dll",
                    "<(module_root_dir)/obs/obs-studio/build/rundir/Release/bin/64bit/obs-frontend-api.dll",
                    "<(module_root_dir)/obs/obs-studio/build/rundir/Release/bin/64bit/obs-scripting.dll",
                    "<(module_root_dir)/obs/obs-studio/build/rundir/Release/bin/64bit/Qt6Core.dll",
                    "<(module_root_dir)/obs/obs-studio/build/rundir/Release/bin/64bit/Qt6Gui.dll",
                    "<(module_root_dir)/obs/obs-studio/build/rundir/Release/bin/64bit/Qt6Network.dll",
                    "<(module_root_dir)/obs/obs-studio/build/rundir/Release/bin/64bit/Qt6Svg.dll",
                    "<(module_root_dir)/obs/obs-studio/build/rundir/Release/bin/64bit/Qt6Widgets.dll",
                    "<(module_root_dir)/obs/obs-studio/build/rundir/Release/bin/64bit/Qt6Xml.dll",
                    "<(module_root_dir)/obs/obs-studio/build/rundir/Release/bin/64bit/srt.dll",
                    "<(module_root_dir)/obs/obs-studio/build/rundir/Release/bin/64bit/swresample-5.dll",
                    "<(module_root_dir)/obs/obs-studio/build/rundir/Release/bin/64bit/swscale-8.dll",
                    "<(module_root_dir)/obs/obs-studio/build/rundir/Release/bin/64bit/w32-pthreads.dll",
                    "<(module_root_dir)/obs/obs-studio/build/rundir/Release/bin/64bit/zlib.dll",
                
                
                ]

              }
 ],
'defines': ['NAPI_DISABLE_CPP_EXCEPTIONS'],
}
]
}