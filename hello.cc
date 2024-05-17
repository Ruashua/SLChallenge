#include <napi.h>
#include <string>
#include ".\obs\obs-studio\libobs\obs.h"

obs_encoder_t* videoEncoder = NULL;
obs_encoder_t* audioEncoder = NULL;
obs_service_info serviceInfo = {};
obs_output_info outputInfo = {};
obs_service_t* service = NULL;
obs_output_t* output = NULL;

Napi::String StartObs(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (obs_startup("en -US", NULL, NULL))
    {
        return Napi::String::New(env, "OBS Started");
    }
    return Napi::String::New(env, "OBS did not start.");
}

Napi::String ShutdownObs(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    obs_encoder_release(audioEncoder);
    obs_encoder_release(videoEncoder);
    obs_service_release(service);
    obs_output_release(output);

    obs_shutdown();
    return Napi::String::New(env, "OBS shutdown");
}

Napi::String ResetAudio(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    obs_audio_info oai;
    if (obs_reset_audio(&oai))
    {
        return Napi::String::New(env, "Audio reset");
    }
    return Napi::String::New(env, "Audio did not reset");
}

Napi::String ResetVideo(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    obs_video_info ovi;
    if (obs_reset_video(&ovi))
    {
        return Napi::String::New(env, "Video reset");
    }
    return Napi::String::New(env, "Video did not reset");
}

Napi::String OpenModule(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    obs_module_t* module;
    if (MODULE_SUCCESS == obs_open_module(&module, "..\\..\\obs\\obs-studio\\build\\plugins\\win-wasapi\\Release\\win-wasapi.dll", NULL))
    {
        return Napi::String::New(env, "Opened Module");
        obs_init_module(module);
        obs_post_load_modules();
    }

    return Napi::String::New(env, "Did not open Module");
}

Napi::String CreateAudioEncoder(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    audioEncoder = obs_audio_encoder_create("id", "name", NULL, 0, NULL);
    if (audioEncoder != NULL)
    {
        return Napi::String::New(env, "Audio Encoder created");
    }
    return Napi::String::New(env, "Audio Encoder not created");
}

Napi::String CreateVideoEncoder(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    videoEncoder = obs_video_encoder_create("id", "name", NULL, NULL);
    
    if (videoEncoder != NULL)
    {
        return Napi::String::New(env, "Video Encoder created");
    }
    return Napi::String::New(env, "Video Encoder not created");
}


Napi::String CreateTwitchService(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();


    serviceInfo.id = "TwitchDenver";
    serviceInfo.get_name = [](void*) -> const char* {
        return std::string("Twitch").c_str();
        };
    serviceInfo.get_url = [](void*) -> const char* {
        return std::string("rtmp://den52.contribute.live-video.net/app/").c_str();
        };
    serviceInfo.get_key = [](void*) -> const char* {
        return std::string("key").c_str();
        };
    obs_register_service(&serviceInfo);

    return Napi::String::New(env, "Service created");
}

/*
Here is where I stopped.
When I call obs_output_create in any capacity, the console says 
[23080:0517/131944.996:ERROR:crashpad_client_win.cc(868)] not connected
which looks to be a node.js error.  Maybe caused by the C++ side crashing.
I debugged my build of OBS and every time obs_output_create is called it succeeds.
Attaching the VS debugger to the process it just tells me there is an access violation
reading a memory location in the obs.dll.
This leads me to believe something is slightly off with my build environment somewhere.
*/
Napi::String CreateRtmpOutput(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    outputInfo.id = "Twitch";
    outputInfo.protocols = "RTMP";
    outputInfo.flags = OBS_OUTPUT_SERVICE || OBS_OUTPUT_AV;
    outputInfo.encoded_audio_codecs = "id";
    outputInfo.encoded_video_codecs = "id";

    obs_register_output(&outputInfo);
    

    try
    {
        
        output = obs_output_create("null_output", "null", nullptr, nullptr);
    }
    catch (...)
    {
         
    }
    
    service = obs_service_create("rtmp_common", NULL, NULL, nullptr);
    obs_output_set_service(output, service);

    if (obs_output_start(output))
    {
        //If I did everything right above, this should execute.
        //But I'm sure I didn't because I didn't link the service info with the service.
        

        obs_output_stop(output);
        return Napi::String::New(env, "RTMP output started");
    }

    return Napi::String::New(env, "RTMP output not started");
}



Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "StartObs"),
        Napi::Function::New(env, StartObs));
    exports.Set(Napi::String::New(env, "ShutdownObs"),
        Napi::Function::New(env, ShutdownObs));
    exports.Set(Napi::String::New(env, "ResetAudio"),
        Napi::Function::New(env, ResetAudio));
    exports.Set(Napi::String::New(env, "ResetVideo"),
        Napi::Function::New(env, ResetVideo));
    exports.Set(Napi::String::New(env, "OpenModule"),
        Napi::Function::New(env, OpenModule));
    exports.Set(Napi::String::New(env, "CreateAudioEncoder"),
        Napi::Function::New(env, CreateAudioEncoder));
    exports.Set(Napi::String::New(env, "CreateVideoEncoder"),
        Napi::Function::New(env, CreateVideoEncoder));
    exports.Set(Napi::String::New(env, "CreateTwitchService"),
        Napi::Function::New(env, CreateTwitchService));
    exports.Set(Napi::String::New(env, "CreateRtmpOutput"),
        Napi::Function::New(env, CreateRtmpOutput));
    return exports;
}


NODE_API_MODULE(hello, Init)