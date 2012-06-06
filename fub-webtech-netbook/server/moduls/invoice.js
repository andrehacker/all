var events = require("events");



function Invoice(mainDb) {
	this.db = mainDb;
	this.lookupActiv = false;
	this.customerList = new Object();
	this.bikeList = new Object();
	this.bikeCatList = new Object();
	events.EventEmitter.call(this);
}


// inherit events.EventEmitter
Invoice.super_ = events.EventEmitter;
//All Methods get the EventEmitter
Invoice.prototype = Object.create(events.EventEmitter.prototype, {
    constructor: {
        value: Invoice,
        enumerable: false
    }
});
Invoice.prototype.create = function(CustomerId, BikeId, BikeCatId, status, start) {
	var self = this;
	
	var newInvoice = self.db.Invoice.build({'CustomerId': CustomerId,
		'BikeId': BikeId, 'BikeCatId':BikeCatId, 'status': status, 'rent_start': start })
	newInvoice.save().on('success', function dbNewInvoice(result) {
		if(result == undefined){
			self.emit('failure', "Invoice problem by create new one.");
		}
		else{
			self.emit('success', {'info': 'Invoice created.', 'Invoice': self.InvoiceToJson([result])});
		}		
	}).on('failure', function dbNewInvoiceFailure(error){
		self.emit('failure', "Invoice problem by create new one.");
	});
}
Invoice.prototype.setRentelEnd = function(InvoiceId, end, status) {
	var self = this;
    self.db.Invoice.find({ where: {'id': InvoiceId} }).on('success', function changeRentelEnd(invoice){
    	self.db.BikeCat.find({where: {'id': invoice.BikeCatId}}).on('success', function(bikeCat){
			var timeDiff = (end.getTime() - invoice.rent_start.getTime()) / (1000*60);
			var pricePerMin = parseFloat(bikeCat.price);
			
			//set new values of invoice
			invoice.rent_end = end;
			invoice.status = 1;
			invoice.saldo = Math.round(timeDiff * pricePerMin);
			 
			invoice.save().on('success', function rentelEndUpdate(updateInvoice) {
				console.log('Set Invoice (#' + updateInvoice.id + ') rentel end ' + end + '.');
				self.emit('success', self.InvoiceToJson([updateInvoice]));
			}).on('failure', function rentelEndUpdateError(error){
				self.emit('failure', "Can't set rentel End update error.");
			});
		}).on('failure', function(){
			self.emit('failure', "Can't calculate price.");
		});
    }).on('failure', function updateFindInvoiceFailure(){
    	self.emit('failure', "Invoice update error (Invoice not found).");
    });
}
Invoice.prototype.changeStatus = function(InvoiceId, status) {
	var self = this;
    self.db.Invoice.find({ where: {'id': InvoiceId} }).on('success', function changeStatusInvoice(invoice){
    	invoice.status = status;
    	invoice.save().on('success', function dbInvoiceUpdate(updateInvoice) {
			console.log('Set Invoice (#' + updateInvoice.id + ') to status ' + status + '.');
			self.emit('success', self.InvoiceToJson([updateInvoice]));
		}).on('failure', function dbInvoiceUpdateError(error){
			self.emit('failure', "Invoice update error.");
		});
    }).on('failure', function updateFindInvoiceFailure(){
    	self.emit('failure', "Invoice update error (Invoice not found).");
    });
}



Invoice.prototype.getList = function(isAdmin, customerId) {
	var self = this;
	if(isAdmin){
		var whereObj = {};//{ where: {'deleted': false}};
	}
	else{
		var whereObj = { where: {'CustomerId': customerId}};
	}
    self.db.Invoice.findAll(whereObj).on('success', function dbInvoiceGetList(customerList) {
		self.emit('success', self.InvoiceToJson(customerList));
	}).on('failure', function dbInvoiceGetListError(error){
		self.emit('failure', "Invoice remove error.");
	});
}
Invoice.prototype.getInvoiceById = function(invoiceId) {
	var self = this;
    self.db.Invoice.find({ where: {'id': invoiceId} }
	).on('success', function dbInvoiceInfo(customerInfo) {
		if(customerInfo != undefined){
			self.emit('success', self.InvoiceToJson([customerInfo]));
		}
		else{
			self.emit('failure', "By getting Invoice Information was throw an error.");
		}
	}).on('failure', function dbInvoiceGetInfoError(error){
		self.emit('failure', "Invoice not exist.");
	});
}

