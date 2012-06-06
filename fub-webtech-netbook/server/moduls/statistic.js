var events = require("events");
var db = require('./ormapper.js');
var mysql = require('mysql');


// for us to do a require later
module.exports = Statistic;

function Statistic(mainDb) {
	this.client = mysql.createClient({user: 'simon',  password: 'pw'});

	this.client.query('USE nodejs');
	
	
	events.EventEmitter.call(this);
}


// inherit events.EventEmitter
Statistic.super_ = events.EventEmitter;
//All Methods get the EventEmitter
Statistic.prototype = Object.create(events.EventEmitter.prototype, {
    constructor: {
        value: Statistic,
        enumerable: false
    }
});

Statistic.prototype.allocationFromTheBikeCat = function() {
	var self = this;
		self.client.query(
	  	'SELECT bs.name AS Label, COUNT(i.id) AS Count FROM Invoices As i RIGHT JOIN BikeCats As bs ON (i.BikeCatId = bs.id) GROUP BY bs.name ORDER BY COUNT(i.id)',
	  function selectCb(err, results, fields) {
		if (err) {
		  throw err;
		}
		self.emit('success', results)
	  }
	);
}
Statistic.prototype.allocationTopFiveBikes = function() {
	var self = this;
		self.client.query(
	  	'SELECT b.name AS Label, COUNT(i.id) AS Count FROM Invoices As i LEFT JOIN Bikes As b ON (i.BikeId = b.id) GROUP BY b.name ORDER BY COUNT(i.id) LIMIT 5',
	  function selectCb(err, results, fields) {
		if (err) {
		  throw err;
		}
		self.emit('success', results)
	  }
	);
}
Statistic.prototype.allocationTopFiveCustomers = function() {
	var self = this;
		self.client.query(
	  	'SELECT b.name AS Label, COUNT(i.id) AS Count FROM Invoices As i LEFT JOIN Customers As b ON (i.CustomerId = b.id) GROUP BY b.name ORDER BY COUNT(i.id) LIMIT 5',
	  function selectCb(err, results, fields) {
		if (err) {
		  throw err;
		}
		self.emit('success', results)
	  }
	);
}
Statistic.prototype.allocationTopFiveCustomersMoney = function() {
	var self = this;
		self.client.query(
	  	'SELECT b.name AS Label, SUM(i.saldo) AS Count FROM Invoices As i LEFT JOIN Customers As b ON (i.CustomerId = b.id) GROUP BY b.name ORDER BY SUM(i.id) LIMIT 5',
	  function selectCb(err, results, fields) {
		if (err) {
		  throw err;
		}
		self.emit('success', results)
	  }
	);
}
Statistic.prototype.parsData = function(stats) {
	var sndLabels = "", sndDatas = "";
	for(var i = 0; i < stats.length; i++){
		if((i+1) == stats.length){
			sndLabels += stats[i].Label
			sndDatas += stats[i].Count
		}
		else{
			sndLabels += stats[i].Label+'|'
			sndDatas += stats[i].Count+','
		}
	}
	return {'labels': sndLabels, 'values': sndDatas};
}
Statistic.prototype.webHandel = function(res, req) {
	var self = this;
    switch(req.params[1]){
	    case "bikeCat": // just call ajax/Rent/info to get the current satuts of the rentel
    		self.allocationFromTheBikeCat();
    		self.on('success',function customerRentelGetInfoSuccess(stats){
    			var obj = self.parsData(stats);
				res.send({'img_src' : 'https://chart.googleapis.com/chart?cht=p&chd=t:' + obj.values + '&chs=300x300&chdl=' + obj.labels});
    		}).on('failure', function customerRentelGetInfoFailure(error){
    			res.send({'failure' : error});
    		});
    	break;
    	case "topFiveBiks":
    		self.allocationTopFiveBikes();
    		self.on('success',function customerRentelGetInfoSuccess(stats){
    			var obj = self.parsData(stats);
				res.send({'img_src' : 'https://chart.googleapis.com/chart?cht=bhs&chd=t:' + obj.values + '&chs=300x150&chdl=' + obj.labels});
    		}).on('failure', function customerRentelGetInfoFailure(error){
    			res.send({'failure' : error});
    		});
    	break;
    	case "topFiveCustomers":
    		self.allocationTopFiveCustomers();
    		self.on('success',function customerRentelGetInfoSuccess(stats){
    			var obj = self.parsData(stats);
				res.send({'img_src' : 'https://chart.googleapis.com/chart?cht=bhs&chd=t:' + obj.values + '&chs=300x150&chdl=' + obj.labels});
    		}).on('failure', function customerRentelGetInfoFailure(error){
    			res.send({'failure' : error});
    		});
    	break;
    	case "topFiveCustomersMony":
    		self.allocationTopFiveCustomersMoney();
    		self.on('success',function customerRentelGetInfoSuccess(stats){
    			var obj = self.parsData(stats);
				res.send({'img_src' : 'https://chart.googleapis.com/chart?cht=bhs&chd=t:' + obj.values + '&chs=300x150&chdl=' + obj.labels});
    		}).on('failure', function customerRentelGetInfoFailure(error){
    			res.send({'failure' : error});
    		});
    	break;
		default:
			res.send({'failure' : "Statistic: Wrong action."});
    }
    self.client.end();
}
