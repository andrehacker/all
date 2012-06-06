module.exports = function(sequelize, DataTypes){
	return sequelize.define("BikeCat",{
		id: { type: Sequelize.INTEGER, autoIncrement: true },
		label: { type: Sequelize.STRING, allowNull: false},
		description: { type: Sequelize.STRING, allowNull: false},
		pricecat:  {type: Sequelize.INTEGER}
	})
}
