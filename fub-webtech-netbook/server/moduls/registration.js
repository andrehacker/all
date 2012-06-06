var events = require("events");
var Customer = require('./customer.js');

function Registration(mainDb) {
	this.customer = new Customer(mainDb);
	events.EventEmitter.call(this);
}


// inherit events.EventEmitter
Registration.super_ = events.EventEmitter;
//All Methods get the EventEmitter
Registration.prototype = Object.create(events.EventEmitter.prototype, {
    constructor: {
        value: Registration,
        enumerable: false
    }
});


Registration.prototype.webHandel = function(res, req) {
	if(req.body.txtRegCustomerName == ""){
		res.send({'failure' : "Name must be set."});
		return false;
	}
	if(req.body.txtRegPassword == ""){
		res.send({'failure' : "Password must be set."});
		return false;
	}
	if(req.body.txtRegAddress == ""){
		res.send({'failure' : "Address must be set"});
		return false;
	}
	var self = this;
	self.customer.create(req.body.txtRegCustomerName,
    				 req.body.txtRegPassword,
    				 req.body.txtRegAddress,
    				 false // isAdmin
	);
	self.customer.on('success',function(newCustomerInJSON){
		res.send({'success': 'Successfully registered', 'customer': newCustomerInJSON[0]});
	}).on('failure', function(error){
		res.send({'failure' : error});
	});
}


module.exports = Registration;