Invoice.prototype.InvoiceToJson = function(objToJson) {
	var self = this;
	var result = objToJson;
	var json = new Array();	// dynamic size
	for (var r=0; r < result.length; r++) {	// iterate through array elements
		var entry = new Object();	// Add object properties manually to avoid circular references
		for(var i in result[r].attributes){//iterate through all attributes
			//LookUp Customer
			if(result[r].attributes[i] == "CustomerId"){
				self.lookup(self, self.db.Customer, self.customerList, result[r][result[r].attributes[i]]);
			}
			//LookUp Bike
			else if(result[r].attributes[i] == "BikeId"){
				self.lookup(self, self.db.Bike, self.bikeList, result[r][result[r].attributes[i]]);
			}
			//LookUp BikeCat
			else if(result[r].attributes[i] == "BikeCatId"){
				self.lookup(self, self.db.BikeCat, self.bikeCatList, result[r][result[r].attributes[i]]);
			}
			//push current attribute to row
			entry[result[r].attributes[i]] = result[r][result[r].attributes[i]];
		}
		//add row
		json.push(entry);
	}
	//return list of record set
	return json;
}
Invoice.prototype.lookup = function(self, dbTable, list, tmpId){
	if(list[tmpId] == undefined){
		dbTable.find({where: {'id': tmpId}}).on('success',function(objInfo){
			if(objInfo != undefined){
				var obj = self.InvoiceToJson([objInfo]);
				list[tmpId] = obj[0];
			}
		});
	}
}
Invoice.prototype.webHandel = function(res, req) {
	var self = this;
    switch(req.params[1]){
	    case "info":
    		self.getInvoiceById(req.body.txtInvoiceId);
    		self.on('success',function customerGetInfoSuccess(customerList){
    			//kleiner work a round
    			setTimeout(function(){
	    			res.send({'invoices': customerList, 'customers': self.customerList, 'bikes': self.bikeList, 'bikeCats': self.bikeCatList});
    			},250);
    		}).on('failure', function customerGetInfoFailure(error){
    			res.send({'failure' : error});
    		});
    	break;
    	case "list":
    		self.getList(req.session.isAdmin,req.session.customer_id);
    		self.on('success',function customerGetListSuccess(customerList){
    			//kleiner work a round
    			setTimeout(function(){
	    			res.send({'invoices': customerList, 'customers': self.customerList, 'bikes': self.bikeList, 'bikeCats': self.bikeCatList});
    			},250);
    		}).on('failure', function customerGetListFailure(error){
    			res.send({'failure' : error});
    		});
    	break;
    	case "create":
    		self.create(req.body.txtCustomerId,
    				 req.body.txtBikeId,
    				 req.body.txtBikeCatId,
    				 0,
    				 new Date()
    		);
    		self.on('success',function(newInvoiceInJSON){
    			//kleiner work a round
    			setTimeout(function(){
	    			res.send({'invoices': newInvoiceInJSON, 'customers': self.customerList, 'bikes': self.bikeList, 'bikeCats': self.bikeCatList});
    			},250);
    		}).on('failure', function(error){
    			res.send({'failure' : error});
    		});
    	break;
    	case "changeStatus":
    		self.changeStatus(req.body.txtInvoiceId, req.body.txtInvoiceStatus);
    		self.on('success',function(InvoiceInJSON){
    			//kleiner work a round
    			setTimeout(function(){
	    			res.send({'invoices': InvoiceInJSON, 'customers': self.customerList, 'bikes': self.bikeList, 'bikeCats': self.bikeCatList});
    			},250);
    		}).on('failure', function(error){
    			res.send({'failure' : error});
    		});
    	break;
    	case "setRentelEnd":
    		self.setRentelEnd(req.body.txtInvoiceId, new Date());
    		self.on('success',function(InvoiceInJSON){
    			//kleiner work a round
    			setTimeout(function(){
	    			res.send({'invoices': InvoiceInJSON, 'customers': self.customerList, 'bikes': self.bikeList, 'bikeCats': self.bikeCatList});
    			},250);
    		});
    		self.on('failure', function(error){
    			res.send({'failure' : error});
    		});
    	break;
		default:
			res.send({'failure' : "Invoice: Wrong action."});
    }
}

module.exports = Invoice;
