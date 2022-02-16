#include "app_plot.h"
#include "app_pub.h"
#include "app_sub.h"
#include <thread>
 


Napi::Object app_plot::Init(Napi::Env env, Napi::Object exports) {
  Napi::Function func =
      DefineClass(env,"app_plot",{
                  InstanceMethod("start", &app_plot::start),
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

Napi::Value app_plot::example(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env(); 
    return Napi::String::New(env,"some string test");
}


Napi::Value app_plot::start(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::String returnValue = Napi::String::New(env, "this is hello hasidi from App_plot module");

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