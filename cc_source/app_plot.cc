#include <thread>
#include <chrono>
#include <mutex>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "app_plot.h"
#include "app_pub.h"
#include "app_sub.h"
#include "app_data_process.h"
#include "app_deff.h"

// std::mutex myMutex;

Napi::Object app_plot::Init(Napi::Env env, Napi::Object exports)
{
    Napi::Function func = DefineClass(env, "app_plot", {InstanceMethod("start", &app_plot::start), InstanceMethod("set_pub_port_list", &app_plot::set_pub_port_list), InstanceMethod("set_buffer", &app_plot::set_buffer), InstanceMethod("get_data", &app_plot::get_data)});

    Napi::FunctionReference *constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);

    exports.Set("app_plot", func);
    return exports;
}

app_plot::app_plot(const Napi::CallbackInfo &info) : Napi::ObjectWrap<app_plot>(info) {}

Napi::Value app_plot::set_pub_port_list(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    struct in_addr ip_addr;
    int info_length = info.Length();

    if (info_length <= 0 || !info[0].IsArray())
    {
        printf(" Invalid Arguments"
               "\n");
        return Napi::String::New(env, "failed");
    }
    Napi::Array array = info[0].As<Napi::Array>();
    Napi::Object obj;
    for (uint32_t count = 0; count < array.Length(); count++)
    {
        Napi::Value v = array[count];
        obj = v.ToObject();
        printf("APP_PLOT :: SET IP  :: %s"
               "\n",
               ((std::string)obj.Get("ip").As<Napi::String>()).c_str());
        if (inet_pton(AF_INET, ((std::string)obj.Get("ip").As<Napi::String>()).c_str(), &(ip_addr.s_addr)) == 0)
        {
            printf("APP_PLOT :: SET IP  :: Invalid Device IP"
                   "\n");
            return Napi::String::New(env, "failed");
        }
        pub_port_list[pub_port_list_len] = ip_addr;
        pub_port_list_len++;
    }
    

    return Napi::String::New(env, "success");
}

Napi::Value app_plot::set_buffer(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    if (!info[0].IsTypedArray())
    {
        printf(" APP_PLOT :: SET BUFFERS :: Invalid Arguments"
               "\n");
        return Napi::String::New(env, "failed");
    }
    data_que = (device_data *)info[0].As<Napi::Uint16Array>().Data();
    return Napi::String::New(env, "success");
}

Napi::Value app_plot::get_data(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    return Napi::Number::New(env, data_count.count);
}

Napi::Value app_plot::start(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::String returnValue = Napi::String::New(env, "success");

    /*commit thread*/
    std::thread th_pub;
    th_pub = std::thread([this]
                         { app_plot_req_pub_thread(); });
    th_pub.detach();

    std::thread th_sub;
    th_sub = std::thread([this]
                         { app_plot_data_sub_thread(); });
    th_sub.detach();

    std::thread th_process;
    th_sub = std::thread([this]
                         { app_plot_data_process_thread(); });
    th_sub.detach();

    return returnValue;
}

void app_plot::app_plot_req_pub_thread()
{
    app_device_config_init_connector_pub();
}

void app_plot::app_plot_data_sub_thread()
{
    app_plot_config_init_connector_sub();
}

void app_plot::app_plot_data_process_thread()
{

    data_process();
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports)
{
    return app_plot::Init(env, exports);
}

NODE_API_MODULE(app_plot, InitAll)