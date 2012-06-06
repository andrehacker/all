var express = require('express');
var store = new express.session.MemoryStore;
var app = express.createServer(
	express.logger({format: 'dev'}),
	express.bodyParser(),
	express.cookieParser(),
	express.session({ secret: 'nodeJsCachArea', store: store }),
	'/', express.static(__dirname + '/../client')
);
app.listen(3000);

var db = require('./moduls/ormapper.js');



dynSites = function(req, res){
	switch (req.params[0]) {
		/**
		 * /ajax/login der Username muss in [txtUser] und das Passwort in [txtPassword] stehen.
		 */
  		case "login":
  			var Auth = require("./moduls/login.js");
			var auth = new Auth(db);
			if(req.params[1] == "info"){
				auth.getAuthInfo(req, res);
			}
			else{
				auth.on('success',function(customer){
					req.session.customer_id = customer.id;
					req.session.isAdmin = customer.isAdmin;
					req.session.auth = true;
					console.log('Login (Name: ' + customer.name + ', isAdmin: ' + customer.isAdmin + ')')
					res.send({'success': 'Warmly Welcome ' + customer.name, 'customer': customer});
				}).on('failure',function(error){
					res.send({'failure': error});
				});
				auth.login(req.body.txtUser,req.body.txtPassword);
			}
		break;
  		/**
  		 * simple call ajax/logout
  		 */
  		case "logout":
  			req.session.destroy();
  			res.send({'success': "You are logout"});
  		break;
  		case "Registration":
  			var Registration = require('./moduls/registration.js');
  			var reg = new Registration(db);
  			reg.webHandel(res, req);  			
  		break;
  		case "Customer"://http://localhost:port/ajax/kunde/
  			if(req.session.auth && req.session.isAdmin){
  				var Customer = require("./moduls/customer.js");
				var customer = new Customer(db).webHandel(res, req);
  			}		
  			else{
  				res.send({'failure': "You have no Permissions."})
  			}
		break;
		case "Invoice":
			var Invoice = require("./moduls/invoice.js");
			var invoice = new Invoice(db).webHandel(res, req);
		break;
		case "Rent":
			var Rent = require("./moduls/rent.js");
			var rent = new Rent(db).webHandel(res, req);
		break;
		case "Statistic":
			var Statistic = require("./moduls/statistic.js");
			var statistic = new Statistic(db).webHandel(res, req);
		break;
		case "Admin":
  			switch(req.params[1]){
  				case "loadbikes":
					var Admin = require("./moduls/admin.js");
					var admin = new Admin();
					admin.loadBikes( function (result) {
						if (result != null) {
							res.send(result);
						}
						else { res.send("Error loading bikes"); }
					} );
  					break;
  				case "loadbike":
					var Admin = require("./moduls/admin.js");
					var admin = new Admin();
					admin.loadBike( req.body.id , function (result) {
						if (result != null) {
							res.send(result);
						}
						else { res.send("Error loading bikes"); }
					} );
  					break;
  				case "addbike":
  					console.log("Add bike: " + req.body);
  					
					var Admin = require("./moduls/admin.js");
					var admin = new Admin();
					admin.addBike( req.body, function (result) {
						if (result != null) {
							res.send(result);
						}
						else { res.send("Unhandeled error adding bike"); }
					} );
  					break;
  				case "deletebike":
  					console.log("Delete bike: " + req.body);
  					
					var Admin = require("./moduls/admin.js");
					var admin = new Admin();
					admin.deleteBike( req.body, function (result) {
						if (result != null) {
							res.send(result);
						}
						else { res.send("Unhandeled error deleting bike"); }
					} );
  					break;
  				case "loadbikecats":
					var Admin = require("./moduls/admin.js");
					var admin = new Admin();
					admin.loadBikeCats( function (result) {
						if (result != null) {
							res.send(result);
						}
						else { res.send("Error loading bikecats"); }
					} );
  					break;
  				case "addbikecat":
  					console.log("Add bikecat: " + req.body);
  					
					var Admin = require("./moduls/admin.js");
					var admin = new Admin();
					admin.addBikeCat( req.body, function (result) {
						if (result != null) {
							res.send(result);
						}
						else { res.send("Unhandeled error adding bikecat"); }
					} );
  					break;
  				case "deletebikecat":
  					console.log("Delete bikecat: " + req.body);
  					
					var Admin = require("./moduls/admin.js");
					var admin = new Admin();
					admin.deleteBikeCat( req.body, function (result) {
						if (result != null) {
							res.send(result);
						}
						else { res.send("Unhandeled error deleting bikecat"); }
					} );
  					break;
  				default:
  					res.send("Admin: Wrong action.");
  					console.log("Admin: Wrong action");
  			}
			break;
		case "quit":
			process.exit();
			break;
		default:
	    	res.send(req.params);
    }
}

//http://localhost:port/ajax/%modul%/%param%
app.get(/^\/ajax?(?:\/(\w+)(?:\/(\w+))?)?/, dynSites);
app.post(/^\/ajax?(?:\/(\w+)(?:\/(\w+))?)?/, dynSites);

