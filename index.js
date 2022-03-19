var addon = require('bindings')('app_plot');

var obj = new addon.app_plot();

var pub_port_list = [{
    'id': 1,
    'ip': "192.168.1.55"
   }/*,
    {
    'id': 8,
    'port':809,
    'ip': "127.0.0.1"
    }*/
];

console.log(obj.set_pub_port_list(pub_port_list))



var app_plot_buffer = [];
var app_plot_buffer_rp = [0]; // this shoud be circuler 4096

for (var array_count = 0; array_count < 2; array_count++) {
    app_plot_buffer[array_count] = new Uint32Array(4096 *7);
    obj.set_buffer(array_count, app_plot_buffer[array_count]);
    app_plot_buffer_rp[array_count] = 0;
}
console.log( obj.example() ); // 11npm 
console.log(obj.start())
app_plot_buffer_rp[0]=0;

function read_lwatch_data() {
    var wp = obj.get_watch(0);
    if (wp === -1) {
        console.log("live watch disconnected");
    } else {
        while (app_plot_buffer_rp[0] !== wp) {
            console.log("")
            var data_ts = app_plot_buffer[0][(app_plot_buffer_rp[0]*7 )];
            var data_device_id = app_plot_buffer[0][(app_plot_buffer_rp[0]*7 )+1];
            var data_app_id = app_plot_buffer[0][(app_plot_buffer_rp[0]*7 )+2]; 
            var data_send_data = app_plot_buffer[0][(app_plot_buffer_rp[0]*7 )+3];
            var data_recived_data = app_plot_buffer[0][(app_plot_buffer_rp[0]*7 )+5];
             
            // console.log(data_ts+"and "+data_device_id+"and "+data_app_id+"and"+data_send_data+"and"+data_recived_data);
             
                console.log("data_ts: " + app_plot_buffer_rp[0]*7  + " " + data_ts);
                console.log("data_device_id: " + (app_plot_buffer_rp[0]*7 +1)  + " " + data_device_id);
                console.log("data_app_id: " + (app_plot_buffer_rp[0]*7 +2)  + " " + data_app_id);
                console.log("data_recived_data: " + (app_plot_buffer_rp[0]*7 +5)  + " " + data_recived_data);
                console.log("data_send_data: " + (app_plot_buffer_rp[0]*7 +3)  + " " + data_send_data+"\n");
                
            // }

            app_plot_buffer_rp[0]++;
            if (app_plot_buffer_rp[0] === 4096) {
                app_plot_buffer_rp[0] = 0;
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
setInterval(intervalFunc, 2000);

