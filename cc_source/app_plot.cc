#include <thread>
#include <chrono>  
#include <mutex>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "app_plot.h"
#include "app_pub.h"
#include "app_sub.h"
 
// std::mutex myMutex;

Napi::Object app_plot::Init(Napi::Env env, Napi::Object exports) {
  Napi::Function func =
      DefineClass(env,"app_plot",{
                  InstanceMethod("start", &app_plot::start),
                  InstanceMethod("set_pub_port_list", &app_plot::set_pub_port_list),
                  InstanceMethod("example", &app_plot::example)});

  Napi::FunctionReference* constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent(func);
  env.SetInstanceData(constructor);

  exports.Set("app_plot", func);
  return exports;
}

app_plot::app_plot(const Napi::CallbackInfo& info):Napi::ObjectWrap<app_plot>(info) {
  printf("Hello this is from C side\n");
}

Napi::Value app_plot::set_pub_port_list(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    struct in_addr ip_addr;
    int info_length = info.Length();

    if (info_length <= 0 || !info[0].IsArray()) {
        printf(  "PQ :: LWATCH :: SET HA LIST :: Invalid Arguments"   "\n");
        return Napi::String::New(env, "failed");
    }
    Napi::Array array = info[0].As<Napi::Array>();
    Napi::Object obj;
    for (uint32_t count = 0; count < array.Length(); count++) {
        Napi::Value v = array[count];
        obj = v.ToObject();
        printf(  "PQ :: LWATCH :: SET HA  :: %s"   "\n", ((std::string)obj.Get("ip").As<Napi::String>()).c_str());
        if (inet_pton(AF_INET, ((std::string)obj.Get("ip").As<Napi::String>()).c_str(), &(ip_addr.s_addr)) == 0) {
            printf(  "PQ :: LWATCH :: SET HA :: Invalid Device IP"   "\n");
            return Napi::String::New(env, "failed");
        }
        pub_port_list[pub_port_list_len] = ip_addr;
        pub_port_list_len++;
    }
    printf(  "PQ :: LWATCH :: SET HA LIST :: %u"  , array.Length());
    return Napi::String::New(env, "success");
}





Napi::Value app_plot::example(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env(); 
    return Napi::String::New(env,"some string test");
}


Napi::Value app_plot::start(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::String returnValue = Napi::String::New(env, " hello this is from App_plot module");

    /*commit thread*/
    std::thread th_pub;
    th_pub = std::thread([this] {
        app_plot_req_pub_thread(); });
    th_pub.detach();

    std::thread th_sub;
    th_sub = std::thread([this] {
        app_plot_data_sub_thread(); });
    th_sub.detach();
    return returnValue;
}

 

void app_plot::app_plot_req_pub_thread() {
    app_device_config_init_connector_pub();
}

void app_plot::app_plot_data_sub_thread() {
    app_plot_config_init_connector_sub();
}


 
Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return app_plot::Init(env, exports);
}

NODE_API_MODULE(app_plot, InitAll)