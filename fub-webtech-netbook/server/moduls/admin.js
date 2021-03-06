/*
This module uses callback mechanism instead of EventEmitter
to communicate with the caller
*/
var db = require('./ormapper.js');

// Define constructor with members - and methods!
function Admin() {
	this.db = db;
	
	this.loadBikes = loadBikes;
	this.loadBike = loadBike;
	this.addBike = addBike;
	this.deleteBike = deleteBike;
	
	this.loadBikeCats = loadBikeCats;
	this.addBikeCat = addBikeCat;
	this.deleteBikeCat = deleteBikeCat;
}

var temp = null;	// Temporary storage - not safe if there is more then one client!!! DIRTY WORKAROUND!!!

/*
VERY BAD: converting a sequelize object to JSON will fail due to circular references.
Still open:
https://github.com/sdepold/sequelize/issues/73
https://github.com/sdepold/sequelize/issues/83

So let's write our own method to do this:
*/

function bikesToJSON(bikes, cats) {
	console.log("Cats: " + cats.length);
	var json = new Array();	// dynamic size
	for (var i=0; i < bikes.length; i++) {	// iterate through array elements
		json.push(bikeToObj(bikes[i], cats));
	}
	return json;
}

function bikeToJSON(bike, cats) {
	console.log("Cats: " + cats.length);
	return bikeToObj(bike, cats);
}

function bikeToObj(curBike, cats) {
	cat = getCatById(curBike.BikeCatId, cats);
	var bike = new Object();	// Add object properties manually to avoid circular references
	bike.id = curBike.id;
	bike.name = curBike.name;
	bike.description = curBike.description;
	bike.img_url = curBike.img_url;
	bike.position_lat = curBike.position_lat;
	bike.position_long = curBike.position_long;
	bike.deleted = curBike.deleted;
	bike.isRented = curBike.isRented;
	bike.category = cat.name;
	bike.price = cat.price;
	return bike;
}

function getCatById(id, cats) {
	if (cats == null) {
		return "no categories";
	}
	for (var i=0; i < cats.length; i++) {
		if (cats[i].id == id) {
			return cats[i];
		}
	}
	return "no category";
}

function bikeCatsToJSON(result) {
	var json = new Array();	// dynamic size
	for (var i=0; i < result.length; i++) {	// iterate through array elements
		var bikecat = new Object();	// Add object properties manually to avoid circular references
		bikecat.id = result[i].id;
		bikecat.name = result[i].name;
		bikecat.description = result[i].description;
		bikecat.price = result[i].price;
		bikecat.deleted = result[i].deleted;
		json.push(bikecat);
	}
	return json;
}

// Interface methods
function loadBikes (callback) {
	db.Bike.findAll({where: {deleted: false}}).on('success', function(bikes) {
		console.log("Loading Bikes result: " + bikes)
		// Load Bike Categories (manual JOIN)
		//temp = bikes;	// make result available in next callback!
		db.BikeCat.findAll({where: {deleted: false}}).on('success', function(bikeCats) {
			var cats = bikeCatsToJSON(bikeCats);
			// callback
			callback(bikesToJSON(bikes, cats));	// Parse model to JSON manually
		});
	}).on('failure', function(error){
		console.log("Error loading bikes from DB");
		callback(null);
	});
}

function loadBike (bikeId, callback) {
	db.Bike.find({where: {id: bikeId}}).on('success', function(bike) {
		console.log("Loading Bike result: " + bike)
		// Load Bike Category (manual JOIN)
		//temp = bike;	// make result available in next callback!
		db.BikeCat.findAll({where: {id: bike.BikeCatId}}).on('success', function(bikeCats) {
			//console.log("Bike id still available? " + bike.id);
			var cats = bikeCatsToJSON(bikeCats);
			// callback
			callback(bikeToJSON(bike, cats));	// Parse model to JSON manually
		});
	}).on('failure', function(error){
		console.log("Error loading bike from DB");
		callback(null);
	});
}

function addBike (bike, callback) {
	
	var location = getRandomLocation();
	
	var newBike = db.Bike.build( {
		name: bike.new_bike_name,
		description: bike.new_bike_description,
		img_url: bike.new_bike_url,
		position_lat: location.lat,
		position_long: location.long,
		deleted: false,
		BikeCatId: bike.new_bike_cat
	});
	newBike.save().on('success', function() {
		console.log("Success adding bike to db");
		callback("ok");
	}).on('failure', function(error){
		console.log("Error adding bike");
		callback("Error adding bike");
	});
}

function getRandomLocation () {
	// Currently hardcoded: Around Berlin Mitte 52.522697, 13.415122
	// vary from -0.03 to +0.03
	// 0.00 - 0.03 = -0.03
	// 0.06 - 0.03 =  0.03
	var loc = new Object();
	loc.lat  = 52.522697 - 0.03 + ((Math.random() * 6)/100);
	loc.long = 13.415122 - 0.03 + ((Math.random() * 6)/100);
	return loc;
}

function deleteBike (data, callback) {
	
	// First find bike to delete
	console.log("Inside delete bike: " + data.id);
	db.Bike.find(
		{where: {id: data.id} }
	).on('success', function(bike) {
		if (bike == null) {
			callback("Error: No bike found");
		}
		console.log("Loaded bike to delete: " + bike)
		bike.deleted = true;
		bike.save().on('success', function() {
			console.log("Success deleting bike");
			callback("ok");
		}).on('failure', function(error){
			console.log("Error deleting bike");
			callback("error deleting bike");
		});
		
	}).on('failure', function(error){
		console.log("Error deleting bike");
		callback(null);
	});
}




function loadBikeCats (callback) {
	db.BikeCat.findAll({where: {deleted: false}}).on('success', function(result) {
		console.log("Loading BikeCats result: " + result)
		// callback
		callback( bikeCatsToJSON(result) );
	}).on('failure', function(error){
		console.log("Error loading bike cats from DB");
		callback(null);
	});
}

function addBikeCat (bikecat, callback) {
	
	var newcat = db.BikeCat.build( {
		name: bikecat.new_bikecat_name,
		description: bikecat.new_bikecat_description,
		price: bikecat.new_bikecat_price,
		deleted: false
	});
	newcat.save().on('success', function() {
		console.log("Success adding bikecat to db");
		// callback!
		callback("ok");
	}).on('failure', function(error){
		console.log("Error adding bikecat to db");
		callback("error adding bikecat");
	});
}

function deleteBikeCat (data, callback) {
	
	// First find bikecat to delete
	db.BikeCat.find(
		{where: {id: data.id} }
	).on('success', function(bikecat) {
		if (bikecat == null) {
			callback("Error: No bikecat found");
		}
		console.log("Loaded bikecat to delete: " + bikecat)
		bikecat.deleted = true;
		bikecat.save().on('success', function() {
			console.log("Success deleting bikecat");
			callback("ok");
		}).on('failure', function(error){
			console.log("Error deleting bikecat");
			callback("error deleting bikecat");
		});
		
	}).on('failure', function(error){
		console.log("Error deleting bikecat");
		callback(null);
	});
}



// Export constructors
module.exports = Admin;


