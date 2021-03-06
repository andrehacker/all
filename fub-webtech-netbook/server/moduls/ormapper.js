var Sequelize = require("sequelize");
var sequelize = new Sequelize('nodejs', 'simon', 'pw');

var db = module.exports = {
	'sequelize': sequelize,
	Bike:
		 sequelize.define("Bike",{
			//bike_id: { type: Sequelize.INTEGER, autoIncrement: true },
			//bikecat_id:  {type: Sequelize.INTEGER, allowNull: false },
			name: { type: Sequelize.STRING, allowNull: false},
			description: { type: Sequelize.TEXT, allowNull: false},
			img_url: { type: Sequelize.TEXT, allowNull: false},
			position_lat: { type: Sequelize.STRING, allowNull: false},
			position_long: { type: Sequelize.STRING, allowNull: false},
			isRented: { type: Sequelize.BOOLEAN, allowNull: false, defaultValue: false},
			deleted: {type: Sequelize.BOOLEAN, allowNull: false, defaultValue: false}
		}),
	BikeCat:
		sequelize.define("BikeCat",{
			//bikecat_id: { type: Sequelize.INTEGER, autoIncrement: true },
			name: { type: Sequelize.STRING, allowNull: false},
			description: { type: Sequelize.STRING, allowNull: false},
			price:  {type: Sequelize.STRING},
			deleted: {type: Sequelize.BOOLEAN, allowNull: false, defaultValue: false}
			//pricecat_id:  {type: Sequelize.INTEGER}
		}),
 	Customer:
		sequelize.define("Customer",{
			//customer_id: { type: Sequelize.INTEGER, autoIncrement: true },
			name: { type: Sequelize.STRING, allowNull: false},
			address: { type: Sequelize.TEXT, allowNull: false},
			password: { type: Sequelize.STRING, allowNull: false},
			isAdmin: {type: Sequelize.BOOLEAN, allowNull: false, defaultValue: false},
			deleted: {type: Sequelize.BOOLEAN, allowNull: false, defaultValue: false}
		}),
	Invoice: 
		sequelize.define("Invoice",{
			//invoice_id: { type: Sequelize.INTEGER, autoIncrement: true },
			//customer_id: { type: Sequelize.INTEGER, allowNull:false },
			//bike_id: { type: Sequelize.INTEGER, allowNull:false },
			//pricecat_id: { type: Sequelize.INTEGER, allowNull:false },
			status: {type: Sequelize.INTEGER, allowNull: false, defaultValue: 0}, //0 = fahrrad ist gerade verliehn, 1= fahrrad ist zurück u. unbezahlt, 2 = gemaht, 3= bezahlt und zurück.
			rent_start: {type: Sequelize.DATE, allowNull:false},
			rent_end: {type: Sequelize.DATE, allowNull:true},
			saldo: { type: Sequelize.STRING, allowNull: true},
		})
};


// adds to BikeCat.(getBikes|setBikes|removeBike)()
db.BikeCat.hasMany(db.Bike);
//db.Bike.belongsTo(BikeCat);

/*
 * Die Rechnungs Relationen
 */
//See Example:
//https://github.com/sdepold/sequelize/blob/master/examples/using-multiple-model-files/app.js
// add by Bike.(getInvoices|setInvoices|removeInvoice)
db.Bike.hasMany(db.Invoice); 
db.Invoice.belongsTo(db.Bike); //add only a field BikdeId

db.BikeCat.hasMany(db.Invoice);
db.Invoice.belongsTo(db.BikeCat);//add only a field BikdeCatId

db.Customer.hasMany(db.Invoice);
db.Invoice.belongsTo(db.Customer);//add only a field CustomerId



