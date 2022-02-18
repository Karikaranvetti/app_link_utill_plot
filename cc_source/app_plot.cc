#include <thread>
#include <chrono>  
#include <mutex>
#include "app_plot.h"
#include "app_pub.h"
#include "app_sub.h"
 
// std::mutex myMutex;

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
    Napi::String returnValue = Napi::String::New(env, " hello this is from App_plot module");
     void* socket=app_device_config_init_connector_pub();
    /*commit thread*/
    std::thread th_pub1;
    th_pub1 = std::thread([this,socket] {
        app_plot_req_pub_thread1(socket); });
    th_pub1.detach();

    std::thread th_pub2;
    th_pub2 = std::thread([this,socket ]{
        app_plot_req_pub_thread2(socket); });
    th_pub2.detach();

    std::thread th_sub;
    th_sub = std::thread([this] {
        app_plot_data_sub_thread(); });
    th_sub.detach();

    // std::this_thread::sleep_for(std::chrono::seconds(10));
    return returnValue;
}

 

void app_plot::app_plot_req_pub_thread1(void* sock) {
   void * socket=sock;
//    std::lock_guard<std::mutex> guard(myMutex);
    pub_topic_send(socket,"ABC");

}

void app_plot::app_plot_req_pub_thread2(void* sock) {
    void* socket=sock;
    // std::lock_guard<std::mutex> guard(myMutex);
    pub_topic_send(socket,"PQR");

}

void app_plot::app_plot_data_sub_thread() {
    app_plot_config_init_connector_sub();
}

 
Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return app_plot::Init(env, exports);
}

NODE_API_MODULE(app_plot, InitAll)