var addon = require('bindings')('app_plot');

var obj = new addon.app_plot();

var pub_port_list = [{
    'id': 1,
    'ip': "192.168.1.55"
   }/*,
    {
    'id': 8,
    'ip': "127.0.0.1"
    }*/
];

console.log(obj.set_pub_port_list(pub_port_list))
    var app_plot_buffer = new Uint32Array(8192 *7);
    obj.set_buffer(app_plot_buffer);
    var app_plot_buffer_rp = 0;
 
console.log(obj.start())
app_plot_buffer_rp=0;

function read_lwatch_data() {
    var wp = obj.get_data();
    if (wp === -1) {
        console.log("live watch disconnected");
    } else {
        while (app_plot_buffer_rp !== wp) {
            console.log("")
            var data_ts = app_plot_buffer[(app_plot_buffer_rp*7 )];
            var data_device_id = app_plot_buffer[(app_plot_buffer_rp*7 )+1];
            var data_app_id = app_plot_buffer[(app_plot_buffer_rp*7 )+2]; 
            var data_send_data = app_plot_buffer[(app_plot_buffer_rp*7 )+3];
            var data_recived_data = app_plot_buffer[(app_plot_buffer_rp*7 )+5];
             
              
            console.log("data_ts: " + data_ts);
            console.log("data_device_id: " + data_device_id);
            console.log("data_app_id: " + data_app_id);
            console.log("data_recived_data: " + data_recived_data);
            console.log("data_send_data: " + data_send_data+"\n");
                
            // }

            app_plot_buffer_rp++;
            if (app_plot_buffer_rp === 8192) {
                app_plot_buffer_rp = 0;
            }
        }
    }
}

// setInterval(() => read_lwatch_data(), 2000);
 

var count = 0;

function intervalFunc() {
  count++;
  read_lwatch_data();
  if (count == '20') {
    clearInterval(this);
  }
}
setInterval(intervalFunc, 1000);

