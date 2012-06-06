module.exports = function(sequelize, DataTypes){
	return sequelize.define("PriceCat",{
		id: { type: Sequelize.INTEGER, autoIncrement: true },
		label: { type: Sequelize.STRING, allowNull: false},
		price:  {type: Sequelize.STRING},
		cycleunit:  {type: Sequelize.STRING}
	})
}
