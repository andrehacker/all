module.exports = function(sequelize, DataTypes){
	return sequelize.define("Costumer",{
		id: { type: Sequelize.INTEGER, autoIncrement: true },
		name: { type: Sequelize.STRING, allowNull: false},
		address: { type: Sequelize.TEXT, allowNull: false},
		password: { type: Sequelize.STRING, allowNull: false}
	})
}
