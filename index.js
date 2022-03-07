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
console.log( obj.example() ); // 11npm 
console.log(obj.start())

setTimeout(() => {
    // console.log(obj.start());
},10000)

// while(true){}



