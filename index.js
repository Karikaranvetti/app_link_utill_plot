var addon = require('bindings')('app_plot');

var obj = new addon.app_plot();
console.log( obj.example() ); // 11npm 
console.log(obj.start())

setTimeout(() => {
    console.log(obj.start());
},10000)

// while(true){}



