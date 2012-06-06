var events = require("events");
//var db = require('./ormapper.js');

// for us to do a require later
module.exports = Customer;

function Customer(mainDB) {
	this.db = mainDB;
﻿  events.EventEmitter.call(this);
}


// inherit events.EventEmitter
Customer.super_ = events.EventEmitter;
//All Methods get the EventEmitter
Customer.prototype = Object.create(events.EventEmitter.prototype, {
    constructor: {
        value: Customer,
        enumerable: false
    }
});

Customer.prototype.create = function(customer_name, customer_password, customer_address, customer_isAdmin) {
﻿  var self = this;
﻿  if(customer_isAdmin == "true" || customer_isAdmin)
﻿      ﻿  customer_isAdmin = true;
﻿      else
﻿      ﻿  customer_isAdmin = false;
    self.db.Customer.find(
﻿  ﻿  {where: {'name': customer_name, 'deleted': false} }
﻿  ).on('success', function dbCustomerExists(result) {
﻿  ﻿  if(result == undefined){
﻿  ﻿  ﻿  self.createHelper(self, customer_name, customer_password, customer_address, customer_isAdmin);
﻿  ﻿  }
﻿  ﻿  else{
﻿  ﻿  ﻿  self.emit('failure', "Customer Name already exsits.");
﻿  ﻿  }﻿  ﻿  
﻿  }).on('failure', function dbCustomerNotExists(error){
﻿  ﻿  self.createHelper(self, customer_name, customer_password, customer_address, customer_isAdmin);
﻿  });
}
Customer.prototype.createHelper = function(self, customer_name, customer_password, customer_address, customer_isAdmin) {
﻿  console.log('Create Customer (Name: ' + customer_name + ' Password: ' + customer_password + ')');
﻿  var newCustomer = self.db.Customer.build({'name': customer_name, 'password': customer_password, 'address': customer_address, 'isAdmin': customer_isAdmin});
﻿  newCustomer.save().on('success', function newCustomerSuccess(newCustomer){
﻿  ﻿  self.emit('success', self.customerToJSON([newCustomer]));
﻿  }).on('failure', function newCustomerFailure(){
﻿  ﻿  ﻿  self.emit('failure', "Customer can not create.");
﻿  });
}

Customer.prototype.update = function(customerId, customer_name, customer_password, customer_address, customer_isAdmin) {
﻿  var self = this;
    self.db.Customer.find({ where: {'deleted': false, 'id': customerId} }).on('success', function updateFindCustomer(customer){
    ﻿  customer.name = customer_name;
    ﻿  customer.password = customer_password;
    ﻿  customer.address = customer_address;
    ﻿  if(customer_isAdmin == "true")
﻿      ﻿  customer.isAdmin = true;
﻿      else
﻿      ﻿  customer.isAdmin = false;
    ﻿  customer.save().on('success', function dbCustomerUpdate(updateCustomer) {
﻿  ﻿  ﻿  console.log('Update Customer (#' + updateCustomer.name + ').');
﻿  ﻿  ﻿  self.emit('success', self.customerToJSON([updateCustomer]));
﻿  ﻿  }).on('failure', function dbCustomerUpdateError(error){
﻿  ﻿  ﻿  self.emit('failure', "Customer update error.");
﻿  ﻿  });
    }).on('failure', function updateFindCustomerFailure(){
    ﻿  self.emit('failure', "Customer update error (Customer not found).");
    });
}

Customer.prototype.remove = function(customerId) {
﻿  var self = this;
﻿  console.log('To Deleted Customer: ' + customerId);
﻿  self.db.Customer.find({ where: {'deleted': false, 'id': customerId} }).on('success',function dbCustomerExists(toDeletedCustomer){
﻿  ﻿  if(toDeletedCustomer != undefined){
﻿  ﻿  ﻿  toDeletedCustomer.deleted = true;
﻿  ﻿  ﻿  toDeletedCustomer.save().on('success', function dbCustomerUpdate(deletedCustomer) {
﻿  ﻿  ﻿  ﻿  console.log('Removed Customer (#' + deletedCustomer.id + ').');
﻿  ﻿  ﻿  ﻿  self.emit('success', self.customerToJSON([deletedCustomer]));
﻿  ﻿  ﻿  }).on('failure', function dbCustomerUpdateError(error){
﻿  ﻿  ﻿  ﻿  self.emit('failure', "Customer remove error.");
﻿  ﻿  ﻿  });
﻿  ﻿  }
﻿  ﻿  else{
﻿  ﻿  ﻿  self.emit('failure', "Customer not exists.");
﻿  ﻿  }﻿  ﻿  
﻿  }).on('failure', function dbCustomerNotExists(){
﻿  ﻿  self.emit('failure', "Customer not exists.");
﻿  })
    
}

