var util = require("util");
var events = require("events");
var Customer = require('./customer.js');



function Auth(mainDb) {
	this.customer = new Customer(mainDb);
	events.EventEmitter.call(this);
}

util.inherits(Auth, events.EventEmitter);

Auth.prototype.login = function(user, password) {
	var self = this;
	self.customer.getCustomerByName(user);
  	self.customer.on('success', function successFindUser(result){
		if(result[0].password == password &&	result[0].name == user){
			self.emit('success', result[0]);
		}
		else{
			self.emit('failure', "Password wrong.");
		}
	}).on('failure', function failureFindUser(error){
		self.emit('failure', error);
	});
}

Auth.prototype.getAuthInfo = function(req, res) {
	var self = this;
	if(req.session.auth != true){
		res.send({'info' : 'Customer not login.'});
	}
	else{
		self.customer.getCustomerById(req.session.customer_id);
		self.customer.on('success',function(customerInJSON){
			res.send({'info':'Customer information loaded.', 'customer': customerInJSON[0]});
		});
		self.customer.on('failure', function(error){
			res.send({'failure' : error});
		});
	}
}

/*
var auth = new Auth();
auth.on("success", function(result) {
console.log('Login with User: ' + result.name + ' Password: ' + result.password + ' was successfull');
	return true;
})
auth.on("failure", function(result) {
	console.log(false);
	return false;
})

auth.login("simon","pw"); // Received data: "It works!"
*/

module.exports = Auth;

