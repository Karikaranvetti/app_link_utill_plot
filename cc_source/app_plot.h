#include <napi.h>
#include <cstdlib>
#include <atomic>
#include <string>
#include <unistd.h>
#include <iostream>
#include <memory>

using namespace std;

class app_plot : public Napi::ObjectWrap<app_plot> {
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    app_plot(const Napi::CallbackInfo& info);
    Napi::Value example(const Napi::CallbackInfo& info);
    Napi::Value start(const Napi::CallbackInfo& info);
    Napi::Value set_pub_port_list(const Napi::CallbackInfo& info);

private:
  
    void app_plot_req_pub_thread1(void* sock);
    void app_plot_req_pub_thread();
    void app_plot_data_sub_thread();
    void app_plot_synq_thread();
};
 
