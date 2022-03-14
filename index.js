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
var lwatch_buffer_rp = [0]; // this shoud be circuler 4096

for (var array_count = 0; array_count < 2; array_count++) {
    app_plot_buffer[array_count] = new Uint32Array(4096 * 50);
    obj.set_buffer(array_count, app_plot_buffer[array_count]);
    lwatch_buffer_rp[array_count] = 0;
}
console.log( obj.example() ); // 11npm 
console.log(obj.start())



while(true){
    setTimeout(() => {
        // console.log(obj.start());
        // result=obj.get_data();
        for(let i = 0; i < app_plot_buffer[0].length; i++){
            console.log("\nHere is time stamp"+app_plot_buffer[0][i].ts +"\n")

        }
    },10000)
}