Customer.prototype.getList = function() {
﻿  var self = this;
    self.db.Customer.findAll(
﻿  ﻿  { where: {'deleted': false}}
﻿  ).on('success', function dbCustomerGetList(customerList) {
﻿  ﻿  self.emit('success', self.customerToJSON(customerList));
﻿  }).on('failure', function dbCustomerGetListError(error){
﻿  ﻿  self.emit('failure', "Customer remove error.");
﻿  });
}
Customer.prototype.getCustomerById = function(customerId) {
﻿  var self = this;
    self.db.Customer.find({ where: {'deleted': false, 'id': customerId} }
﻿  ).on('success', function dbCustomerInfo(customerInfo) {
﻿  ﻿  if(customerInfo != undefined){
﻿  ﻿  ﻿  self.emit('success', self.customerToJSON([customerInfo]));
﻿  ﻿  }
﻿  ﻿  else{
﻿  ﻿  ﻿  self.emit('failure', "By getting Customer Information was throw an error.");
﻿  ﻿  }
﻿  }).on('failure', function dbCustomerGetInfoError(error){
﻿  ﻿  self.emit('failure', "Customer not exist.");
﻿  });
}
Customer.prototype.getCustomerByName = function(customerName) {
﻿  var self = this;
    self.db.Customer.find({ where: {'deleted': false, 'name': customerName} }
﻿  ).on('success', function dbCustomerInfo(customerInfo) {
﻿  ﻿  if(customerInfo != undefined){
﻿  ﻿  ﻿  self.emit('success', self.customerToJSON([customerInfo]));
﻿  ﻿  }
﻿  ﻿  else{
﻿  ﻿  ﻿  self.emit('failure', "By getting Customer Information was throw an error.");
﻿  ﻿  }
﻿  }).on('failure', function dbCustomerGetInfoError(error){
﻿  ﻿  self.emit('failure', "Customer not exist.");
﻿  });
}
Customer.prototype.customerToJSON = function(result) {
﻿  var json = new Array();﻿  // dynamic size
﻿  for (var i=0; i < result.length; i++) {﻿  // iterate through array elements
﻿  ﻿  var customer = new Object();﻿  // Add object properties manually to avoid circular references
﻿  ﻿  customer.id = result[i].id;
﻿  ﻿  customer.name = result[i].name;
﻿  ﻿  customer.address = result[i].address;
﻿  ﻿  customer.password = result[i].password;
﻿  ﻿  customer.deleted = result[i].deleted;
﻿  ﻿  customer.isAdmin = result[i].isAdmin;
﻿  ﻿  /*
﻿  ﻿  if(result[i].isAdmin == 1)
﻿  ﻿  ﻿  customer.isAdmin = 'checked="checked"';
﻿  ﻿  else
﻿  ﻿  ﻿  customer.isAdmin = "";
﻿  ﻿  */
﻿  ﻿  json.push(customer);
﻿  }
﻿  return json;
}

Customer.prototype.webHandel = function(res, req) {
﻿  var self = this;
    switch(req.params[1]){
﻿      case "info":
    ﻿  ﻿  self.getCustomerById(req.body.txtCustomerId);
    ﻿  ﻿  self.on('success',function customerGetInfoSuccess(customerList){
    ﻿  ﻿  ﻿  res.send(customerList);
    ﻿  ﻿  }).on('failure', function customerGetInfoFailure(error){
    ﻿  ﻿  ﻿  res.send({'failure' : error});
    ﻿  ﻿  });
    ﻿  break;
    ﻿  case "list":
    ﻿  ﻿  self.getList();
    ﻿  ﻿  self.on('success',function customerGetListSuccess(customerList){
    ﻿  ﻿  ﻿  res.send(customerList);
    ﻿  ﻿  }).on('failure', function customerGetListFailure(error){
    ﻿  ﻿  ﻿  res.send({'failure' : error});
    ﻿  ﻿  });
    ﻿  break;
    ﻿  case "create":
    ﻿  ﻿  self.create(req.body.txtCustomerName,
    ﻿  ﻿  ﻿  ﻿   req.body.txtPassword,
    ﻿  ﻿  ﻿  ﻿   req.body.txtAddress,
    ﻿  ﻿  ﻿  ﻿   req.body.txtIsAdmin
    ﻿  ﻿  );
    ﻿  ﻿  self.on('success',function(newCustomerInJSON){
    ﻿  ﻿  ﻿  res.send(newCustomerInJSON);
    ﻿  ﻿  }).on('failure', function(error){
    ﻿  ﻿  ﻿  res.send({'failure' : error});
    ﻿  ﻿  });
    ﻿  break;
    ﻿  case "update":
    ﻿  ﻿  self.update(req.body.txtCustomerId, req.body.txtCustomerName, req.body.txtPassword, req.body.txtAddress, req.body.txtIsAdmin);
    ﻿  ﻿  self.on('success',function(CustomerInJSON){
    ﻿  ﻿  ﻿  res.send(CustomerInJSON);
    ﻿  ﻿  }).on('failure', function(error){
    ﻿  ﻿  ﻿  res.send({'failure' : error});
    ﻿  ﻿  });
    ﻿  break;
    ﻿  case "delete":
    ﻿  ﻿  self.remove(req.body.txtCustomerId);
    ﻿  ﻿  self.on('success',function(CustomerInJSON){
    ﻿  ﻿  ﻿  res.send(CustomerInJSON);
    ﻿  ﻿  });
    ﻿  ﻿  self.on('failure', function(error){
    ﻿  ﻿  ﻿  res.send({'failure' : error});
    ﻿  ﻿  });
    ﻿  break;
    ﻿  case "me":
    ﻿  ﻿  if(req.session.auth == false){
    ﻿  ﻿  ﻿  res.send({'info' : 'Customer not login.'});
    ﻿  ﻿  }
    ﻿  ﻿  else{
    ﻿  ﻿  ﻿  self.getCustomerById(req.session.customer_id);
﻿  ﻿  ﻿  ﻿  self.on('success',function(CustomerInJSON){
﻿  ﻿  ﻿  ﻿  ﻿  res.send({'info':'Customer information loaded.', 'cutomer': CustomerInJSON[0]});
﻿  ﻿  ﻿  ﻿  });
﻿  ﻿  ﻿  ﻿  self.on('failure', function(error){
﻿  ﻿  ﻿  ﻿  ﻿  res.send({'failure' : error});
﻿  ﻿  ﻿  ﻿  });
    ﻿  ﻿  }
    ﻿  ﻿  
    ﻿  break;
﻿  ﻿  default:
﻿  ﻿  ﻿  res.send({'failure' : "Customer: Wrong action."});
    }
}



